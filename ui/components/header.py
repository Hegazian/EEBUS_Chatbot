"""
EEBUS Engineering Platform — Header Banner Component
"""
import gradio as gr


def render_header(total_chunks: int = 0):
    """Render the high-tech header banner with live telemetry status pills."""
    with gr.Row(elem_id="header-block"):
        with gr.Column():
            gr.HTML("<div class='header-title'>⚡ EEBUS Engineering Platform</div>")
            gr.HTML(
                "<div class='header-subtitle'>"
                "Industrial AI & Developer Suite for <strong>SHIP</strong> (Smart High-level Interface Protocol), "
                "<strong>SPINE</strong> (Smart Premises Interoperable Neutral-Message Exchange), "
                "and <strong>EEBUS Energy Use Cases</strong>. Featuring W3C schema validation, interactive protocol state machines, "
                "role-tailored engineering directives, and session-isolated hybrid RAG."
                "</div>"
            )
            gr.HTML(
                f"""
                <div class='header-badge-strip'>
                    <span class='status-pill'>🟢 ChromaDB Online ({total_chunks:,} chunks)</span>
                    <span class='status-pill' style='background:rgba(6, 182, 212, 0.15); border-color:rgba(6, 182, 212, 0.4); color:#38bdf8;'>⚡ Hybrid RAG (BGE + BM25)</span>
                    <span class='tech-badge'>SHIP TS 1.1.0</span>
                    <span class='tech-badge'>SPINE TS 1.3.0</span>
                    <span class='tech-badge'>EEBUS Use Cases</span>
                    <span class='tech-badge'>MS-MARCO Reranker</span>
                    <span class='tech-badge'>W3C Datagram Inspector</span>
                    <span class='tech-badge'>5 Engineering Roles</span>
                </div>
                """
            )
