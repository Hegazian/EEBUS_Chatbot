"""
EEBUS Chatbot Configuration
Centralized configuration, paths, defaults, and system prompts.
"""

import os
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

try:
    from dotenv import load_dotenv
    load_dotenv(os.path.join(BASE_DIR, ".env"), override=True)
except ImportError:
    pass

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
   - SHIP: Transport, WebSocket, TLS 1.2 (RFC 5246), mDNS discovery, connection handshake state machines (CMI, Hello, PIN, Data Exchange).
   - SPINE: Application & domain layer, Resource Specifications, Datagrams, Function Sets, Command Frames (read, write, notify, ack).
   - Use Cases: Business logic (EVSE charging, Heat Pump control, Limitation of Power Production/Consumption).
3. Include exact technical identifiers, XML/JSON payload snippets, XSD data types, or state machine transitions whenever relevant.
4. Structure complex responses using clear headings, bullet points, and code blocks.
5. Provide precise document and section/page references based on the retrieved sources.
"""

USER_ROLES = {
    "💻 Software Developer": {
        "title": "Software Developer & Implementer",
        "description": "Focuses on concrete data types, XSD schemas, code structures, and datagram implementation.",
        "instruction": (
            "The user is a Software Developer implementing EEBUS (SHIP/SPINE) in code. "
            "Tailor your response to concrete implementation details: provide exact XSD data types, "
            "syntactically valid XML or JSON datagram snippets, function identifiers, WebSocket/TLS socket considerations, "
            "and pragmatic programming patterns."
        )
    },
    "🧪 QA & Test Engineer": {
        "title": "QA & Conformance Test Engineer",
        "description": "Focuses on boundary testing, timeout constraints, negative scenarios, and error states.",
        "instruction": (
            "The user is a QA / Test Engineer validating EEBUS implementations against specifications. "
            "Tailor your response to test scenarios, protocol edge cases, timeout timers (e.g. T_hello_init, T_hello_prolong, T_pin_verify), "
            "invalid datagram structures, expected error codes/results, and strict conformance verification criteria."
        )
    },
    "🏛️ Systems Architect": {
        "title": "Systems & Solutions Architect",
        "description": "Focuses on device topologies, resource models (Device/Entity/Feature), and system scalability.",
        "instruction": (
            "The user is a Systems / Solutions Architect designing smart energy and IoT ecosystems (HEMS/EMS). "
            "Tailor your response to architectural topologies, the Device/Entity/Feature resource hierarchy, "
            "separation of concerns between transport (SHIP) and application (SPINE), security trust models, and multi-device scalability."
        )
    },
    "📋 Compliance & Certification": {
        "title": "Compliance & Certification Specialist",
        "description": "Focuses on formal specification clauses, RFC 2119 keywords, and official Use Case requirements.",
        "instruction": (
            "The user is an EEBUS Compliance & Certification Specialist. "
            "Tailor your response to formal specification clauses, normative vs. informative text, "
            "RFC 2119 requirement keywords (MUST, SHALL, SHOULD, MAY), specification version compatibility, "
            "and official EEBUS Use Case certification checklists."
        )
    },
    "🔧 Field & Commissioning Engineer": {
        "title": "Field & Commissioning Engineer",
        "description": "Focuses on mDNS discovery, on-site pairing, TLS certificate exchange, and network diagnostics.",
        "instruction": (
            "The user is a Field & Commissioning Engineer installing and diagnosing devices on-site. "
            "Tailor your response to real-world deployment workflows: mDNS/DNS-SD discovery, PIN authentication pairing, "
            "TLS certificate exchange, firewall/network configuration, and diagnosing connection dropouts."
        )
    }
}

DEFAULT_USER_ROLE = "💻 Software Developer"


def get_system_prompt_for_role(role_key: str = DEFAULT_USER_ROLE) -> str:
    """Combine base EEBUS protocol prompt with role-specific engineering directive."""
    role_info = USER_ROLES.get(role_key, USER_ROLES[DEFAULT_USER_ROLE])
    role_directive = (
        f"\n\nUSER ENGINEERING ROLE DIRECTIVE ({role_info['title']}):\n"
        f"{role_info['instruction']}"
    )
    return SYSTEM_PROMPT.strip() + role_directive

CATEGORIZED_QUESTIONS = {
    "🔌 SHIP Protocol & Transport": [
        "What are the states in the SHIP connection handshake (SME)?",
        "How does mDNS discovery work in SHIP?",
        "What cipher suites are required for SHIP TLS 1.2?"
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
