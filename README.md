# ⚡ EEBUS Protocol Expert — RAG Chatbot

An AI-powered technical assistant built with **LlamaIndex**, **ChromaDB**, and **Google Gemini** to answer developer questions on EEBUS specifications (**SHIP**, **SPINE**, Use Cases, and XSD schemas) with exact standard citations.

---

## ⚡ Key Features

- **Real-Time Token Streaming**: Instant response streaming in a dark-mode Gradio web app.
- **Fast Incremental Ingestion**: Uses MD5 document hashing to process file updates in milliseconds.
- **Type-Aware Semantic Chunking**: Preserves syntax integrity for PDFs, Markdown, XSD schemas, and XML datagrams.
- **Interactive Source Citations**: Sidebar displays retrieved specification passages with page numbers and expandable previews.

---

## 🚀 Quick Start

### 1. Environment Setup

* **Windows**:
  ```cmd
  setup_env.bat
  ```

* **Linux / WSL**:
  ```bash
  chmod +x setup_env.sh && ./setup_env.sh
  ```

### 2. Configure API Key

Copy `.env.example` to `.env` and set your `GOOGLE_API_KEY`:
```env
GOOGLE_API_KEY=your_actual_gemini_api_key_here
```

### 3. Ingest Documents
Build or update the vector index from `EEBUS/`:
```bash
python eebus_ingest.py
```
*(Run `python eebus_ingest.py --force` to force a full re-indexing from scratch)*

### 4. Launch Chatbot
```bash
python qabot_gemini.py
```
Open **`http://127.0.0.1:7860`** in your browser!

---

## 📂 Directory Structure

```text
├── EEBUS/               # EEBUS documentation corpus (PDFs, XSDs, MD, XMLs)
├── eebus_ingest.py      # Document ingestion & vector indexing pipeline
├── qabot_gemini.py      # Gradio chat interface & streaming RAG engine
├── requirements.txt     # Python package dependencies
├── .env.example         # Template for environment variables
└── README.md            # Developer documentation
```
