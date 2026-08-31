"""
EEBUS Engineering Platform — Tab 4: Benchmark & Telemetry
Automated 25-query RAG evaluation suite and live scorecard renderer.
"""
import os
import gradio as gr
from tests.evaluate_rag import run_rag_benchmark, generate_markdown_report


def create_benchmark_tab():
    """Construct Tab 4: Benchmark & Telemetry."""
    with gr.TabItem("📊 Benchmark & Telemetry", id="tab_telemetry"):
        gr.HTML("<div style='margin-bottom:12px; color:#94a3b8;'>Automated RAG evaluation scorecard across 25 ground-truth technical queries.</div>")
        
        with gr.Row():
            bench_btn = gr.Button("Run Live Benchmark Suite (25 Queries) 🚀", elem_classes=["primary-btn"], scale=1)
        
        existing_report = "*Click the button above to execute the automated benchmark suite.*"
        report_file = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), "tests", "benchmark_report.md")
        if os.path.exists(report_file):
            try:
                with open(report_file, "r", encoding="utf-8") as f:
                    existing_report = f.read()
            except Exception:
                pass
        
        benchmark_results = gr.Markdown(value=existing_report)

        def run_benchmark_handler(progress=gr.Progress(track_tqdm=False)):
            def p_cb(idx, total, desc):
                progress(idx / total, desc=desc)
            scorecard = run_rag_benchmark(eval_top_k=5, progress_callback=p_cb)
            return generate_markdown_report(scorecard)

        bench_btn.click(
            fn=run_benchmark_handler,
            outputs=[benchmark_results]
        )
