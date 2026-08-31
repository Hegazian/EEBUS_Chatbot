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
from llama_index.core.chat_engine import ContextChatEngine
from llama_index.vector_stores.chroma import ChromaVectorStore
from llama_index.retrievers.bm25 import BM25Retriever
from llama_index.embeddings.huggingface import HuggingFaceEmbedding

from .config import (
    PERSIST_DIR, BM25_PERSIST_DIR, CACHE_FILE, COLLECTION_NAME,
    PRIMARY_EMBEDDING_MODEL, FALLBACK_EMBEDDING_MODEL, RERANKER_MODEL,
    DEFAULT_RETRIEVER_K, DEFAULT_TEMPERATURE, CACHE_TTL_HOURS, SYSTEM_PROMPT,
    DEFAULT_USER_ROLE, get_system_prompt_for_role
)
from .retriever import EEBUSHybridRetriever


# ─── Embedding Setup ────────────────────────────────────────────────────────────

_EMBED_MODEL = None


def get_embedding_model():
    """Lazily initialize BGE-small embedding model with automatic fallback."""
    global _EMBED_MODEL
    if _EMBED_MODEL is not None:
        return _EMBED_MODEL
    try:
        _EMBED_MODEL = HuggingFaceEmbedding(model_name=PRIMARY_EMBEDDING_MODEL)
    except Exception as e:
        print(f"⚠️ Primary embedding model ({PRIMARY_EMBEDDING_MODEL}) failed: {e}. Falling back to {FALLBACK_EMBEDDING_MODEL}...")
        _EMBED_MODEL = HuggingFaceEmbedding(model_name=FALLBACK_EMBEDDING_MODEL)
    Settings.embed_model = _EMBED_MODEL
    return _EMBED_MODEL


# Backward compatibility alias
init_embedding_model = get_embedding_model


# ─── BM25 Singleton Cache ──────────────────────────────────────────────────────

_CACHED_BM25_RETRIEVER = None


def get_cached_bm25_retriever() -> Optional[BM25Retriever]:
    """Lazily load and cache the persistent BM25Retriever in memory to avoid repeated disk reads."""
    global _CACHED_BM25_RETRIEVER
    if _CACHED_BM25_RETRIEVER is not None:
        return _CACHED_BM25_RETRIEVER
    if os.path.exists(BM25_PERSIST_DIR):
        try:
            _CACHED_BM25_RETRIEVER = BM25Retriever.from_persist_dir(BM25_PERSIST_DIR)
            return _CACHED_BM25_RETRIEVER
        except Exception as err:
            print(f"⚠️ Note loading BM25 index ({err}).")
            return None
    return None


# ─── Model Discovery & Persistent Caching ──────────────────────────────────────

def select_best_model(api_key: Optional[str] = None) -> str:
    """Dynamically discover available Gemini models with persistent caching."""
    key = api_key or os.getenv("GOOGLE_API_KEY")
    if not key or key == "your_actual_gemini_api_key_here":
        return "models/gemini-1.5-flash"

    import hashlib
    key_hash = hashlib.sha256(key.encode()).hexdigest()[:12]

    if os.path.exists(CACHE_FILE):
        try:
            with open(CACHE_FILE, "r", encoding="utf-8") as f:
                cache_data = json.load(f)
            cached_model = cache_data.get("selected_model")
            cached_time = cache_data.get("timestamp", 0)
            cached_hash = cache_data.get("key_hash", "")
            if cached_model and cached_hash == key_hash and (time.time() - cached_time < CACHE_TTL_HOURS * 3600):
                return cached_model
        except Exception:
            pass

    try:
        import warnings
        with warnings.catch_warnings():
            warnings.filterwarnings("ignore", category=FutureWarning)
            import google.generativeai as genai
            genai.configure(api_key=key)
            available_models = [m.name for m in genai.list_models() if 'generateContent' in m.supported_generation_methods]
        
        # Prioritize stable models with generous free-tier quotas (15 RPM / 1,500 RPD)
        # Avoid floating aliases like 'gemini-flash-latest' which route to preview models with strict 5 RPM caps.
        priority = [
            "models/gemini-1.5-flash",
            "models/gemini-2.0-flash",
            "models/gemini-1.5-flash-latest",
            "models/gemini-1.5-pro",
            "models/gemini-pro"
        ]
        
        selected = None
        for candidate in priority:
            if candidate in available_models:
                selected = candidate
                break
                
        if not selected and available_models:
            flash_candidates = [m for m in available_models if "1.5-flash" in m or "2.0-flash" in m]
            selected = flash_candidates[0] if flash_candidates else available_models[0]
            
        final_model = selected or "models/gemini-1.5-flash"
        
        with open(CACHE_FILE, "w", encoding="utf-8") as f:
            json.dump({"selected_model": final_model, "key_hash": key_hash, "timestamp": time.time()}, f, indent=2)
            
        return final_model
    except Exception as e:
        return "models/gemini-1.5-flash"


