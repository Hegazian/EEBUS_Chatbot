"""
EEBUS Engineering Platform — Tab 1: Protocol Expert Chat
Session-isolated multi-turn RAG assistant with dynamic engineering personas.
"""
import gradio as gr
from core.config import (
    DEFAULT_RETRIEVER_K, DEFAULT_TEMPERATURE, CATEGORIZED_QUESTIONS,
    USER_ROLES, DEFAULT_USER_ROLE
)
from core.engine import create_chat_engine
from ui.components.sources_viewer import format_sources_html
from ui.components.knowledge_stats import render_knowledge_stats


def stream_respond(
    message: str,
    history: list,
    session: dict,
    temperature: float,
    top_k: int,
    llm_provider: str,
    api_key: str,
    component_filter: str = "All Specifications",
    use_reranker: bool = True,
    user_role: str = DEFAULT_USER_ROLE
):
    """Process user message and stream response using per-session isolated ChatEngine."""
    if not message.strip():
        yield "", history, "<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>", session
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
        or session.get("user_role") != user_role
    )

    if needs_rebuild:
        try:
            engine, _ = create_chat_engine(
                temperature=temperature,
                top_k=int(top_k),
                llm_provider=llm_provider,
                api_key=api_key,
                component_filter=component_filter,
                use_reranker=use_reranker,
                user_role=user_role
            )
            session["engine"] = engine
            session["temperature"] = temperature
            session["top_k"] = int(top_k)
            session["llm_provider"] = llm_provider
            session["api_key"] = api_key
            session["component_filter"] = component_filter
            session["use_reranker"] = use_reranker
            session["user_role"] = user_role

            if history:
                try:
                    from llama_index.core.llms import ChatMessage, MessageRole
                    # Limit memory window to the most recent 30 turns (15 Q&A exchanges)
                    # Filter out system error messages to prevent LLM memory contamination
                    bounded_history = history[-30:]
                    messages = []
                    for m in bounded_history:
                        content = ""
                        role = None
                        if isinstance(m, dict):
                            content = str(m.get("content", ""))
                            role = MessageRole.USER if m.get("role") == "user" else MessageRole.ASSISTANT
                        elif isinstance(m, (list, tuple)) and len(m) == 2:
                            if m[0]:
                                role = MessageRole.USER
                                content = str(m[0])
                            elif m[1]:
                                role = MessageRole.ASSISTANT
                                content = str(m[1])
                        
                        # Skip empty, placeholder, or system error messages
                        if not content or content == "..." or content.startswith("⚠️"):
                            continue
                        if role:
                            messages.append(ChatMessage(role=role, content=content))
                    
                    if hasattr(engine, "_memory"):
                        engine._memory.set(messages)
                    elif hasattr(engine, "memory"):
                        engine.memory.set(messages)
                except Exception:
                    pass
        except Exception as e:
            history.append({"role": "user", "content": message})
            history.append({"role": "assistant", "content": f"⚠️ Configuration Error: {str(e)}"})
            yield gr.update(), history, f"<div style='color:#ef4444; font-size:0.85em;'>⚠️ Config Error</div>", session
            return

    history.append({"role": "user", "content": message})
    history.append({"role": "assistant", "content": "..."})
    yield gr.update(value=""), history, "<div style='color:#06b6d4; font-size:0.85em; padding:8px;'>⚡ Searching EEBUS specifications & generating response...</div>", session

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
                
            yield gr.update(), history, sources_html or "<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>⚡ Synthesizing technical answer...</div>", session

        if not accumulated_text.strip():
            accumulated_text = "⚠️ No response was generated. The request may have been truncated or blocked by an upstream safety filter."
            history[-1]["content"] = accumulated_text

        if hasattr(streaming_response, "source_nodes") and streaming_response.source_nodes:
            sources_html = format_sources_html(streaming_response.source_nodes)
            
        yield gr.update(), history, sources_html, session

    except Exception as err:
        err_msg = str(err)
        if "429" in err_msg or "quota" in err_msg.lower() or "rate_limit" in err_msg.lower():
            err_str = (
                "⚠️ **Gemini Free-Tier Rate Limit Reached (HTTP 429)**\n\n"
                "Google Gemini free-tier imposes a strict requests-per-minute ceiling on newly created API keys. "
                "The engine has been automatically pinned to **Gemini 1.5 Flash** (15 requests/min, 1,500 requests/day).\n\n"
                "⏳ **Please wait ~10 seconds** and click **Send** again to resume."
            )
            badge_html = "<div style='color:#f59e0b; font-size:0.85em; padding:8px;'>⚠️ Free-tier quota exceeded. Please wait 10s.</div>"
        else:
            err_str = f"⚠️ An error occurred while generating response: {err_msg}"
            badge_html = "<div style='color:#ef4444; font-size:0.85em;'>⚠️ Generation error</div>"
            
        if history:
            history[-1]["content"] = err_str
        # Preserve retrieved source citation cards alongside the error badge if available
        combined_display = f"{badge_html}{sources_html}" if sources_html else badge_html
        yield gr.update(), history, combined_display, session


