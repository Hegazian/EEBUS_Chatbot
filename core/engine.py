"""
EEBUS Chat Engine Factory & Multi-Provider LLM Orchestrator
Provides isolated ContextChatEngine instances, dynamic model selection, and memory buffers.
"""

import os
import json
import time
import chromadb
from typing import Tuple, Optional
from llama_index.core import VectorStoreIndex, Settings
from llama_index.core.memory import ChatMemoryBuffer
from llama_index.core.postprocessor import SentenceTransformerRerank
from llama_index.core.chat_engine import ContextChatEngine
from llama_index.vector_stores.chroma import ChromaVectorStore
from llama_index.retrievers.bm25 import BM25Retriever
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.llms.gemini import Gemini

from .config import (
    PERSIST_DIR, BM25_PERSIST_DIR, CACHE_FILE, COLLECTION_NAME,
    PRIMARY_EMBEDDING_MODEL, FALLBACK_EMBEDDING_MODEL, RERANKER_MODEL,
    DEFAULT_RETRIEVER_K, DEFAULT_TEMPERATURE, CACHE_TTL_HOURS, SYSTEM_PROMPT
)
from .retriever import EEBUSHybridRetriever


# ─── Embedding Setup ────────────────────────────────────────────────────────────

def init_embedding_model():
    """Initialize BGE-small embedding model with automatic fallback."""
    try:
        return HuggingFaceEmbedding(model_name=PRIMARY_EMBEDDING_MODEL)
    except Exception as e:
        print(f"⚠️ Primary embedding model ({PRIMARY_EMBEDDING_MODEL}) failed: {e}. Falling back to {FALLBACK_EMBEDDING_MODEL}...")
        return HuggingFaceEmbedding(model_name=FALLBACK_EMBEDDING_MODEL)


# Configure global default embedding model once
Settings.embed_model = init_embedding_model()


# ─── Model Discovery & Persistent Caching ──────────────────────────────────────

def select_best_model() -> str:
    """Dynamically discover available Gemini models with persistent caching."""
    api_key = os.getenv("GOOGLE_API_KEY")
    if not api_key or api_key == "your_actual_gemini_api_key_here":
        return "models/gemini-1.5-flash"

    if os.path.exists(CACHE_FILE):
        try:
            with open(CACHE_FILE, "r", encoding="utf-8") as f:
                cache_data = json.load(f)
            cached_model = cache_data.get("selected_model")
            cached_time = cache_data.get("timestamp", 0)
            if cached_model and (time.time() - cached_time < CACHE_TTL_HOURS * 3600):
                return cached_model
        except Exception:
            pass

    try:
        import google.generativeai as genai
        genai.configure(api_key=api_key)
        available_models = [m.name for m in genai.list_models() if 'generateContent' in m.supported_generation_methods]
        
        priority = [
            "models/gemini-2.5-flash",
            "models/gemini-2.0-flash",
            "models/gemini-1.5-flash-latest",
            "models/gemini-1.5-flash",
            "models/gemini-flash-latest",
            "models/gemini-1.5-pro",
            "models/gemini-pro"
        ]
        
        selected = None
        for candidate in priority:
            if candidate in available_models:
                selected = candidate
                break
                
        if not selected and available_models:
            selected = available_models[0]
            
        final_model = selected or "models/gemini-1.5-flash"
        
        with open(CACHE_FILE, "w", encoding="utf-8") as f:
            json.dump({"selected_model": final_model, "timestamp": time.time()}, f, indent=2)
            
        return final_model
    except Exception as e:
        print(f"⚠️ Dynamic model probing failed ({e}). Falling back to 'models/gemini-1.5-flash'.")
        return "models/gemini-1.5-flash"


LLM_MODEL = select_best_model()


# ─── Chat Engine Factory (Per-Session Isolated) ────────────────────────────────

