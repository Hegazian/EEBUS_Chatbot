"""
EEBUS Protocol Expert — RAG Chatbot (Ultra-Enhanced Production UI)
===================================================================
Gemini-powered chatbot that answers developer questions about the EEBUS
protocol stack (SHIP, SPINE, Use Cases, XSD schemas) using LlamaIndex.

Features:
- Noise Filtering on Retrieved Spec Nodes.
- 1-Click Auto-Submit for Quick Specification Prompts.
- Universal Gradio 3.x / 4.x / 5.x Compatibility.
- Premium Glassmorphism UI with ambient neon accents.
- Real-Time Token Streaming with response status badges.
- Expandable Citation Cards with glowing component badges (SHIP / SPINE / UseCase).
- Advanced RAG Settings Drawer (Temperature & Top-K Controls).
"""

import os
import sys
import time
import json
import argparse
import warnings
from dotenv import load_dotenv

warnings.filterwarnings("ignore")
load_dotenv(override=True)

import chromadb
import gradio as gr

from llama_index.core import VectorStoreIndex, Settings
from llama_index.core.memory import ChatMemoryBuffer
from llama_index.vector_stores.chroma import ChromaVectorStore
from llama_index.llms.gemini import Gemini
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
import google.generativeai as genai

# ─── Configuration ──────────────────────────────────────────────────────────────

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
PERSIST_DIR = os.path.join(BASE_DIR, "eebus_chroma_db")
CACHE_FILE = os.path.join(BASE_DIR, ".model_cache.json")
COLLECTION_NAME = "eebus_docs"
PRIMARY_EMBEDDING_MODEL = "BAAI/bge-small-en-v1.5"
FALLBACK_EMBEDDING_MODEL = "all-MiniLM-L6-v2"
DEFAULT_RETRIEVER_K = 6
DEFAULT_TEMPERATURE = 0.3
CACHE_TTL_HOURS = 24

# ─── Model Discovery & Caching ──────────────────────────────────────────────────

def select_best_model() -> str:
    """Dynamically discover available Gemini models with persistent caching."""
    api_key = os.getenv("GOOGLE_API_KEY")
    if not api_key:
        print("⚠️ GOOGLE_API_KEY not found in environment. Defaulting to gemini-flash-latest.")
        return "models/gemini-flash-latest"

    if os.path.exists(CACHE_FILE):
        try:
            with open(CACHE_FILE, "r", encoding="utf-8") as f:
                cache_data = json.load(f)
                cached_model = cache_data.get("model")
                cached_ts = cache_data.get("timestamp", 0)
                if cached_model and (time.time() - cached_ts) < (CACHE_TTL_HOURS * 3600):
                    print(f"🚀 Using cached active model: {cached_model}")
                    return cached_model
        except Exception:
            pass

    genai.configure(api_key=api_key)
    try:
        available = [m.name for m in genai.list_models() if "generateContent" in m.supported_generation_methods]
        print(f"\n📋 Discovered {len(available)} models for your API key.")
        
        candidates = [
            "models/gemini-flash-latest",
            "models/gemini-2.0-flash-lite",
            "models/gemini-2.5-flash-lite",
            "models/gemini-flash-lite-latest",
            "models/gemini-2.0-flash",
            "models/gemini-2.5-flash",
            "models/gemini-pro-latest",
            "models/gemini-3.6-flash"
        ]
        
        for m in available:
            if m not in candidates:
                candidates.append(m)
                
        print("🔍 Probing candidate models to find an active model...")
        for candidate in candidates:
            if candidate in available:
                try:
                    test_model = genai.GenerativeModel(candidate)
                    test_model.generate_content("test")
                    print(f"🎯 Selected active model: {candidate}\n")
                    try:
                        with open(CACHE_FILE, "w", encoding="utf-8") as f:
                            json.dump({"model": candidate, "timestamp": time.time()}, f)
                    except Exception:
                        pass
                    return candidate
                except Exception as err:
                    err_msg = str(err).split('\n')[0]
                    print(f"  ⚠️ Skipping {candidate} ({err_msg})")
                    continue
    except Exception as e:
        print(f"⚠️ Error querying models: {e}")
        
    return "models/gemini-flash-latest"

LLM_MODEL = select_best_model()

# ─── System Prompt ──────────────────────────────────────────────────────────────

