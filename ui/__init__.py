"""
EEBUS Engineering Platform — UI Package
Exports build_ui() to instantiate the complete Gradio interface.
"""
import chromadb
import gradio as gr

from core.config import (
    PERSIST_DIR, COLLECTION_NAME, DEFAULT_RETRIEVER_K, DEFAULT_TEMPERATURE,
    DEFAULT_USER_ROLE
)
from .styles import CUSTOM_CSS
from .head import HEAD_HTML
from .components import render_header
from .tabs import (
    create_chat_tab,
    create_inspector_tab,
    create_state_machines_tab,
    create_benchmark_tab
)


def build_ui():
    """Construct multi-tab industrial Gradio platform with modular components."""
    total_chunks = 0
    try:
        db = chromadb.PersistentClient(path=PERSIST_DIR)
        total_chunks = db.get_collection(COLLECTION_NAME).count()
    except Exception:
        pass

    with gr.Blocks(title="EEBUS Engineering Platform") as demo:
        
        # Per-Session State
        session_state = gr.State(lambda: {
            "engine": None,
            "temperature": DEFAULT_TEMPERATURE,
            "top_k": DEFAULT_RETRIEVER_K,
            "llm_provider": "Gemini (Google)",
            "api_key": "",
            "component_filter": "All Specifications",
            "use_reranker": True,
            "user_role": DEFAULT_USER_ROLE
        })

        # Header Component
        render_header(total_chunks)

        # Tab Navigation
        with gr.Tabs():
            create_chat_tab(session_state, total_chunks)
            create_inspector_tab(session_state)
            create_state_machines_tab()
            create_benchmark_tab()

        # Client-side Mermaid initialization on page load
        demo.load(js="() => { setTimeout(() => { if (window.mermaid) window.mermaid.run(); }, 350); }")

    return demo


__all__ = ["build_ui", "CUSTOM_CSS", "HEAD_HTML"]
