"""
EEBUS Protocol Expert — Industrial Engineering Platform
Application Entry Point and Server Launcher.
"""
import os
import argparse
import chromadb
import gradio as gr
from dotenv import load_dotenv
from core.config import PERSIST_DIR, COLLECTION_NAME
from ui import build_ui, CUSTOM_CSS, HEAD_HTML

load_dotenv(override=True)


def main():
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
        demo = build_ui()
        try:
            demo.launch(
                server_name=args.host,
                server_port=args.port,
                share=args.share,
                css=CUSTOM_CSS,
                head=HEAD_HTML,
                theme=gr.themes.Base()
            )
        except TypeError:
            demo.launch(server_name=args.host, server_port=args.port, share=args.share)
    else:
        print("\n❌ Failed to find database. Please run python eebus_ingest.py --force first.")


if __name__ == "__main__":
    main()