def clear_history(session: dict):
    """Reset session chat engine memory, purge cached engine instance, and clear display."""
    if session:
        engine = session.get("engine")
        if engine:
            try:
                if hasattr(engine, "reset"):
                    engine.reset()
                if hasattr(engine, "_memory") and hasattr(engine._memory, "reset"):
                    engine._memory.reset()
            except Exception:
                pass
        session["engine"] = None
    return [], "<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>", session


def update_role_description(role_key: str) -> str:
    """Return descriptive guidance badge for the selected engineering role."""
    role_info = USER_ROLES.get(role_key, USER_ROLES[DEFAULT_USER_ROLE])
    return (
        f"<div id='role-guidance-box'>"
        f"<span>🎯</span> <strong>{role_info['title']} Focus:</strong> {role_info['description']}"
        f"</div>"
    )


def create_chat_tab(session_state: gr.State, total_chunks: int = 0):
    """Construct Tab 1: Protocol Expert Chat with role switcher and quick prompts."""
    with gr.TabItem("💬 Protocol Expert Chat", id="tab_chat"):
        with gr.Row():
            with gr.Column(scale=3):
                chatbot = gr.Chatbot(elem_id="chatbot", show_label=False)

                with gr.Row():
                    role_dropdown = gr.Dropdown(
                        choices=list(USER_ROLES.keys()),
                        value=DEFAULT_USER_ROLE,
                        label="🎭 User Engineering Role / Persona",
                        info="Tailors response technical depth, code snippets, test scenarios, or architecture",
                        scale=3
                    )
                    component_filter_dropdown = gr.Dropdown(
                        choices=["All Specifications", "SHIP (Transport)", "SPINE (Application)", "Use Cases"],
                        value="All Specifications",
                        label="🎯 Specification Scope Filter",
                        scale=2
                    )
                
                # Dynamic role guidance callout banner
                role_guidance_display = gr.HTML(value=update_role_description(DEFAULT_USER_ROLE))

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

                with gr.Accordion("⚙️ Advanced RAG Engine Settings", open=False):
                    with gr.Row():
                        llm_provider_dropdown = gr.Dropdown(
                            choices=["Gemini (Google)", "ChatGPT (OpenAI)", "Claude (Anthropic)"], 
                            value="Gemini (Google)", 
                            label="🤖 LLM Provider"
                        )
                        api_key_input = gr.Textbox(
                            type="password", 
                            placeholder="Optional: Override .env key...", 
                            label="🔑 API Key"
                        )
                    with gr.Row():
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
                    value="<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>*Sources will appear here after your question*</div>",
                    elem_id="sources-display",
                )
                render_knowledge_stats(total_chunks)

        settings_inputs = [
            temp_slider,
            top_k_slider,
            llm_provider_dropdown,
            api_key_input,
            component_filter_dropdown,
            reranker_checkbox,
            role_dropdown
        ]

        # Update role description callout dynamically
        role_dropdown.change(
            fn=update_role_description,
            inputs=[role_dropdown],
            outputs=[role_guidance_display]
        )

        def make_prompt_chip_handler(prompt_text: str):
            def _handler(history, session, temp, top_k, prov, key, comp, rerank, role):
                yield from stream_respond(
                    prompt_text,
                    history,
                    session,
                    temp,
                    top_k,
                    prov,
                    key,
                    comp,
                    rerank,
                    role
                )
            return _handler

        gr.HTML("<div class='sidebar-label' style='margin-top:14px;'>💡 QUICK SPECIFICATION PROMPTS</div>")
        with gr.Row():
            for cat_title, questions in CATEGORIZED_QUESTIONS.items():
                with gr.Column(scale=1):
                    gr.HTML(f"<div class='chip-category-title'>{cat_title}</div>")
                    for q in questions:
                        btn = gr.Button(q, size="sm", elem_classes=["prompt-chip"])
                        btn.click(
                            fn=make_prompt_chip_handler(q),
                            inputs=[chatbot, session_state] + settings_inputs,
                            outputs=[msg, chatbot, sources_display, session_state]
                        )

        submit_args = dict(
            fn=stream_respond,
            inputs=[msg, chatbot, session_state] + settings_inputs,
            outputs=[msg, chatbot, sources_display, session_state]
        )

        msg.submit(**submit_args)
        send_btn.click(**submit_args)
        clear_btn.click(
            fn=clear_history,
            inputs=[session_state],
            outputs=[chatbot, sources_display, session_state]
        )