def create_chat_engine(
    temperature: float = DEFAULT_TEMPERATURE,
    top_k: int = DEFAULT_RETRIEVER_K,
    llm_provider: str = "Gemini (Google)",
    api_key: str = "",
    component_filter: str = "All Specifications",
    use_reranker: bool = True
) -> Tuple[ContextChatEngine, int]:
    """
    Factory function creating an isolated ContextChatEngine instance with
    dedicated memory buffer, hybrid retriever, and optional cross-encoder reranker.
    """
    if not os.path.exists(PERSIST_DIR):
        raise FileNotFoundError(
            f"Vector store not found at {PERSIST_DIR}.\n"
            "Run 'python eebus_ingest.py' first to index the documentation."
        )

    db = chromadb.PersistentClient(path=PERSIST_DIR)
    chroma_collection = db.get_collection(COLLECTION_NAME)
    vector_store = ChromaVectorStore(chroma_collection=chroma_collection)
    
    index = VectorStoreIndex.from_vector_store(vector_store)
    session_memory = ChatMemoryBuffer.from_defaults(token_limit=16000)

    # Initialize isolated LLM instance
    if llm_provider == "Gemini (Google)":
        key = api_key or os.getenv("GOOGLE_API_KEY")
        if not key or key == "your_actual_gemini_api_key_here":
            raise ValueError("Google Gemini API Key is missing. Please set GOOGLE_API_KEY in .env or the UI.")
        model_name = LLM_MODEL if LLM_MODEL else "models/gemini-1.5-flash"
        session_llm = Gemini(model=model_name, temperature=temperature, max_tokens=4096, api_key=key)
    elif llm_provider == "ChatGPT (OpenAI)":
        try:
            from llama_index.llms.openai import OpenAI
        except ImportError:
            raise ImportError("llama-index-llms-openai is not installed. Please install it via 'pip install llama-index-llms-openai'.")
        key = api_key or os.getenv("OPENAI_API_KEY")
        if not key or key == "your_openai_api_key_here":
            raise ValueError("OpenAI API Key is missing. Please set OPENAI_API_KEY in .env or the UI.")
        session_llm = OpenAI(model="gpt-4o-mini", temperature=temperature, max_tokens=4096, api_key=key)
    elif llm_provider == "Claude (Anthropic)":
        try:
            from llama_index.llms.anthropic import Anthropic
        except ImportError:
            raise ImportError("llama-index-llms-anthropic is not installed. Please install it via 'pip install llama-index-llms-anthropic anthropic'.")
        key = api_key or os.getenv("ANTHROPIC_API_KEY")
        if not key or key == "your_anthropic_api_key_here":
            raise ValueError("Anthropic API Key is missing. Please set ANTHROPIC_API_KEY in .env or the UI.")
        session_llm = Anthropic(model="claude-3-haiku-20240307", temperature=temperature, max_tokens=4096, api_key=key)
    elif llm_provider == "Mock":
        from llama_index.core.llms.mock import MockLLM
        session_llm = MockLLM()
    else:
        raise ValueError(f"Unknown LLM Provider: {llm_provider}")

    # Build hybrid retriever (Vector + BM25)
    fetch_k = max(int(top_k) * 2, 14)
    vector_retriever = index.as_retriever(similarity_top_k=fetch_k)

    bm25_retriever = None
    if os.path.exists(BM25_PERSIST_DIR):
        try:
            bm25_retriever = BM25Retriever.from_persist_dir(BM25_PERSIST_DIR)
            bm25_retriever.similarity_top_k = fetch_k
        except Exception as err:
            print(f"⚠️ Note loading BM25 index ({err}). Continuing with vector retriever.")

    hybrid_retriever = EEBUSHybridRetriever(
        vector_retriever=vector_retriever,
        bm25_retriever=bm25_retriever,
        component_filter=component_filter,
        candidate_k=fetch_k
    )

    # Cross-Encoder Reranker postprocessor
    node_postprocessors = []
    if use_reranker:
        try:
            node_postprocessors.append(
                SentenceTransformerRerank(
                    model=RERANKER_MODEL,
                    top_n=int(top_k)
                )
            )
        except Exception as err:
            print(f"⚠️ Note loading SentenceTransformerRerank ({err}).")

    chat_engine = ContextChatEngine.from_defaults(
        retriever=hybrid_retriever,
        memory=session_memory,
        system_prompt=SYSTEM_PROMPT,
        node_postprocessors=node_postprocessors,
        llm=session_llm
    )
    
    total_chunks = chroma_collection.count()
    return chat_engine, total_chunks
