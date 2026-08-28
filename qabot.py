"""
EEBUS Protocol Expert — Industrial Engineering Platform (Phase 4)
==================================================================
Multi-Tab Production Workspace:
- Tab 1: 💬 Protocol Expert Chat (Per-session memory isolated RAG assistant)
- Tab 2: 🔬 SPINE Datagram Inspector (W3C Schema validation & AI error diagnosis)
- Tab 3: 🔄 Protocol State Machines (Interactive SHIP SME & SPINE lifecycles)
- Tab 4: 📊 Benchmark & Telemetry (25-query evaluation suite & live knowledge stats)
"""

import os
import sys
import argparse
import warnings
from dotenv import load_dotenv

warnings.filterwarnings("ignore")
load_dotenv(override=True)

import chromadb
import gradio as gr

from core.config import (
    PERSIST_DIR, COLLECTION_NAME, DEFAULT_RETRIEVER_K, DEFAULT_TEMPERATURE,
    CATEGORIZED_QUESTIONS
)
from core.engine import create_chat_engine
from core.parsers import is_clean_node
from tools.validator import (
    validate_spine_datagram, get_sample_datagrams, diagnose_datagram_error
)
from tools.state_machine import get_state_machine_data, STATE_MACHINES
from tests.evaluate_rag import run_rag_benchmark, generate_markdown_report


# ─── Source Citation Formatter ──────────────────────────────────────────────────

def format_sources_html(source_nodes) -> str:
    """Format retrieved source nodes into rich HTML citation cards with glowing component badges."""
    if not source_nodes:
        return "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*No sources retrieved for this turn*</div>"

    seen = set()
    cards = []
    
    type_badges = {
        "SHIP": "background:rgba(6, 182, 212, 0.15); color:#06b6d4; border:1px solid rgba(6, 182, 212, 0.3);",
        "SPINE": "background:rgba(139, 92, 246, 0.15); color:#a78bfa; border:1px solid rgba(139, 92, 246, 0.3);",
        "UseCase": "background:rgba(16, 185, 129, 0.15); color:#34d399; border:1px solid rgba(16, 185, 129, 0.3);",
        "General": "background:rgba(100, 116, 139, 0.15); color:#cbd5e1; border:1px solid rgba(100, 116, 139, 0.3);"
    }

    icons = {
        "pdf": "📄",
        "schema": "📐",
        "markdown": "📝",
        "xml_example": "📋",
        "text": "📃"
    }

    for idx, node in enumerate(source_nodes, 1):
        metadata = node.metadata or {}
        filename = metadata.get("filename", "Unknown Document")
        
        snippet = node.node.get_content().strip() if hasattr(node, "node") else getattr(node, "text", "")
        if not is_clean_node(snippet):
            continue

        schema_name = metadata.get("schema_element_name")
        item_key = f"{filename}::{schema_name}" if schema_name else filename
        if item_key in seen:
            continue
        seen.add(item_key)

        component = metadata.get("component", "General")
        page = metadata.get("page_label", "")
        file_type = metadata.get("file_type", "pdf")
        icon = icons.get(file_type, "📄")
        badge_style = type_badges.get(component, type_badges["General"])
        
        if len(snippet) > 480:
            snippet = snippet[:480] + "..."

        page_str = f"<span style='color:#94a3b8; font-size:0.8em; margin-left:6px;'>Page {page}</span>" if page else ""
        elem_str = f"<span style='color:#38bdf8; font-size:0.8em; margin-left:6px;'>Type: {schema_name}</span>" if schema_name else ""
        
        score_val = getattr(node, "score", None)
        score_badge = f"<span style='color:#38bdf8; font-size:0.75em; margin-left:auto;'>Score: {score_val:.2f}</span>" if score_val is not None else ""

        card_html = f"""
<div style="background:#0f172a; border:1px solid #1e293b; border-radius:12px; padding:12px; margin-bottom:10px; transition:all 0.2s ease;">
    <div style="display:flex; justify-content:space-between; align-items:center; gap:8px;">
        <span style="font-weight:600; font-size:0.88em; color:#e2e8f0; display:flex; align-items:center; gap:6px;">
            <span>{icon}</span> {filename}
        </span>
        <span style="font-size:0.72em; font-weight:700; padding:2px 8px; border-radius:12px; {badge_style}">
            {component}
        </span>
    </div>
    <div style="margin-top:4px; font-size:0.78em; color:#94a3b8; display:flex; align-items:center;">
        {page_str}{elem_str}{score_badge}
    </div>
    <details style="margin-top:8px;">
        <summary style="cursor:pointer; color:#8b5cf6; font-size:0.8em; font-weight:600; user-select:none;">
            🔍 View Spec Passages
        </summary>
        <pre style="background:#080c14; color:#cbd5e1; font-family:'JetBrains Mono', monospace; font-size:0.75em; padding:10px; border-radius:8px; margin-top:6px; border:1px solid #1e293b; white-space:pre-wrap; max-height:180px; overflow-y:auto; line-height:1.4;">{snippet}</pre>
    </details>
</div>
"""
        cards.append(card_html)

    return "".join(cards) if cards else "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Clean specification sources retrieved*</div>"


