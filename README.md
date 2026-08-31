# ⚡ EEBUS Engineering Platform — Industrial AI & Developer Suite

[![EEBUS Standard](https://img.shields.io/badge/EEBUS-SHIP_1.1.0_%7C_SPINE_1.3.0-06b6d4.svg)](https://www.eebus.org/)
[![LlamaIndex](https://img.shields.io/badge/Orchestrator-LlamaIndex_0.14-8b5cf6.svg)](https://www.llamaindex.ai/)
[![Vector Store](https://img.shields.io/badge/Dense_Store-ChromaDB-emerald.svg)](https://www.trychroma.com/)
[![Sparse Index](https://img.shields.io/badge/Sparse_Index-BM25_Okapi-orange.svg)](https://github.com/dorianbrown/rank_bm25)
[![Reranker](https://img.shields.io/badge/Reranker-MS--MARCO_MiniLM-blue.svg)](https://huggingface.co/cross-encoder/ms-marco-MiniLM-L-6-v2)
[![UI](https://img.shields.io/badge/Interface-Gradio_Multi--Tab-ff6b6b.svg)](https://gradio.app/)

A production-ready, industrial-grade engineering platform and Retrieval-Augmented Generation (RAG) assistant for the **EEBUS** communication standards: **SHIP** (Smart High-level Interface Protocol), **SPINE** (Smart Premises Interoperable Neutral-Message Exchange), and official **EEBUS Use Cases** (EVSE charging, Heat Pump control, Limitation of Power Consumption/Production).

Built with **LlamaIndex**, **ChromaDB**, **BM25**, and **Google Gemini** (with multi-provider support for **OpenAI** and **Anthropic**).

---

## 🌟 What Makes This Platform Different?

* **📐 Structure-Aware XSD & XML Ingestion**: Parses all 75 SPINE & SHIP schemas into **1,471 self-contained, valid structural XML definitions** (`complexType`, `simpleType`, `element`) with target namespace headers, preventing XML tags from being sliced in half by arbitrary character splitters.
* **🔍 State-of-the-Art Hybrid Retrieval**: Blends dense semantic embeddings (`BAAI/bge-small-en-v1.5`) with exact lexical symbol search (`BM25Okapi`) using **Reciprocal Rank Fusion (RRF)**, ensuring precise matches for protocol enums, hex identifiers, and XSD element names.
* **⚡ Cross-Encoder Reranking**: Uses `cross-encoder/ms-marco-MiniLM-L-6-v2` to re-rank the hybrid candidate pool, elevating high-relevance technical passages and suppressing peripheral noise.
* **🛡️ Concurrent Multi-User Session Isolation**: All conversation states, memories, and inference parameters are encapsulated in Gradio `gr.State`. Multiple browser connections or users can work simultaneously without context cross-contamination.
* **🔬 W3C Schema Datagram Inspector**: Official validation of raw XML datagrams against `EEBus_SPINE_TS_Datagram.xsd` with semantic header extraction and instant AI-driven compliance repair.
* **🔄 Interactive Protocol State Machines**: Native Mermaid.js visualizations and transition tables for the SHIP Connection Handshake (SME) and SPINE Subscription/Binding lifecycles.
* **📊 Automated Evaluation Suite**: 25 curated ground-truth test queries measuring Hit Rate @ K, MRR, and XSD Structure Precision.

---

## 🖥️ Platform Tour: 4 Dedicated Workspaces

The platform is organized into 4 specialized tabs within [`qabot.py`](file:///d:/EEBUS_Chatbot/qabot.py):

### 1. 💬 Protocol Expert Chat
* **Context-Grounded Reasoning**: Answers technical questions strictly from official EEBUS specifications, differentiating between transport (SHIP), domain (SPINE), and business logic (Use Cases).
* **Specification Scope Filtering**: Scope retrieval dynamically to `"All Specifications"`, `"SHIP (Transport)"`, `"SPINE (Application)"`, or `"Use Cases"`.
* **Cross-Encoder Toggle**: Enable or bypass neural reranking directly from the settings drawer.
* **Multi-LLM Orchestration**: Switch dynamically between Google Gemini, OpenAI GPT-4o-mini, and Anthropic Claude 3 Haiku.
* **Interactive Source Citations**: Expandable citation cards with file basenames, page labels, component badges, and relevance scores.
* **Quick Specification Prompts**: 1-click prompt chips covering handshake flows, resource models, and power limitation algorithms.

### 2. 🔬 SPINE Datagram Inspector
* **W3C XML Schema Validation**: Validates raw SPINE datagrams against official XSDs via `xmlschema`.
* **Semantic Header Breakdown**: Inspects `specificationVersion`, `msgCounter`, `cmdClassifier` (`read`, `reply`, `notify`, `write`, `call`, `result`), `addressSource`, and `addressDestination`.
* **AI Error Diagnosis & Repair**: When a datagram violates schema rules, the AI engine diagnoses the exact failure according to SPINE TS 1.3.0 and outputs a corrected, valid XML payload.
* **Curated Test Samples**: 1-click testing of valid notifications, read requests, and common developer error scenarios.

### 3. 🔄 Protocol State Machines
* **Interactive Mermaid.js Visualizations**:
  * **SHIP SME Handshake**: CMI Initialization → mDNS Discovery → Hello State → Protocol Check → PIN Verification → Approved → Active Data Exchange.
  * **SPINE Subscription Lifecycle**: Discovery → Subscription Request → Result Ack → Asynchronous Notify Stream → Unsubscribe.
  * **SPINE Binding Lifecycle**: Pairing → Binding Request → Operational Bound state.
* **Transition Matrix**: Complete reference table with protocol phases, trigger events, timeout timers ($T_{\text{hello\_init}}$, $T_{\text{hello\_prolong}}$, $T_{\text{pin\_verify}}$), and specification section citations (e.g. SHIP TS 1.1.0 Section 12).

### 4. 📊 Benchmark & Telemetry
* **Knowledge Base Analytics**: Live metrics on the 5,957 database chunks across 118 files.
* **Automated Evaluation Suite**: Run on-demand benchmarks across 25 curated test cases covering all protocol layers.
* **Live Scorecard**: Visual scoreboard reporting Hit Rate @ 1, Hit Rate @ 3, Hit Rate @ 5, Mean Reciprocal Rank (MRR), and average latency.

---

## 📊 Benchmark Scorecard

Evaluated against the 25 golden ground-truth technical queries in [`tests/evaluate_rag.py`](file:///d:/EEBUS_Chatbot/tests/evaluate_rag.py):

| Metric | Target | Benchmark Result | Status |
| :--- | :--- | :--- | :--- |
| **Hit Rate @ 1** (Top-1 Accuracy) | ≥ 60.0% | **68.0%** | ✅ PASS |
| **Hit Rate @ 3** (Top-3 Accuracy) | ≥ 80.0% | **84.0%** | ✅ PASS |
| **Hit Rate @ 5** (Top-5 Accuracy) | ≥ 85.0% | **88.0%** | ✅ PASS |
| **Mean Reciprocal Rank (MRR)** | ≥ 0.700 | **0.763** | ✅ PASS |
| **Structure-Aware XSD Precision** | 100.0% | **100.0%** | ✅ PASS |
| **Average End-to-End Latency** | < 3,500 ms | **2,816 ms** | ✅ PASS |

*(See [`tests/benchmark_report.md`](file:///d:/EEBUS_Chatbot/tests/benchmark_report.md) for the complete query-by-query breakdown).*

---

## 📂 Project Architecture

```text
EEBUS_Chatbot/
├── core/                               # Central Core Package
│   ├── __init__.py                     # Package entry point
│   ├── config.py                       # Paths, .env auto-loader, prompts, constants
│   ├── parsers.py                      # PyPDFReader, StructureAwareXSDParser, validators
│   ├── retriever.py                    # EEBUSHybridRetriever (BGE + BM25 via RRF)
│   └── engine.py                       # Per-session ContextChatEngine factory
├── tools/                              # Engineering & Protocol Tools
│   ├── __init__.py                     # Tools package exports
│   ├── validator.py                    # W3C schema validator for SPINE datagrams
│   └── state_machine.py                # SHIP & SPINE state machine models & Mermaid diagrams
├── tests/                              # Automated Benchmark Suite
│   ├── __init__.py                     # Tests package exports
│   ├── evaluate_rag.py                 # 25 ground-truth evaluation benchmark
│   └── benchmark_report.md             # Auto-generated benchmark scorecard
├── EEBUS/                              # Official standard documentation corpus
│   ├── EEBus_SHIP_TS_Specification_v1.1.0/
│   ├── EEBus_SPINE_V1.3.0_Final_hp/
│   │   └── XSDs/                       # 77 SPINE W3C XML Schema files
│   ├── Implementation Guides/          # Official SHIP and SPINE Implementation Guides
│   ├── Test Specifications/            # Conformance test suites
│   ├── Test Cases/                     # High-level test specifications
│   └── Use Cases/                      # E-Mobility, Grid, Inverter, HVAC Use Cases
├── eebus_ingest.py                     # CLI document ingestion pipeline
├── qabot.py                            # Production 4-tab Gradio engineering platform
├── requirements.txt                    # Project dependencies
├── .env.example                        # API keys template
└── README.md                           # Platform documentation
```

---

## 🚀 Getting Started

### 1. Environment Setup

Clone the repository and install dependencies in a virtual environment:

#### Windows
```cmd
setup_env.bat
```

#### Linux / WSL (Ubuntu)
```bash
chmod +x setup_env.sh && ./setup_env.sh
```

#### Manual Setup
```bash
python -m venv venv
# Windows:
venv\Scripts\activate
# Linux/WSL:
source venv/bin/activate

pip install -r requirements.txt
```

### 2. Configure API Keys

Create a `.env` file from `.env.example`:
```bash
cp .env.example .env
```

Edit `.env` and add your API key:
```env
GOOGLE_API_KEY=your_gemini_api_key_here

# Optional (for multi-provider switching in UI):
OPENAI_API_KEY=your_openai_api_key_here
ANTHROPIC_API_KEY=your_anthropic_api_key_here
```

### 3. Document Ingestion

Build the dense ChromaDB vector store and sparse BM25 index from `EEBUS/`:

```bash
# Incremental sync (sub-second if files are unchanged):
python eebus_ingest.py

# Force a clean rebuild from scratch:
python eebus_ingest.py --force
```

### 4. Launch the Engineering Platform

```bash
python qabot.py
```

Optional CLI flags:
```bash
python qabot.py --host 0.0.0.0 --port 7860 --share
```

Open **`http://127.0.0.1:7860`** in your browser!

---

## 🧪 Running Automated Tests & Benchmarks

To execute the 25 ground-truth evaluation queries through the hybrid pipeline:

```bash
python tests/evaluate_rag.py
```

To run individual verification scripts:
```bash
# Verify structure-aware XSD parser:
python scratch/verify_xsd_parser.py

# Verify per-session memory isolation:
python scratch/verify_phase3.py

# Verify datagram schema validator & state machines:
python scratch/verify_phase4.py
```

---

## 📚 Supported EEBUS Specifications

The knowledge base indexes the complete official standard specifications:

| Specification | Version | Format | Coverage |
| :--- | :--- | :--- | :--- |
| **SHIP Technical Specification** | v1.1.0 | PDF | Transport, TLS 1.2, mDNS, SME handshake |
| **SHIP Implementation Guide** | v1.1.0 | Markdown | Developer setup, message sequence charts |
| **SHIP Transfer Protocol Schema** | v1.1.0 | XSD | CMI frames, Hello, PIN, Data exchange |
| **SPINE Protocol Specification** | v1.3.0 | PDF | Datagram layer, Command frames, Classifiers |
| **SPINE Resource Specification** | v1.3.0 | PDF | Resource model, Function Sets, Data types |
| **SPINE Technical Report** | v1.3.0 | PDF | Architectural introduction & domain overview |
| **SPINE Schema Suite (75 Files)** | v1.3.0 | XSD | Full W3C XML Schema definitions |
| **SPINE Example Datagrams** | v1.3.0 | XML | Restricted & general function exchanges |
| **Limitation of Power Consumption (LPC)** | v1.0.0 | PDF | Use case specification & implementation guide |
| **Limitation of Power Production (LPP)** | v1.0.0 | PDF | Photovoltaic generation curtailment rules |
| **EVSE Commissioning & Configuration** | v1.0.0 | PDF | EV charger pairing and configuration |
| **EV Supply Equipment State** | v1.0.0 | PDF | EVSE operational states and telemetry |

---

## 📄 License & Attribution

* EEBUS, SHIP, and SPINE specifications are copyrighted by [EEBus Initiative e.V.](https://www.eebus.org/)
* Platform code is released under the **MIT License**.
