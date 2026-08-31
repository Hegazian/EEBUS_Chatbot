"""
EEBUS Engineering Platform — Tab 3: Protocol State Machines
Interactive lifecycle models and Mermaid diagrams for SHIP and SPINE.
"""
import time
import gradio as gr
from tools.state_machine import get_state_machine_data


def format_state_machine_view(machine_key: str):
    """Generate Mermaid diagram and state transition table for chosen state machine."""
    data = get_state_machine_data(machine_key)
    uid = f"mermaid_{machine_key}_{int(time.time() * 1000)}"
    
    mermaid_html = f"""
<div id="{uid}" class="mermaid-box">
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


def create_state_machines_tab():
    """Construct Tab 3: Protocol State Machines."""
    with gr.TabItem("🔄 Protocol State Machines", id="tab_state_machines") as tab_state_machines:
        gr.HTML("<div style='margin-bottom:12px; color:#94a3b8;'>Interactive lifecycle models for SHIP Connection Handshake, SPINE Subscriptions, and Bindings.</div>")
        
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
            outputs=[mermaid_display, info_display],
            js="() => { setTimeout(() => { if (window.mermaid) window.mermaid.run(); }, 250); }"
        )

        # Trigger Mermaid re-render on tab selection
        tab_state_machines.select(
            fn=None,
            js="() => { setTimeout(() => { if (window.mermaid) window.mermaid.run(); }, 250); }"
        )