# ─── Response Streamer (Session-Isolated) ──────────────────────────────────────

def stream_respond(
    message: str,
    history: list,
    session: dict,
    temperature: float,
    top_k: int,
    llm_provider: str,
    api_key: str,
    component_filter: str = "All Specifications",
    use_reranker: bool = True
):
    """Process user message and stream response using per-session isolated ChatEngine."""
    if not message.strip():
        yield "", history, "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>", session
        return

    if history is None:
        history = []

    if session is None:
        session = {}

    engine = session.get("engine")
    
    needs_rebuild = (
        engine is None
        or session.get("temperature") != temperature
        or session.get("top_k") != int(top_k)
        or session.get("llm_provider") != llm_provider
        or session.get("api_key") != api_key
        or session.get("component_filter") != component_filter
        or session.get("use_reranker") != use_reranker
    )

    if needs_rebuild:
        try:
            engine, _ = create_chat_engine(
                temperature=temperature,
                top_k=int(top_k),
                llm_provider=llm_provider,
                api_key=api_key,
                component_filter=component_filter,
                use_reranker=use_reranker
            )
            session["engine"] = engine
            session["temperature"] = temperature
            session["top_k"] = int(top_k)
            session["llm_provider"] = llm_provider
            session["api_key"] = api_key
            session["component_filter"] = component_filter
            session["use_reranker"] = use_reranker

            if history:
                try:
                    from llama_index.core.llms import ChatMessage, MessageRole
                    messages = []
                    for m in history:
                        role = MessageRole.USER if m["role"] == "user" else MessageRole.ASSISTANT
                        messages.append(ChatMessage(role=role, content=m["content"]))
                    if hasattr(engine, "_memory"):
                        engine._memory.set(messages)
                    elif hasattr(engine, "memory"):
                        engine.memory.set(messages)
                except Exception:
                    pass
        except Exception as e:
            history.append({"role": "user", "content": message})
            history.append({"role": "assistant", "content": f"⚠️ Configuration Error: {str(e)}"})
            yield "", history, f"<div style='color:#ef4444; font-size:0.85em;'>⚠️ Config Error</div>", session
            return

    history.append({"role": "user", "content": message})
    history.append({"role": "assistant", "content": "..."})
    yield "", history, "<div style='color:#06b6d4; font-size:0.85em; padding:8px;'>⚡ Searching EEBUS specifications & generating response...</div>", session

    try:
        streaming_response = engine.stream_chat(message)
        accumulated_text = ""
        sources_formatted = False
        sources_html = ""

        for token in streaming_response.response_gen:
            accumulated_text += token
            history[-1]["content"] = accumulated_text
            
            if not sources_formatted and hasattr(streaming_response, "source_nodes") and streaming_response.source_nodes:
                sources_html = format_sources_html(streaming_response.source_nodes)
                sources_formatted = True
                
            yield "", history, sources_html or "<div style='color:#64748b; font-size:0.88em; padding:8px;'>⚡ Synthesizing technical answer...</div>", session

        if hasattr(streaming_response, "source_nodes") and streaming_response.source_nodes:
            sources_html = format_sources_html(streaming_response.source_nodes)
            
        yield "", history, sources_html, session

    except Exception as err:
        err_str = f"⚠️ An error occurred while generating response: {str(err)}"
        if history:
            history[-1]["content"] = err_str
        yield "", history, "<div style='color:#ef4444; font-size:0.85em;'>⚠️ Generation error</div>", session