SYSTEM_PROMPT = """\
You are an expert EEBUS protocol engineer and technical documentation assistant.
Your deep knowledge spans the entire EEBUS specification stack:

• **SHIP (Smart Home IP)** — The secure transport protocol: mDNS/DNS-SD discovery, \
TLS 1.2 mutual authentication, WebSocket binary framing, SME connection states \
(CMI → Hello → Protocol Handshake → PIN → Data Exchange → Termination), \
certificate management, key material updates, and SHIP commissioning.

• **SPINE** — The application-layer protocol: datagrams, command frames, \
function sets, binding & subscription management, and the full XSD-defined data model.

• **Use Cases** — Limitation of Power Consumption/Production, Monitoring of Grid \
Connection Point, etc.

─── RULES ───
1. Provide precise, technically accurate answers grounded ONLY in the retrieved context.
2. Reference specific spec sections, version numbers, and document names.
3. Use exact RFC 2119 terminology (SHALL, MUST, MAY, SHOULD) from the standards.
4. Include relevant data structures, message formats, state machines, and XSD types.
5. Distinguish clearly between SHIP (transport) and SPINE (application) concerns.
6. When discussing XSD schemas, provide element names, types, and cardinality.
7. Format code, message structures, and protocol flows in markdown code blocks.
8. Always cite the source documents used in your answer.
"""

# ─── Embedding Setup ────────────────────────────────────────────────────────────

def init_embedding_model():
    """Initialize embedding model matching eebus_ingest.py."""
    try:
        return HuggingFaceEmbedding(model_name=PRIMARY_EMBEDDING_MODEL)
    except Exception:
        return HuggingFaceEmbedding(model_name=FALLBACK_EMBEDDING_MODEL)

Settings.embed_model = init_embedding_model()
Settings.llm = Gemini(model=LLM_MODEL, temperature=DEFAULT_TEMPERATURE, max_tokens=4096)

# ─── Chat Engine Setup ──────────────────────────────────────────────────────────

def get_chat_engine(temperature: float = DEFAULT_TEMPERATURE, top_k: int = DEFAULT_RETRIEVER_K):
    """Load ChromaDB index and initialize the Context Chat Engine."""
    if not os.path.exists(PERSIST_DIR):
        raise FileNotFoundError(
            f"Vector store not found at {PERSIST_DIR}.\n"
            "Run 'python eebus_ingest.py' first to index the documentation."
        )

    db = chromadb.PersistentClient(path=PERSIST_DIR)
    chroma_collection = db.get_collection(COLLECTION_NAME)
    vector_store = ChromaVectorStore(chroma_collection=chroma_collection)
    
    index = VectorStoreIndex.from_vector_store(vector_store)
    memory = ChatMemoryBuffer.from_defaults(token_limit=16000)

    Settings.llm = Gemini(model=LLM_MODEL, temperature=temperature, max_tokens=4096)

    chat_engine = index.as_chat_engine(
        chat_mode="context",
        memory=memory,
        system_prompt=SYSTEM_PROMPT,
        similarity_top_k=int(top_k)
    )
    
    total_chunks = chroma_collection.count()
    return chat_engine, total_chunks

# Initialize startup engine
try:
    chat_engine, total_chunks = get_chat_engine()
except Exception as e:
    print(f"⚠️ Error initializing engine: {e}")
    chat_engine, total_chunks = None, 0


# ─── Text Noise Filter ──────────────────────────────────────────────────────────

def is_clean_node(text: str) -> bool:
    """Filter out raw PDF stream noise or binary garbage."""
    if not text or len(text.strip()) < 25:
        return False
    pdf_stream_markers = ["/Filter", "/FlateDecode", "/FontDescriptor", "%PDF-", "/XObject", "endstream", "endobj"]
    return sum(1 for m in pdf_stream_markers if m in text) < 2


# ─── Source Citation Helper ─────────────────────────────────────────────────────

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

        if filename in seen:
            continue
        seen.add(filename)

        component = metadata.get("component", "General")
        page = metadata.get("page_label", "")
        file_type = metadata.get("file_type", "pdf")
        icon = icons.get(file_type, "📄")
        badge_style = type_badges.get(component, type_badges["General"])
        
        if len(snippet) > 450:
            snippet = snippet[:450] + "..."

        page_str = f"<span style='color:#94a3b8; font-size:0.8em; margin-left:6px;'>Page {page}</span>" if page else ""

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
    <div style="margin-top:4px; font-size:0.78em; color:#94a3b8;">
        {page_str}
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


# ─── Response Streamer ──────────────────────────────────────────────────────────

