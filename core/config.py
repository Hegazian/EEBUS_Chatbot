"""
EEBUS Chatbot Configuration
Centralized configuration, paths, defaults, and system prompts.
"""

import os
from dotenv import load_dotenv

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
load_dotenv(os.path.join(BASE_DIR, ".env"), override=True)

EEBUS_DIR = os.path.join(BASE_DIR, "EEBUS")
PERSIST_DIR = os.path.join(BASE_DIR, "eebus_chroma_db")
BM25_PERSIST_DIR = os.path.join(BASE_DIR, "eebus_bm25")
HASHES_FILE = os.path.join(BASE_DIR, ".doc_hashes.json")
CACHE_FILE = os.path.join(BASE_DIR, ".model_cache.json")

COLLECTION_NAME = "eebus_docs"
PRIMARY_EMBEDDING_MODEL = "BAAI/bge-small-en-v1.5"
FALLBACK_EMBEDDING_MODEL = "all-MiniLM-L6-v2"
RERANKER_MODEL = "cross-encoder/ms-marco-MiniLM-L-6-v2"

DEFAULT_RETRIEVER_K = 6
DEFAULT_TEMPERATURE = 0.3
CACHE_TTL_HOURS = 24

EXCLUDE_SEGMENTS = {"KEO", ".XPR", "__PYCACHE__", ".VSCODE", "BUILD", ".IDEA", ".GIT"}

SYSTEM_PROMPT = """You are the EEBUS Protocol Expert, an authoritative AI technical assistant specialized in the EEBUS communication standards: SHIP (Smart High-level Interface Protocol) and SPINE (Smart Premises Interoperable Neutral-Message Exchange), as well as EEBUS Use Case specifications.

When answering, adhere to these technical guidelines:
1. Ground answers firmly in the retrieved context. If information is not in the context, explicitly state that it is not covered by the available EEBUS specifications.
2. Differentiate clearly between protocol layers:
   - SHIP: Transport, WebSocket, TLS 1.3, mDNS discovery, connection handshake state machines (CMI, Hello, PIN, Data Exchange).
   - SPINE: Application & domain layer, Resource Specifications, Datagrams, Function Sets, Command Frames (read, write, notify, ack).
   - Use Cases: Business logic (EVSE charging, Heat Pump control, Limitation of Power Production/Consumption).
3. Include exact technical identifiers, XML/JSON payload snippets, XSD data types, or state machine transitions whenever relevant.
4. Structure complex responses using clear headings, bullet points, and code blocks.
5. Provide precise document and section/page references based on the retrieved sources.
"""

CATEGORIZED_QUESTIONS = {
    "🔌 SHIP Protocol & Transport": [
        "What are the states in the SHIP connection handshake (SME)?",
        "How does mDNS discovery work in SHIP?",
        "What cipher suites are required for SHIP TLS 1.3?"
    ],
    "🧱 SPINE Architecture & Data Model": [
        "Explain the SPINE resource model: Device, Entity, and Feature.",
        "What are the SPINE message classifiers (read, write, notify)?",
        "How is access control and subscription handled in SPINE?"
    ],
    "⚡ Energy Use Cases": [
        "How does EVSE power limitation work in EEBUS Use Cases?",
        "What is the Limitation of Power Consumption (LPC) flow?",
        "How do Heartbeats maintain device connection alive status?"
    ]
}
