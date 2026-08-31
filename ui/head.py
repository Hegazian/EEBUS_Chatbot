"""
EEBUS Engineering Platform — External Head Scripts & Assets
Loads Mermaid.js v10 module and enforces consistent dark theme on DOM root.
"""

HEAD_HTML = """
<script>
    (function() {
        // Enforce dark theme class on DOM root immediately to prevent light-mode font washouts
        function enforceDark() {
            document.documentElement.classList.add('dark');
            if (document.body) {
                document.body.classList.add('dark');
            }
            const gradioApp = document.querySelector('gradio-app');
            if (gradioApp) {
                gradioApp.classList.add('dark');
            }
        }
        enforceDark();
        document.addEventListener('DOMContentLoaded', enforceDark);
        // Observe attribute changes on html in case Gradio attempts to revert to light mode
        const observer = new MutationObserver(enforceDark);
        observer.observe(document.documentElement, { attributes: true, attributeFilter: ['class'] });
    })();
</script>
<script type="module">
    import mermaid from 'https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs';
    window.mermaid = mermaid;
    mermaid.initialize({
        startOnLoad: false,
        theme: 'dark',
        themeVariables: {
            darkMode: true,
            background: '#080e1a',
            primaryColor: '#131f38',
            primaryTextColor: '#f8fafc',
            primaryBorderColor: '#38bdf8',
            lineColor: '#64748b',
            secondaryColor: '#1e1b4b',
            tertiaryColor: '#064e3b'
        }
    });
</script>
"""