def stream_respond(message: str, history: list, temperature: float, top_k: int):
    """Process message and stream response token-by-token using Gradio dict messages format."""
    if not message.strip():
        yield "", history, "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>"
        return

    if history is None:
        history = []

    if chat_engine is None:
        error_msg = "Error: Chat engine not initialized. Did you run `python eebus_ingest.py`?"
        history.append({"role": "user", "content": message})
        history.append({"role": "assistant", "content": error_msg})
        yield "", history, "❌ Engine offline"
        return

    history.append({"role": "user", "content": message})
    history.append({"role": "assistant", "content": "..."})
    yield "", history, "<div style='color:#06b6d4; font-size:0.85em; padding:8px;'>⚡ Searching EEBUS specifications & generating response...</div>"

    try:
        streaming_response = chat_engine.stream_chat(message)
        
        accumulated_text = ""
        sources_formatted = False
        sources_html = ""

        for token in streaming_response.response_gen:
            accumulated_text += token
            history[-1]["content"] = accumulated_text
            
            if not sources_formatted and hasattr(streaming_response, "source_nodes") and streaming_response.source_nodes:
                sources_html = format_sources_html(streaming_response.source_nodes)
                sources_formatted = True
                
            yield "", history, sources_html or "<div style='color:#64748b; font-size:0.88em; padding:8px;'>⚡ Synthesizing technical answer...</div>"

        if hasattr(streaming_response, "source_nodes") and streaming_response.source_nodes:
            sources_html = format_sources_html(streaming_response.source_nodes)
            
        yield "", history, sources_html

    except Exception as err:
        err_str = f"⚠️ An error occurred while generating response: {str(err)}"
        if history:
            history[-1]["content"] = err_str
        yield "", history, "<div style='color:#ef4444; font-size:0.85em;'>⚠️ Generation error</div>"


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

#header-block h1 {
    font-size: 2.1em !important;
    font-weight: 800 !important;
    background: linear-gradient(135deg, #38bdf8, #8b5cf6, #34d399);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    background-clip: text;
    margin: 0 0 6px 0 !important;
    letter-spacing: -0.5px;
}

.status-badge {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    background: rgba(6, 182, 212, 0.1);
    border: 1px solid rgba(6, 182, 212, 0.3);
    color: #38bdf8;
    padding: 4px 12px;
    border-radius: 20px;
    font-size: 0.78em;
    font-weight: 600;
}

#chatbot {
    border: 1px solid var(--border-color) !important;
    border-radius: 16px !important;
    background: var(--bg-panel) !important;
    min-height: 540px !important;
    max-height: 540px !important;
    box-shadow: inset 0 2px 4px rgba(0, 0, 0, 0.2);
}

#chatbot .message {
    border-radius: 12px !important;
    line-height: 1.6 !important;
}

#msg-input textarea {
    background: var(--bg-card) !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 14px !important;
    color: var(--text-bright) !important;
    padding: 14px 18px !important;
    font-size: 0.95em !important;
    transition: all 0.2s ease;
}

#msg-input textarea:focus {
    border-color: var(--primary-cyan) !important;
    box-shadow: 0 0 0 3px rgba(6, 182, 212, 0.2) !important;
}

#send-btn {
    background: linear-gradient(135deg, #06b6d4, #8b5cf6) !important;
    color: #ffffff !important;
    border: none !important;
    border-radius: 14px !important;
    font-weight: 700 !important;
    font-size: 0.95em !important;
    min-height: 50px !important;
    transition: transform 0.15s ease, box-shadow 0.2s ease;
    box-shadow: 0 4px 14px rgba(6, 182, 212, 0.3);
}

#send-btn:hover {
    transform: translateY(-1px);
    box-shadow: 0 6px 20px rgba(6, 182, 212, 0.45);
}

#clear-btn {
    background: var(--bg-card) !important;
    border: 1px solid var(--border-color) !important;
    color: var(--text-dim) !important;
    border-radius: 14px !important;
    min-height: 50px !important;
    transition: all 0.2s ease;
}

#clear-btn:hover {
    border-color: var(--primary-cyan) !important;
    color: var(--text-bright) !important;
}

#sources-display {
    background: var(--bg-panel) !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 16px !important;
    min-height: 280px !important;
    max-height: 360px !important;
    overflow-y: auto !important;
    padding: 14px !important;
}

#stats-display {
    background: linear-gradient(135deg, var(--bg-panel), #141b36) !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 16px !important;
    padding: 16px !important;
}

.chip-category-title {
    font-size: 0.78em;
    font-weight: 700;
    text-transform: uppercase;
    letter-spacing: 1px;
    color: var(--primary-cyan);
    margin-bottom: 8px;
}

.prompt-chip button {
    background: var(--bg-card) !important;
    border: 1px solid var(--border-color) !important;
    color: var(--text-bright) !important;
    border-radius: 10px !important;
    padding: 8px 14px !important;
    font-size: 0.82em !important;
    transition: all 0.2s ease !important;
}

.prompt-chip button:hover {
    border-color: var(--primary-cyan) !important;
    background: rgba(6, 182, 212, 0.1) !important;
    color: var(--primary-cyan) !important;
    transform: translateY(-1px);
}

.sidebar-label {
    font-size: 0.8em;
    text-transform: uppercase;
    letter-spacing: 1.2px;
    color: var(--text-dim);
    margin-bottom: 10px;
    font-weight: 700;
}