# ─── Datagram Inspector Handler ─────────────────────────────────────────────────

def inspect_datagram_handler(xml_text: str, session: dict):
    """Validate SPINE Datagram and trigger AI compliance diagnosis if invalid."""
    if not xml_text or not xml_text.strip():
        badge = "<div style='color:#f87171; font-weight:700;'>⚠️ Please provide an XML datagram.</div>"
        return badge, "No input provided.", "", "", session

    validation = validate_spine_datagram(xml_text)
    is_valid = validation.get("is_valid", False)

    if is_valid:
        badge = """
<div style="background:rgba(16, 185, 129, 0.15); border:1px solid rgba(16, 185, 129, 0.4); padding:10px 16px; border-radius:10px; color:#34d399; font-weight:700; font-size:0.95em; display:flex; align-items:center; gap:8px;">
    <span>✅</span> SPINE TS 1.3.0 SCHEMA COMPLIANT
</div>"""
        err_details = "✨ No schema violations detected. Datagram is 100% valid."
        ai_diag = "✅ **Validation Passed**: All header elements, addressing formats, and command payloads adhere strictly to `EEBus_SPINE_TS_Datagram.xsd` and associated feature definitions."
    else:
        err_type = validation.get("error_type", "Validation Error")
        err_path = validation.get("error_path") or "Root"
        err_line = validation.get("line_number") or "N/A"
        err_msg = validation.get("error_message", "")
        
        badge = f"""
<div style="background:rgba(239, 68, 68, 0.15); border:1px solid rgba(239, 68, 68, 0.4); padding:10px 16px; border-radius:10px; color:#f87171; font-weight:700; font-size:0.95em; display:flex; align-items:center; gap:8px;">
    <span>❌</span> {err_type.upper()}
</div>"""
        err_details = f"**Error Path:** `{err_path}`  \n**Line Number:** `{err_line}`  \n**Violation:** {err_msg}"
        
        # Trigger AI diagnosis using session engine
        engine = session.get("engine") if session else None
        if not engine:
            try:
                engine, _ = create_chat_engine()
                if session:
                    session["engine"] = engine
            except Exception:
                pass
        
        if engine:
            ai_diag = diagnose_datagram_error(xml_text, validation, engine)
        else:
            ai_diag = "⚠️ AI diagnostic engine unavailable. Please review the schema error path above."

    # Semantic Breakdown
    header = validation.get("header", {})
    addr_src = header.get("addressSource") or {}
    addr_dst = header.get("addressDestination") or {}
    funcs = validation.get("functions", [])
    
    semantic_md = f"""
### 📋 Semantic Header & Payload Summary
| Field | Extracted Value | Specification Requirement |
| :--- | :--- | :--- |
| **Specification Version** | `{header.get('specificationVersion') or 'N/A'}` | Must match active version (1.3.0) |
| **Command Classifier** | `{header.get('cmdClassifier') or 'N/A'}` | read, reply, notify, write, call, result |
| **Message Counter** | `{header.get('msgCounter') or 'N/A'}` | Positive monotonic integer |
| **Address Source** | `{addr_src.get('device') or 'N/A'} : E{addr_src.get('entity') or '-'} : F{addr_src.get('feature') or '-'}` | Valid SPINE URI & feature address |
| **Address Destination** | `{addr_dst.get('device') or 'N/A'} : E{addr_dst.get('entity') or '-'} : F{addr_dst.get('feature') or '-'}` | Valid SPINE URI & feature address |
| **Target Function Sets** | `{', '.join(funcs) if funcs else 'None'}` | Recognized SPINE Function Set |
"""
    return badge, err_details, semantic_md, ai_diag, session


