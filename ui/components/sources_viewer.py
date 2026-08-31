"""
EEBUS Engineering Platform — Source Citation Formatter Component
"""
import html
from core.parsers import is_clean_node


def format_sources_html(source_nodes) -> str:
    """Format retrieved source nodes into rich HTML citation cards with glowing component badges."""
    if not source_nodes:
        return "<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>*No sources retrieved for this turn*</div>"

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
        metadata = (node.node.metadata if hasattr(node, "node") else getattr(node, "metadata", {})) or {}
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

        safe_filename = html.escape(str(filename))
        safe_snippet = html.escape(str(snippet))
        safe_schema_name = html.escape(str(schema_name)) if schema_name else ""

        page_str = f"<span style='color:#94a3b8; font-size:0.8em; margin-left:6px;'>Page {page}</span>" if page else ""
        elem_str = f"<span style='color:#38bdf8; font-size:0.8em; margin-left:6px;'>Type: {safe_schema_name}</span>" if safe_schema_name else ""
        
        score_val = getattr(node, "score", None)
        score_badge = f"<span style='color:#38bdf8; font-size:0.75em; margin-left:auto;'>Score: {score_val:.2f}</span>" if score_val is not None else ""

        card_html = f"""
<div style="background:#0f172a; border:1px solid #1e293b; border-radius:12px; padding:12px; margin-bottom:10px; transition:all 0.2s ease;">
    <div style="display:flex; justify-content:space-between; align-items:center; gap:8px;">
        <span style="font-weight:600; font-size:0.88em; color:#e2e8f0; display:flex; align-items:center; gap:6px;">
            <span>{icon}</span> {safe_filename}
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
        <pre style="background:#080c14; color:#cbd5e1; font-family:'JetBrains Mono', monospace; font-size:0.75em; padding:10px; border-radius:8px; margin-top:6px; border:1px solid #1e293b; white-space:pre-wrap; max-height:180px; overflow-y:auto; line-height:1.4;">{safe_snippet}</pre>
    </details>
</div>
"""
        cards.append(card_html)

    return "".join(cards) if cards else "<div style='color:#94a3b8; font-size:0.88em; padding:8px;'>*Clean specification sources retrieved*</div>"