footer { display: none !important; }
"""

CATEGORIZED_QUESTIONS = {
    "🔒 SHIP Security & Transport": [
        "What are the mandatory TLS cipher suites for SHIP?",
        "How is mDNS/DNS-SD discovery configured for SHIP?",
    ],
    "🔄 Connection State Machines": [
        "How does the SME connection state machine work?",
        "Describe the PIN verification state machine",
    ],
    "📐 SPINE Datagrams & XSDs": [
        "Explain the SPINE datagram command frame structure",
        "What XSD types does LoadControl define?",
    ]
}

def build_ui():
    """Build the Gradio interface."""
    theme = gr.themes.Soft(
        primary_hue=gr.themes.colors.cyan,
        secondary_hue=gr.themes.colors.purple,
        neutral_hue=gr.themes.colors.slate,
        font=[gr.themes.GoogleFont("Inter"), "system-ui", "sans-serif"],
    )

    with gr.Blocks(theme=theme, css=CUSTOM_CSS, title="EEBUS Protocol Expert") as demo:
        with gr.Row(elem_id="header-block"):
            with gr.Column(scale=4):
                gr.Markdown(
                    "# ⚡ EEBUS Protocol Expert\n"
                    "Production RAG Assistant for **SHIP** & **SPINE** Specifications & Use Cases"
                )
            with gr.Column(scale=1, min_width=200):
                gr.HTML(
                    f"<div style='text-align:right; margin-top:8px;'>"
                    f"<span class='status-badge'>🟢 Online</span><br/>"
                    f"<span style='font-size:0.75em; color:#94a3b8; margin-top:4px; display:inline-block;'>LLM: <b>{LLM_MODEL.replace('models/', '')}</b></span>"
                    f"</div>"
                )

        with gr.Row():
            with gr.Column(scale=3):
                chatbot = gr.Chatbot(
                    elem_id="chatbot",
                    show_label=False
                )
                with gr.Row():
                    msg = gr.Textbox(
                        elem_id="msg-input",
                        placeholder="Ask about EEBUS protocol specifications, SME states, XSD types...",
                        show_label=False,
                        scale=6,
                        lines=1,
                        max_lines=4,
                    )
                    send_btn = gr.Button("Send ⚡", elem_id="send-btn", scale=1)
                    clear_btn = gr.Button("Clear 🗑️", elem_id="clear-btn", scale=1)

                with gr.Accordion("⚙️ RAG Engine Settings", open=False):
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
                        f"**Retriever:** `VectorStoreIndex + ContextEngine`\n\n"
                        f"**Mode:** `Token Streaming ⚡`"
                    ),
                    elem_id="stats-display",
                )

        gr.HTML("<div class='sidebar-label' style='margin-top:12px;'>💡 QUICK SPECIFICATION PROMPTS</div>")
        with gr.Row():
            for cat_title, questions in CATEGORIZED_QUESTIONS.items():
                with gr.Column(scale=1):
                    gr.HTML(f"<div class='chip-category-title'>{cat_title}</div>")
                    for q in questions:
                        btn = gr.Button(q, size="sm", elem_classes=["prompt-chip"])
                        # Click populates msg and immediately auto-submits to stream_respond
                        btn.click(
                            fn=lambda question=q: question, outputs=[msg]
                        ).then(
                            fn=stream_respond,
                            inputs=[msg, chatbot, temp_slider, top_k_slider],
                            outputs=[msg, chatbot, sources_display]
                        )

        def clear_history():
            if chat_engine:
                chat_engine.reset()
            return [], "<div style='color:#64748b; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>"

        submit_args = dict(
            fn=stream_respond,
            inputs=[msg, chatbot, temp_slider, top_k_slider],
            outputs=[msg, chatbot, sources_display]
        )

        msg.submit(**submit_args)
        send_btn.click(**submit_args)
        clear_btn.click(fn=clear_history, outputs=[chatbot, sources_display])

    return demo


# ─── Main Entry Point ───────────────────────────────────────────────────────────

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="EEBUS Chatbot Web Server")
    parser.add_argument("--host", type=str, default="127.0.0.1", help="Host IP to bind (default: 127.0.0.1)")
    parser.add_argument("--port", type=int, default=7860, help="Port number (default: 7860)")
    parser.add_argument("--share", action="store_true", help="Create a public Gradio share link")
    args = parser.parse_args()

    if chat_engine:
        print(f"\n✅ Ready — {total_chunks:,} LlamaIndex chunks loaded from ChromaDB.")
        print(f"🌐 Launching enhanced server on http://{args.host}:{args.port} (share={args.share})\n")
        build_ui().launch(server_name=args.host, server_port=args.port, share=args.share)
    else:
        print("\n❌ Failed to load index. Please run eebus_ingest.py first.")