# ─── State Machine View Formatter ───────────────────────────────────────────────

def format_state_machine_view(machine_key: str):
    """Generate Mermaid diagram and state transition table for chosen state machine."""
    data = get_state_machine_data(machine_key)
    
    mermaid_html = f"""
<div class="mermaid-box" style="background:#0b1120; border:1px solid #1e3a5f; border-radius:14px; padding:20px; margin-bottom:16px; overflow-x:auto;">
    <script type="module">
        import mermaid from 'https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs';
        mermaid.initialize({{ startOnLoad: true, theme: 'dark' }});
    </script>
    <pre class="mermaid">
{data['mermaid']}
    </pre>
</div>
"""
    
    info_md = f"""
### {data['title']}
**Specification Reference:** `{data['standard']}`

{data['description']}

#### 🔄 State Transition Rules & Timeout Matrix
| State Identifier | Protocol Phase | Trigger Event | Timeout Timer | Specification Description |
| :--- | :--- | :--- | :--- | :--- |
"""
    for s in data["states"]:
        info_md += f"| `{s['state']}` | **{s['phase']}** | {s['trigger']} | `{s['timeout']}` | {s['description']} |\n"

    return mermaid_html, info_md


# ─── Ultra-Enhanced Gradio CSS ──────────────────────────────────────────────────

