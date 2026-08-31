"""
EEBUS Engineering Platform — Knowledge Base Telemetry Sidebar
"""
import gradio as gr


def render_knowledge_stats(total_chunks: int = 0):
    """Render sidebar telemetry metrics for indexed specification chunks."""
    gr.HTML("<div class='sidebar-label' style='margin-top:16px'>📊 KNOWLEDGE BASE</div>")
    stats_md = gr.Markdown(
        value=(
            f"**Index Chunks:** `{total_chunks:,}`\n\n"
            f"**Embeddings:** `BAAI/bge-small-en-v1.5`\n\n"
            f"**Retriever:** `Hybrid (Dense BGE + Sparse BM25)`\n\n"
            f"**Reranker:** `Cross-Encoder MS-MARCO`\n\n"
            f"**Active Personas:** `5 Tailored Engineering Roles`\n\n"
            f"**Isolation:** `Per-Session Memory Buffer`\n\n"
            f"**Mode:** `Token Streaming ⚡`"
        ),
        elem_id="stats-display",
    )
    return stats_md
