"""
EEBUS Engineering Platform — Tab 2: SPINE Datagram Inspector
W3C schema validation, semantic header analysis, and AI error diagnosis.
"""
import gradio as gr
from core.config import DEFAULT_TEMPERATURE, DEFAULT_USER_ROLE, DEFAULT_RETRIEVER_K
from core.engine import create_chat_engine
from tools.validator import (
    validate_spine_datagram, get_sample_datagrams, diagnose_datagram_error
)


def inspect_datagram_handler(xml_text: str, session: dict):
    """Validate SPINE Datagram and trigger AI compliance diagnosis if invalid."""
    if not xml_text or not xml_text.strip():
        badge = "<div class='status-badge-container' style='background:rgba(239, 68, 68, 0.15); border:1px solid rgba(239, 68, 68, 0.4); color:#f87171;'>⚠️ Please provide an XML datagram.</div>"
        return badge, "No input provided.", "", "", session

    validation = validate_spine_datagram(xml_text)
    is_valid = validation.get("is_valid", False)

    if is_valid:
        badge = """
<div class='status-badge-container' style="background:rgba(16, 185, 129, 0.15); border:1px solid rgba(16, 185, 129, 0.4); color:#34d399;">
    <span>✅</span> SPINE TS 1.3.0 SCHEMA COMPLIANT
</div>"""
        err_details = "✨ No schema violations detected. Datagram is 100% compliant."
        ai_diag = "✅ **Validation Passed**: All header elements, addressing formats, and command payloads adhere strictly to `EEBus_SPINE_TS_Datagram.xsd` and associated feature definitions."
    else:
        err_type = validation.get("error_type", "Validation Error")
        err_path = validation.get("error_path") or "Root"
        err_line = validation.get("line_number") or "N/A"
        err_msg = validation.get("error_message", "")
        
        badge = f"""
<div class='status-badge-container' style="background:rgba(239, 68, 68, 0.15); border:1px solid rgba(239, 68, 68, 0.4); color:#f87171;">
    <span>❌</span> {err_type.upper()}
</div>"""
        err_details = f"**Error Path:** `{err_path}`  \n**Line Number:** `{err_line}`  \n**Violation:** {err_msg}"
        
        # Trigger AI diagnosis using session engine
        engine = session.get("engine") if session else None
        if not engine:
            try:
                temp = session.get("temperature", DEFAULT_TEMPERATURE) if session else DEFAULT_TEMPERATURE
                top_k = session.get("top_k", DEFAULT_RETRIEVER_K) if session else DEFAULT_RETRIEVER_K
                prov = session.get("llm_provider", "Gemini (Google)") if session else "Gemini (Google)"
                key = session.get("api_key", "") if session else ""
                comp = session.get("component_filter", "All Specifications") if session else "All Specifications"
                rerank = session.get("use_reranker", True) if session else True
                role = session.get("user_role", DEFAULT_USER_ROLE) if session else DEFAULT_USER_ROLE

                engine, _ = create_chat_engine(
                    temperature=temp,
                    top_k=int(top_k),
                    llm_provider=prov,
                    api_key=key,
                    component_filter=comp,
                    use_reranker=rerank,
                    user_role=role
                )
                if session is not None:
                    session["engine"] = engine
                    session["temperature"] = temp
                    session["top_k"] = int(top_k)
                    session["llm_provider"] = prov
                    session["api_key"] = key
                    session["component_filter"] = comp
                    session["use_reranker"] = rerank
                    session["user_role"] = role
            except Exception:
                pass
        
        if engine:
            ai_diag = diagnose_datagram_error(xml_text, validation, engine)
        else:
            ai_diag = "⚠️ AI diagnostic engine unavailable. Please review the schema error path above."

    # Semantic Breakdown
    header = validation.get("header") or {}
    addr_src = header.get("addressSource") or {}
    addr_dst = header.get("addressDestination") or {}
    funcs = validation.get("functions") or []
    
    semantic_md = f"""
### 📋 Semantic Header & Payload Summary
| Field | Extracted Value | Specification Requirement |
| :--- | :--- | :--- |
| **Specification Version** | `{header.get('specificationVersion') or 'N/A'}` | Recognized SPINE specification version (e.g. 1.3.0) |
| **Command Classifier** | `{header.get('cmdClassifier') or 'N/A'}` | read, reply, notify, write, call, result |
| **Message Counter** | `{header.get('msgCounter') or 'N/A'}` | Positive monotonic integer |
| **Address Source** | `{addr_src.get('device') or 'N/A'} : E{addr_src.get('entity') or '-'} : F{addr_src.get('feature') or '-'}` | Valid SPINE URI & feature address |
| **Address Destination** | `{addr_dst.get('device') or 'N/A'} : E{addr_dst.get('entity') or '-'} : F{addr_dst.get('feature') or '-'}` | Valid SPINE URI & feature address |
| **Target Function Sets** | `{', '.join(funcs) if funcs else 'None'}` | Recognized SPINE Function Set |
"""
    return badge, err_details, semantic_md, ai_diag, session


def create_inspector_tab(session_state: gr.State):
    """Construct Tab 2: SPINE Datagram Inspector."""
    sample_dict = get_sample_datagrams()

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
                    value="<div style='color:#94a3b8; font-size:0.9em; padding:8px;'>*Click Validate to run W3C schema check*</div>"
                )
                error_box = gr.Markdown(value="*No errors detected.*")
                semantic_box = gr.Markdown(value="*Semantic header analysis will appear here.*")
                
                gr.HTML("<div class='sidebar-label' style='margin-top:14px;'>🤖 AI COMPLIANCE DIAGNOSIS & REPAIR</div>")
                ai_diag_box = gr.Markdown(value="*AI explanation and corrected payload will appear here upon error.*")
                apply_fix_btn = gr.Button("📥 Apply AI Fix to Editor", elem_classes=["secondary-btn"], scale=1)

        def apply_fix_handler(ai_diag_text: str, current_input: str) -> str:
            """Extract corrected XML code block from AI diagnosis and populate the editor."""
            if not ai_diag_text or "```" not in ai_diag_text:
                return current_input
            import re
            match = re.search(r"```(?:xml)?\s*([\s\S]*?)\s*```", ai_diag_text, re.IGNORECASE)
            if match:
                extracted = match.group(1).strip()
                if "<datagram" in extracted or "<?xml" in extracted:
                    return extracted
            return current_input

        apply_fix_btn.click(
            fn=apply_fix_handler,
            inputs=[ai_diag_box, datagram_input],
            outputs=[datagram_input]
        )

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
            fn=lambda: ("", "<div style='color:#94a3b8; font-size:0.9em;'>*Ready*</div>", "", "", ""),
            outputs=[datagram_input, status_badge, error_box, semantic_box, ai_diag_box]
        )