CUSTOM_CSS = """
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700;800&family=JetBrains+Mono:wght@400;500&display=swap');

:root {
    --bg-base: #080c14;
    --bg-panel: #0f172a;
    --bg-card: #1e293b;
    --border-color: #1e3a5f;
    --primary-cyan: #06b6d4;
    --accent-purple: #8b5cf6;
    --text-bright: #f8fafc;
    --text-dim: #94a3b8;
}

body, .gradio-container {
    background-color: var(--bg-base) !important;
    font-family: 'Inter', system-ui, sans-serif !important;
    color: var(--text-bright) !important;
}

.gradio-container {
    max-width: 1440px !important;
    padding-top: 16px !important;
}

#header-block {
    background: linear-gradient(135deg, #0b1329 0%, #1e1b4b 50%, #0b1329 100%);
    border: 1px solid var(--border-color);
    border-radius: 20px;
    padding: 24px 36px;
    margin-bottom: 14px;
    box-shadow: 0 10px 30px -10px rgba(6, 182, 212, 0.15);
    position: relative;
    overflow: hidden;
}

#header-block::before {
    content: '';
    position: absolute;
    top: -50%;
    right: -10%;
    width: 380px;
    height: 380px;
    background: radial-gradient(circle, rgba(6, 182, 212, 0.18) 0%, transparent 70%);
    pointer-events: none;
}

.header-title {
    font-size: 2.1em !important;
    font-weight: 800 !important;
    letter-spacing: -0.5px;
    background: linear-gradient(90deg, #38bdf8, #818cf8, #c084fc);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    margin-bottom: 6px !important;
}

.header-subtitle {
    color: var(--text-dim) !important;
    font-size: 0.96em !important;
    line-height: 1.5;
}

.badge-strip {
    display: flex;
    gap: 8px;
    margin-top: 12px;
    flex-wrap: wrap;
}

.tech-badge {
    background: rgba(15, 23, 42, 0.8);
    border: 1px solid rgba(6, 182, 212, 0.3);
    color: #38bdf8;
    padding: 4px 10px;
    border-radius: 8px;
    font-size: 0.76em;
    font-weight: 600;
    letter-spacing: 0.5px;
    text-transform: uppercase;
}

#chatbot {
    background: #0b1120 !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 16px !important;
    box-shadow: 0 4px 20px rgba(0, 0, 0, 0.3) !important;
    min-height: 520px !important;
}

#chatbot .message.user {
    background: linear-gradient(135deg, #1e3a8a, #3b82f6) !important;
    color: #ffffff !important;
    border-radius: 14px 14px 2px 14px !important;
    font-weight: 500;
}

#chatbot .message.bot {
    background: #111827 !important;
    border: 1px solid #1f2937 !important;
    color: #f3f4f6 !important;
    border-radius: 14px 14px 14px 2px !important;
    line-height: 1.6;
}

#msg-input textarea, #datagram-input textarea {
    background: #0f172a !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 12px !important;
    color: var(--text-bright) !important;
    font-size: 0.92em !important;
    font-family: 'JetBrains Mono', monospace !important;
}

#msg-input textarea:focus, #datagram-input textarea:focus {
    border-color: var(--primary-cyan) !important;
    box-shadow: 0 0 0 2px rgba(6, 182, 212, 0.2) !important;
}

.primary-btn {
    background: linear-gradient(135deg, #06b6d4, #3b82f6) !important;
    border: none !important;
    color: white !important;
    font-weight: 700 !important;
    border-radius: 12px !important;
    transition: all 0.2s ease !important;
}

.primary-btn:hover {
    transform: translateY(-1px) !important;
    box-shadow: 0 4px 12px rgba(6, 182, 212, 0.4) !important;
}

.secondary-btn {
    background: #1e293b !important;
    border: 1px solid #334155 !important;
    color: #94a3b8 !important;
    font-weight: 600 !important;
    border-radius: 12px !important;
    transition: all 0.2s ease !important;
}

.secondary-btn:hover {
    background: #334155 !important;
    color: #f8fafc !important;
}

#sources-display {
    background: #0b1120 !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 14px !important;
    padding: 12px !important;
    max-height: 520px !important;
    overflow-y: auto !important;
}

#stats-display {
    background: #0b1120 !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 14px !important;
    padding: 12px 16px !important;
    font-size: 0.85em !important;
}

.prompt-chip {
    background: rgba(15, 23, 42, 0.7) !important;
    border: 1px solid #1e293b !important;
    color: #cbd5e1 !important;
    border-radius: 8px !important;
    padding: 6px 12px !important;
    font-size: 0.82em !important;
    text-align: left !important;
    transition: all 0.15s ease !important;
    margin-bottom: 6px !important;
    width: 100% !important;
    white-space: normal !important;
    height: auto !important;
    min-height: 42px !important;
    line-height: 1.3 !important;
}

.prompt-chip:hover {
    border-color: var(--primary-cyan) !important;
    background: rgba(6, 182, 212, 0.1) !important;
    color: #38bdf8 !important;
    transform: translateY(-1px) !important;
}

.chip-category-title {
    font-size: 0.75em;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 0.5px;
    color: #8b5cf6;
    margin-bottom: 6px;
}

.sidebar-label {
    font-size: 0.78em;
    font-weight: 700;
    letter-spacing: 0.5px;
    color: #94a3b8;
    margin-bottom: 8px;
}
"""


# ─── Gradio UI Builder ─────────────────────────────────────────────────────────