# ─── Chat Engine Factory (Per-Session Isolated) ────────────────────────────────

def create_chat_engine(
    temperature: float = DEFAULT_TEMPERATURE,
    top_k: int = DEFAULT_RETRIEVER_K,
    llm_provider: str = "Gemini (Google)",
    api_key: str = "",
    component_filter: str = "All Specifications",
    use_reranker: bool = True,
    user_role: str = DEFAULT_USER_ROLE
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
    
    get_embedding_model()
    index = VectorStoreIndex.from_vector_store(vector_store)
    session_memory = ChatMemoryBuffer.from_defaults(token_limit=16000)

    # Initialize isolated LLM instance
    if llm_provider == "Gemini (Google)":
        key = api_key or os.getenv("GOOGLE_API_KEY")
        if not key or key == "your_actual_gemini_api_key_here":
            raise ValueError("Google Gemini API Key is missing. Please set GOOGLE_API_KEY in .env or the UI.")
        try:
            from llama_index.llms.gemini import Gemini
        except ImportError:
            raise ImportError("llama-index-llms-gemini is not installed. Please install it via 'pip install llama-index-llms-gemini'.")
        model_name = select_best_model(key)
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

    # Determine component target for metadata-level filtering
    target_comp = None
    if component_filter and component_filter not in ["All", "All Specifications"]:
        cf_lower = component_filter.lower()
        if "ship" in cf_lower:
            target_comp = "SHIP"
        elif "spine" in cf_lower:
            target_comp = "SPINE"
        elif "use" in cf_lower:
            target_comp = "UseCase"

    # Build hybrid retriever (Vector + BM25)
    fetch_k = max(int(top_k) * 3, 24)
    filters = None
    if target_comp:
        try:
            from llama_index.core.vector_stores import MetadataFilters, ExactMatchFilter
            filters = MetadataFilters(filters=[ExactMatchFilter(key="component", value=target_comp)])
        except Exception:
            filters = None

    vector_retriever = index.as_retriever(similarity_top_k=fetch_k, filters=filters)

    bm25_retriever = get_cached_bm25_retriever()
    if bm25_retriever is not None:
        bm25_retriever.similarity_top_k = max(fetch_k * 2, 40) if target_comp else fetch_k

    hybrid_retriever = EEBUSHybridRetriever(
        vector_retriever=vector_retriever,
        bm25_retriever=bm25_retriever,
        component_filter=component_filter,
        candidate_k=fetch_k
    )

    # Cross-Encoder Reranker postprocessor with CPU Latency Safeguards
    node_postprocessors = []
    if use_reranker:
        try:
            import torch
            # Optimize PyTorch CPU intra-op thread parallelism to reduce evaluation latency
            num_threads = min(4, max(1, (os.cpu_count() or 4) // 2))
            if torch.get_num_threads() != num_threads:
                torch.set_num_threads(num_threads)
        except Exception:
            pass

        try:
            from llama_index.core.postprocessor import SentenceTransformerRerank
            from llama_index.core.postprocessor.types import BaseNodePostprocessor

            class AdaptiveCandidateTrimmer(BaseNodePostprocessor):
                """Bound the candidate pool fed to Cross-Encoder to preserve interactive latency on CPU."""
                max_rerank_pool: int = 12

                def _postprocess_nodes(self, nodes, query_bundle=None):
                    return nodes[:self.max_rerank_pool]

            # 1. First trim candidate pool to top 12 to bound CPU cross-encoder runtime
            node_postprocessors.append(AdaptiveCandidateTrimmer(max_rerank_pool=max(int(top_k) * 2, 12)))

            # 2. Re-rank top 12 candidates using Cross-Encoder neural scoring
            node_postprocessors.append(
                SentenceTransformerRerank(
                    model=RERANKER_MODEL,
                    top_n=int(top_k)
                )
            )
        except Exception as err:
            print(f"⚠️ Note loading SentenceTransformerRerank ({err}).")

    # Fallback node trimmer when reranker is bypassed so top_k is always honored
    if not node_postprocessors:
        try:
            from llama_index.core.postprocessor.types import BaseNodePostprocessor
            class TopKTrimmer(BaseNodePostprocessor):
                limit: int
                def _postprocess_nodes(self, nodes, query_bundle=None):
                    return nodes[:self.limit]
            node_postprocessors.append(TopKTrimmer(limit=int(top_k)))
        except Exception:
            pass

    system_prompt = get_system_prompt_for_role(user_role)

    chat_engine = ContextChatEngine.from_defaults(
        retriever=hybrid_retriever,
        memory=session_memory,
        system_prompt=system_prompt,
        node_postprocessors=node_postprocessors,
        llm=session_llm
    )
    
    total_chunks = chroma_collection.count()
    return chat_engine, total_chunks
