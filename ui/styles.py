"""
EEBUS Engineering Platform — UI Styling System
Professional cyber-dark theme calibrated for high-contrast readability
and standard responsive web layouts across all display resolutions.
"""

CUSTOM_CSS = """
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700;800&family=JetBrains+Mono:wght@400;500;600;700&display=swap');

/* ── Universal Theme Tokens & Contrast Baseline ───────────────────────────── */
:root, html, body, .gradio-container, .dark, :not(.dark) {
    --bg-base: #060b14 !important;
    --bg-panel: #0d1527 !important;
    --bg-card: #131f38 !important;
    --bg-surface: #172545 !important;
    --border-color: #1e3a5f !important;
    --border-subtle: #172d4a !important;
    --border-glow: rgba(6, 182, 212, 0.35) !important;
    
    --primary-cyan: #06b6d4 !important;
    --cyan-bright: #38bdf8 !important;
    --primary-blue: #3b82f6 !important;
    --accent-purple: #8b5cf6 !important;
    --purple-bright: #a78bfa !important;
    --emerald-green: #10b981 !important;
    --emerald-bright: #34d399 !important;
    --amber-warn: #f59e0b !important;
    --red-alert: #ef4444 !important;

    /* High-contrast text colors: guaranteed crisp readability against dark backgrounds */
    --text-pure: #ffffff !important;
    --text-bright: #f8fafc !important;
    --text-body: #e2e8f0 !important;
    --text-dim: #94a3b8 !important;
    --text-muted: #64748b !important;

    /* Gradio native theme variable overrides (forces high-contrast dark tokens) */
    --body-background-fill: #060b14 !important;
    --background-fill-primary: #060b14 !important;
    --background-fill-secondary: #0d1527 !important;
    --block-background-fill: #0d1527 !important;
    --block-border-color: #1e3a5f !important;
    --body-text-color: #f8fafc !important;
    --body-text-color-subdued: #94a3b8 !important;
    --block-label-text-color: #cbd5e1 !important;
    --input-background-fill: #0d1527 !important;
    --input-text-color: #f8fafc !important;
    --input-placeholder-color: #64748b !important;
    --input-border-color: #1e3a5f !important;
    --table-text-color: #f8fafc !important;
    --table-border-color: #1e3a5f !important;
    --table-row-focus: #172545 !important;
    --color-accent: #06b6d4 !important;
    --color-accent-soft: rgba(6, 182, 212, 0.18) !important;
    --link-text-color: #38bdf8 !important;
    --link-text-color-hover: #7dd3fc !important;
    
    --font-sans: 'Inter', system-ui, -apple-system, sans-serif !important;
    --font-mono: 'JetBrains Mono', monospace !important;
}

/* ── Base Layout & Standard Web Viewport Sizing ───────────────────────────── */
html, body {
    background-color: var(--bg-base) !important;
    font-family: var(--font-sans) !important;
    color: var(--text-body) !important;
    margin: 0 !important;
    padding: 0 !important;
    width: 100% !important;
    height: 100% !important;
    -webkit-font-smoothing: antialiased !important;
}

.gradio-container {
    width: 95% !important;
    max-width: 1600px !important;
    margin: 0 auto !important;
    padding: 20px 24px !important;
    box-sizing: border-box !important;
}

@media (max-width: 1200px) {
    .gradio-container {
        width: 98% !important;
        padding: 14px 16px !important;
    }
}

@media (max-width: 768px) {
    .gradio-container {
        width: 100% !important;
        padding: 8px 10px !important;
    }
}

/* ── Universal Typography & Contrast Enforcements ─────────────────────────── */
p, span, div, li, td, th {
    color: var(--text-body);
}

h1, h2, h3, h4, h5, h6 {
    color: var(--text-pure) !important;
    font-weight: 700 !important;
    letter-spacing: -0.3px !important;
}

label, label span, .block-label, .block-title, .label-wrap {
    color: #cbd5e1 !important;
    font-weight: 600 !important;
    font-size: 0.88em !important;
}

.info, .form-info, .block-info {
    color: var(--text-dim) !important;
    font-size: 0.82em !important;
}

/* ── Custom Dark Scrollbars ────────────────────────────────────────────────── */
::-webkit-scrollbar {
    width: 7px;
    height: 7px;
}
::-webkit-scrollbar-track {
    background: #060b14;
}
::-webkit-scrollbar-thumb {
    background: #1e3a5f;
    border-radius: 4px;
}
::-webkit-scrollbar-thumb:hover {
    background: #06b6d4;
}

/* ── Header Banner ─────────────────────────────────────────────────────────── */
#header-block {
    background: linear-gradient(135deg, #091329 0%, #17153b 45%, #081120 100%) !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 18px !important;
    padding: 22px 32px !important;
    margin-bottom: 16px !important;
    box-shadow: 0 12px 32px -12px rgba(6, 182, 212, 0.25), inset 0 1px 0 rgba(255, 255, 255, 0.08) !important;
    position: relative !important;
    overflow: hidden !important;
}

#header-block::before {
    content: '';
    position: absolute;
    top: -50%;
    right: -6%;
    width: 440px;
    height: 440px;
    background: radial-gradient(circle, rgba(6, 182, 212, 0.2) 0%, transparent 70%);
    pointer-events: none;
}

.header-title {
    font-size: 2.2em !important;
    font-weight: 800 !important;
    letter-spacing: -0.5px;
    background: linear-gradient(90deg, #38bdf8 0%, #818cf8 50%, #c084fc 100%);
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    margin-bottom: 6px !important;
}

.header-subtitle {
    color: #cbd5e1 !important;
    font-size: 0.95em !important;
    line-height: 1.55 !important;
}

.header-subtitle strong {
    color: #38bdf8 !important;
}

.header-badge-strip {
    display: flex;
    gap: 8px;
    margin-top: 14px;
    flex-wrap: wrap;
    align-items: center;
}

.tech-badge {
    background: rgba(13, 21, 39, 0.9) !important;
    border: 1px solid rgba(6, 182, 212, 0.35) !important;
    color: #38bdf8 !important;
    padding: 5px 12px !important;
    border-radius: 8px !important;
    font-size: 0.76em !important;
    font-weight: 600 !important;
    letter-spacing: 0.5px !important;
    text-transform: uppercase !important;
    box-shadow: 0 2px 6px rgba(0, 0, 0, 0.25) !important;
}

.tech-badge:hover {
    border-color: #38bdf8 !important;
    box-shadow: 0 0 12px rgba(56, 189, 248, 0.3) !important;
}

.status-pill {
    background: rgba(16, 185, 129, 0.16) !important;
    border: 1px solid rgba(16, 185, 129, 0.45) !important;
    color: #34d399 !important;
    padding: 5px 12px !important;
    border-radius: 8px !important;
    font-size: 0.76em !important;
    font-weight: 700 !important;
    display: inline-flex !important;
    align-items: center !important;
    gap: 6px !important;
}

/* ── Navigation Tabs ───────────────────────────────────────────────────────── */
.tabs > .tab-nav {
    border-bottom: 1px solid var(--border-color) !important;
    background: transparent !important;
    gap: 8px !important;
    margin-bottom: 18px !important;
}

.tabs > .tab-nav > button {
    font-size: 0.95em !important;
    font-weight: 600 !important;
    color: var(--text-dim) !important;
    border: 1px solid transparent !important;
    border-radius: 12px !important;
    padding: 10px 20px !important;
    transition: all 0.2s ease !important;
    background: transparent !important;
}

.tabs > .tab-nav > button:hover {
    color: var(--text-pure) !important;
    background: rgba(19, 31, 56, 0.7) !important;
    border-color: var(--border-color) !important;
}

.tabs > .tab-nav > button.selected {
    color: #38bdf8 !important;
    background: rgba(6, 182, 212, 0.12) !important;
    border: 1px solid rgba(6, 182, 212, 0.45) !important;
    box-shadow: 0 2px 10px rgba(6, 182, 212, 0.2) !important;
}

/* ── Chatbot Component ─────────────────────────────────────────────────────── */
#chatbot {
    background: #080e1b !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 16px !important;
    box-shadow: 0 8px 28px rgba(0, 0, 0, 0.4) !important;
    min-height: 560px !important;
}

#chatbot .message, #chatbot [data-testid="bot"], #chatbot [data-testid="user"] {
    font-size: 0.94em !important;
    line-height: 1.6 !important;
}

/* User chat bubble */
#chatbot [data-testid="user"], #chatbot .message.user, #chatbot .user {
    background: linear-gradient(135deg, #0284c7 0%, #2563eb 100%) !important;
    color: #ffffff !important;
    border: 1px solid rgba(56, 189, 248, 0.3) !important;
    border-radius: 14px 14px 2px 14px !important;
    font-weight: 500 !important;
    box-shadow: 0 4px 12px rgba(2, 132, 199, 0.25) !important;
}

/* Assistant chat bubble */
#chatbot [data-testid="bot"], #chatbot .message.bot, #chatbot .bot {
    background: #0d1527 !important;
    border: 1px solid var(--border-color) !important;
    color: #f8fafc !important;
    border-radius: 14px 14px 14px 2px !important;
    box-shadow: 0 4px 14px rgba(0, 0, 0, 0.3) !important;
}

#role-guidance-box {
    background: rgba(139, 92, 246, 0.12) !important;
    border: 1px solid rgba(139, 92, 246, 0.35) !important;
    border-radius: 10px !important;
    padding: 10px 16px !important;
    font-size: 0.86em !important;
    color: #ddd6fe !important;
    margin-top: -6px !important;
    margin-bottom: 10px !important;
    display: flex !important;
    align-items: center !important;
    gap: 8px !important;
}

#role-guidance-box strong {
    color: #ffffff !important;
}

/* ── Form Inputs, Dropdowns & Textareas ────────────────────────────────────── */
input[type="text"], input[type="password"], textarea, select, .gr-input {
    background-color: #0d1527 !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 12px !important;
    color: #f8fafc !important;
    font-size: 0.92em !important;
    transition: all 0.2s ease !important;
}

input:focus, textarea:focus, select:focus {
    border-color: var(--primary-cyan) !important;
    box-shadow: 0 0 0 2px rgba(6, 182, 212, 0.3) !important;
    outline: none !important;
}

#msg-input textarea, #datagram-input textarea {
    font-family: var(--font-mono) !important;
    font-size: 0.90em !important;
    line-height: 1.5 !important;
}

/* Dropdown choices styling (fixing light mode invisible font) */
.wrap, .dropdown, [data-testid="dropdown"] {
    background-color: #0d1527 !important;
    border-color: var(--border-color) !important;
    color: #f8fafc !important;
}

.wrap .item, .dropdown .item, .wrap span, .dropdown span {
    color: #f8fafc !important;
}

ul.options, .dropdown ul, .options {
    background-color: #0d1527 !important;
    border: 1px solid var(--border-color) !important;
    box-shadow: 0 8px 24px rgba(0, 0, 0, 0.5) !important;
}

ul.options li, .dropdown ul li, .options li {
    background-color: #0d1527 !important;
    color: #e2e8f0 !important;
    padding: 8px 12px !important;
}

ul.options li:hover, .dropdown ul li:hover, .options li:hover,
ul.options li.selected, .dropdown ul li.selected {
    background-color: #172545 !important;
    color: #38bdf8 !important;
}

/* ── Buttons ───────────────────────────────────────────────────────────────── */
.primary-btn {
    background: linear-gradient(135deg, #06b6d4 0%, #3b82f6 100%) !important;
    border: none !important;
    color: #ffffff !important;
    font-weight: 700 !important;
    border-radius: 12px !important;
    padding: 10px 20px !important;
    transition: all 0.2s ease !important;
    box-shadow: 0 4px 12px rgba(6, 182, 212, 0.3) !important;
}

.primary-btn:hover {
    transform: translateY(-1px) !important;
    box-shadow: 0 6px 18px rgba(6, 182, 212, 0.5) !important;
}

.secondary-btn {
    background: #131f38 !important;
    border: 1px solid #1e3a5f !important;
    color: #cbd5e1 !important;
    font-weight: 600 !important;
    border-radius: 12px !important;
    padding: 10px 18px !important;
    transition: all 0.2s ease !important;
}

.secondary-btn:hover {
    background: #1e2d4d !important;
    color: #ffffff !important;
    border-color: #38bdf8 !important;
}

/* ── Sidebars & Display Panels ─────────────────────────────────────────────── */
#sources-display {
    background: #080e1b !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 14px !important;
    padding: 14px !important;
    max-height: 560px !important;
    overflow-y: auto !important;
}

#stats-display {
    background: #080e1b !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 14px !important;
    padding: 16px !important;
    font-size: 0.86em !important;
    line-height: 1.65 !important;
    color: #e2e8f0 !important;
}

#stats-display strong {
    color: #38bdf8 !important;
}

.sidebar-label {
    font-size: 0.82em !important;
    font-weight: 700 !important;
    letter-spacing: 0.6px !important;
    color: #94a3b8 !important;
    margin-bottom: 8px !important;
    display: flex !important;
    align-items: center !important;
    gap: 6px !important;
    text-transform: uppercase !important;
}

/* ── Prompt Chips ──────────────────────────────────────────────────────────── */
.prompt-chip {
    background: rgba(13, 21, 39, 0.85) !important;
    border: 1px solid #1e3a5f !important;
    color: #cbd5e1 !important;
    border-radius: 10px !important;
    padding: 8px 14px !important;
    font-size: 0.84em !important;
    text-align: left !important;
    transition: all 0.15s ease !important;
    margin-bottom: 8px !important;
    width: 100% !important;
    white-space: normal !important;
    height: auto !important;
    min-height: 44px !important;
    line-height: 1.4 !important;
}

.prompt-chip:hover {
    border-color: var(--primary-cyan) !important;
    background: rgba(6, 182, 212, 0.14) !important;
    color: #38bdf8 !important;
    transform: translateY(-1px) !important;
    box-shadow: 0 3px 10px rgba(6, 182, 212, 0.25) !important;
}

.chip-category-title {
    font-size: 0.78em !important;
    font-weight: 700 !important;
    text-transform: uppercase !important;
    letter-spacing: 0.7px !important;
    color: #a78bfa !important;
    margin-bottom: 8px !important;
}

/* ── Markdown Content & Tables (Guaranteed Light/Dark Visibility) ───────────── */
.prose, .prose *, .markdown, .markdown * {
    color: #f1f5f9;
}

.prose strong, .markdown strong {
    color: #ffffff !important;
    font-weight: 700 !important;
}

.prose code, .markdown code {
    background: #080c14 !important;
    color: #38bdf8 !important;
    border: 1px solid #1e3a5f !important;
    padding: 2px 6px !important;
    border-radius: 6px !important;
    font-family: var(--font-mono) !important;
    font-size: 0.88em !important;
}

.prose pre, .markdown pre {
    background: #080c14 !important;
    border: 1px solid #1e3a5f !important;
    border-radius: 10px !important;
    padding: 14px !important;
    color: #e2e8f0 !important;
    overflow-x: auto !important;
}

.prose table, .markdown table {
    border-collapse: collapse !important;
    width: 100% !important;
    margin: 14px 0 !important;
    border-radius: 10px !important;
    overflow: hidden !important;
    border: 1px solid #1e3a5f !important;
}

.prose th, .markdown th {
    background: #131f38 !important;
    color: #38bdf8 !important;
    border: 1px solid #1e3a5f !important;
    padding: 10px 14px !important;
    font-weight: 700 !important;
    text-align: left !important;
    font-size: 0.88em !important;
}

.prose td, .markdown td {
    background: #080e1b !important;
    color: #e2e8f0 !important;
    border: 1px solid #1e3a5f !important;
    padding: 8px 14px !important;
    font-size: 0.86em !important;
}

.prose tr:hover td, .markdown tr:hover td {
    background: #0d1527 !important;
}

/* ── Accordion Component ───────────────────────────────────────────────────── */
.accordion, [data-testid="accordion"] {
    background: #0d1527 !important;
    border: 1px solid var(--border-color) !important;
    border-radius: 12px !important;
}

.accordion .label-wrap {
    color: #38bdf8 !important;
    font-weight: 600 !important;
}

/* ── Datagram Inspector Elements ───────────────────────────────────────────── */
.status-badge-container {
    border-radius: 12px !important;
    padding: 14px 20px !important;
    font-weight: 700 !important;
    font-size: 0.95em !important;
    display: flex !important;
    align-items: center !important;
    gap: 10px !important;
    margin-bottom: 14px !important;
}

/* ── Mermaid Visualizer Container ──────────────────────────────────────────── */
.mermaid-box {
    background: #080e1a !important;
    border: 1px solid #1e3a5f !important;
    border-radius: 14px !important;
    padding: 24px !important;
    margin-bottom: 16px !important;
    overflow-x: auto !important;
    box-shadow: 0 6px 20px rgba(0, 0, 0, 0.45) !important;
}
"""