def build_ui():
    """Construct multi-tab industrial Gradio platform."""
    total_chunks = 0
    try:
        db = chromadb.PersistentClient(path=PERSIST_DIR)
        total_chunks = db.get_collection(COLLECTION_NAME).count()
    except Exception:
        pass

    sample_dict = get_sample_datagrams()

    with gr.Blocks(title="EEBUS Engineering Platform", css=CUSTOM_CSS, theme=gr.themes.Base()) as demo:
        
        # Per-Session State
        session_state = gr.State(lambda: {
            "engine": None,
            "temperature": DEFAULT_TEMPERATURE,
            "top_k": DEFAULT_RETRIEVER_K,
            "llm_provider": "Gemini (Google)",
            "api_key": "",
            "component_filter": "All Specifications",
            "use_reranker": True
        })

        # Header Block
        with gr.Row(elem_id="header-block"):
            with gr.Column():
                gr.HTML("<div class='header-title'>⚡ EEBUS Engineering Platform</div>")
                gr.HTML(
                    "<div class='header-subtitle'>"
                    "Industrial AI & Developer Suite for <strong>SHIP</strong>, <strong>SPINE</strong>, "
                    "and <strong>EEBUS Use Cases</strong>. Featuring schema validation, state machine visualizers, "
                    "and session-isolated retrieval augmented generation."
                    "</div>"
                )
                gr.HTML(
                    "<div class='badge-strip'>"
                    "<span class='tech-badge'>SHIP TS 1.1.0</span>"
                    "<span class='tech-badge'>SPINE TS 1.3.0</span>"
                    "<span class='tech-badge'>Datagram Inspector</span>"
                    "<span class='tech-badge'>State Machine Visualizer</span>"
                    "<span class='tech-badge'>Hybrid BM25 + BGE</span>"
                    "<span class='tech-badge'>MS-MARCO Reranker</span>"
                    "</div>"
                )

        # ─── Navigation Tabs ───────────────────────────────────────────────────

        with gr.Tabs():

            # ── TAB 1: PROTOCOL EXPERT CHAT ───────────────────────────────────
            with gr.TabItem("💬 Protocol Expert Chat", id="tab_chat"):
                with gr.Row():
                    with gr.Column(scale=3):
                        chatbot = gr.Chatbot(elem_id="chatbot", show_label=False)
                        
                        with gr.Row():
                            msg = gr.Textbox(
                                elem_id="msg-input",
                                placeholder="Ask about EEBUS specifications, SME state flow, SPINE resources, XSD types...",
                                show_label=False,
                                scale=6,
                                lines=1,
                                max_lines=4,
                            )
                            send_btn = gr.Button("Send ⚡", elem_classes=["primary-btn"], scale=1)
                            clear_btn = gr.Button("Clear 🗑️", elem_classes=["secondary-btn"], scale=1)

                        with gr.Accordion("⚙️ RAG Engine Settings", open=False):
                            with gr.Row():
                                llm_provider_dropdown = gr.Dropdown(
                                    choices=["Gemini (Google)", "ChatGPT (OpenAI)", "Claude (Anthropic)"], 
                                    value="Gemini (Google)", 
                                    label="🤖 LLM Provider"
                                )
                                component_filter_dropdown = gr.Dropdown(
                                    choices=["All Specifications", "SHIP (Transport)", "SPINE (Application)", "Use Cases"],
                                    value="All Specifications",
                                    label="🎯 Specification Scope Filter"
                                )
                            with gr.Row():
                                api_key_input = gr.Textbox(
                                    type="password", 
                                    placeholder="Optional: Override .env key...", 
                                    label="🔑 API Key"
                                )
                                reranker_checkbox = gr.Checkbox(
                                    value=True,
                                    label="⚡ Cross-Encoder Reranking (MS-MARCO Precision Boost)"
                                )
                            with gr.Row():
                                temp_slider = gr.Slider(
                                    minimum=0.0, maximum=1.0, value=DEFAULT_TEMPERATURE, step=0.05,
                                    label="LLM Temperature (Creativity)"
                                )
                                top_k_slider = gr.Slider(
                                    minimum=3, maximum=12, value=DEFAULT_RETRIEVER_K, step=1,
                                    label="Top-K Spec Passages Retrieved"
                                )

                    with gr.Column(scale=1, min_width=300):
                        gr.HTML("<div class='sidebar-label'>📚 RETRIEVED CITATIONS</div>")
                        sources_display = gr.HTML(
                            value="<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>",
                            elem_id="sources-display",
                        )
                        
                        gr.HTML("<div class='sidebar-label' style='margin-top:16px'>📊 KNOWLEDGE BASE</div>")
                        stats_display = gr.Markdown(
                            value=(
                                f"**Index Chunks:** `{total_chunks:,}`\n\n"
                                f"**Embeddings:** `BAAI/bge-small-en-v1.5`\n\n"
                                f"**Retriever:** `Hybrid (Dense BGE + Sparse BM25)`\n\n"
                                f"**Reranker:** `Cross-Encoder MS-MARCO`\n\n"
                                f"**Isolation:** `Per-Session gr.State`\n\n"
                                f"**Mode:** `Token Streaming ⚡`"
                            ),
                            elem_id="stats-display",
                        )

                settings_inputs = [
                    temp_slider,
                    top_k_slider,
                    llm_provider_dropdown,
                    api_key_input,
                    component_filter_dropdown,
                    reranker_checkbox
                ]

                gr.HTML("<div class='sidebar-label' style='margin-top:12px;'>💡 QUICK SPECIFICATION PROMPTS</div>")
                with gr.Row():
                    for cat_title, questions in CATEGORIZED_QUESTIONS.items():
                        with gr.Column(scale=1):
                            gr.HTML(f"<div class='chip-category-title'>{cat_title}</div>")
                            for q in questions:
                                btn = gr.Button(q, size="sm", elem_classes=["prompt-chip"])
                                btn.click(
                                    fn=lambda question=q: question, outputs=[msg]
                                ).then(
                                    fn=stream_respond,
                                    inputs=[msg, chatbot, session_state] + settings_inputs,
                                    outputs=[msg, chatbot, sources_display, session_state]
                                )

                def clear_history(session: dict):
                    if session and session.get("engine"):
                        try:
                            session["engine"].reset()
                        except Exception:
                            pass
                    return [], "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>", session

                submit_args = dict(
                    fn=stream_respond,
                    inputs=[msg, chatbot, session_state] + settings_inputs,
                    outputs=[msg, chatbot, sources_display, session_state]
                )

                msg.submit(**submit_args)
                send_btn.click(**submit_args)
                clear_btn.click(fn=clear_history, inputs=[session_state], outputs=[chatbot, sources_display, session_state])

            # ── TAB 2: SPINE DATAGRAM INSPECTOR ───────────────────────────────
            with gr.TabItem("🔬 SPINE Datagram Inspector", id="tab_inspector"):
                gr.HTML("<div style='margin-bottom:12px; color:#94a3b8;'>Validate SPINE XML datagrams against <code>EEBus_SPINE_TS_Datagram.xsd</code>, inspect address headers, and generate AI compliance fixes.</div>")
                
                with gr.Row():
                    with gr.Column(scale=1):
                        sample_dropdown = gr.Dropdown(
                            choices=list(sample_dict.keys()),
                            label="📁 Load Curated Sample Datagram",
                            value=list(sample_dict.keys())[0]
                        )
                        datagram_input = gr.Textbox(
                            value=sample_dict[list(sample_dict.keys())[0]],
                            lines=16,
                            label="SPINE XML Datagram Payload",
                            elem_id="datagram-input"
                        )
                        with gr.Row():
                            validate_btn = gr.Button("Validate & Diagnose ⚡", elem_classes=["primary-btn"], scale=2)
                            clear_val_btn = gr.Button("Clear", elem_classes=["secondary-btn"], scale=1)

                    with gr.Column(scale=1):
                        gr.HTML("<div class='sidebar-label'>🛡️ VALIDATION STATUS</div>")
                        status_badge = gr.HTML(
                            value="<div style='color:#64748b; font-size:0.9em; padding:8px;'>*Click Validate to run W3C schema check*</div>"
                        )
                        error_box = gr.Markdown(value="*No errors detected.*")
                        semantic_box = gr.Markdown(value="*Semantic header analysis will appear here.*")
                        
                        gr.HTML("<div class='sidebar-label' style='margin-top:14px;'>🤖 AI COMPLIANCE DIAGNOSIS & REPAIR</div>")
                        ai_diag_box = gr.Markdown(value="*AI explanation and corrected payload will appear here upon error.*")

                sample_dropdown.change(
                    fn=lambda k: sample_dict.get(k, ""),
                    inputs=[sample_dropdown],
                    outputs=[datagram_input]
                )

                validate_btn.click(
                    fn=inspect_datagram_handler,
                    inputs=[datagram_input, session_state],
                    outputs=[status_badge, error_box, semantic_box, ai_diag_box, session_state]
                )

                clear_val_btn.click(
                    fn=lambda: ("", "<div style='color:#64748b; font-size:0.9em;'>*Ready*</div>", "", "", ""),
                    outputs=[datagram_input, status_badge, error_box, semantic_box, ai_diag_box]
                )

            # ── TAB 3: PROTOCOL STATE MACHINES ────────────────────────────────
            with gr.TabItem("🔄 Protocol State Machines", id="tab_state_machines"):
                gr.HTML("<div style='margin-bottom:12px; color:#94a3b8;'>Interactive lifecycle models for SHIP Connection Handshake and SPINE Subscriptions.</div>")
                
                sm_dropdown = gr.Dropdown(
                    choices=[
                        ("🔌 SHIP SME (Connection Handshake State Machine)", "ship_sme"),
                        ("🧱 SPINE Subscription Lifecycle", "spine_subscription"),
                        ("🔗 SPINE Binding Lifecycle", "spine_binding")
                    ],
                    value="ship_sme",
                    label="🎯 Select Protocol Lifecycle Model"
                )
                
                initial_mermaid, initial_info = format_state_machine_view("ship_sme")
                
                mermaid_display = gr.HTML(value=initial_mermaid)
                info_display = gr.Markdown(value=initial_info)

                sm_dropdown.change(
                    fn=format_state_machine_view,
                    inputs=[sm_dropdown],
                    outputs=[mermaid_display, info_display]
                )

            # ── TAB 4: BENCHMARK & TELEMETRY ──────────────────────────────────
            with gr.TabItem("📊 Benchmark & Telemetry", id="tab_telemetry"):
                gr.HTML("<div style='margin-bottom:12px; color:#94a3b8;'>Automated RAG evaluation scorecard across 25 ground-truth technical queries.</div>")
                
                with gr.Row():
                    bench_btn = gr.Button("Run Live Benchmark Suite (25 Queries) 🚀", elem_classes=["primary-btn"], scale=1)
                
                # Check for existing report
                existing_report = "*Click the button above to execute the automated benchmark suite.*"
                report_file = os.path.join(os.path.dirname(__file__), "tests", "benchmark_report.md")
                if os.path.exists(report_file):
                    try:
                        with open(report_file, "r", encoding="utf-8") as f:
                            existing_report = f.read()
                    except Exception:
                        pass
                
                benchmark_results = gr.Markdown(value=existing_report)

                def run_benchmark_handler():
                    scorecard = run_rag_benchmark(eval_top_k=5)
                    return generate_markdown_report(scorecard)

                bench_btn.click(
                    fn=run_benchmark_handler,
                    outputs=[benchmark_results]
                )

    return demo


# ─── Main Entry Point ───────────────────────────────────────────────────────────

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="EEBUS Engineering Platform")
    parser.add_argument("--host", type=str, default="127.0.0.1", help="Host IP to bind (default: 127.0.0.1)")
    parser.add_argument("--port", type=int, default=7860, help="Port number (default: 7860)")
    parser.add_argument("--share", action="store_true", help="Create a public Gradio share link")
    args = parser.parse_args()

    if os.path.exists(PERSIST_DIR):
        try:
            db = chromadb.PersistentClient(path=PERSIST_DIR)
            count = db.get_collection(COLLECTION_NAME).count()
            print(f"\n✅ Ready — {count:,} LlamaIndex chunks loaded from ChromaDB & BM25.")
        except Exception:
            count = 0
        print(f"🌐 Launching EEBUS Engineering Platform on http://{args.host}:{args.port} (share={args.share})\n")
        build_ui().launch(server_name=args.host, server_port=args.port, share=args.share)
    else:
        print("\n❌ Failed to find database. Please run python eebus_ingest.py --force first.")