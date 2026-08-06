"""
EEBUS Documentation Ingestion Pipeline (LlamaIndex) — Upgraded Production Version
===================================================================================
Processes the EEBUS standard documentation corpus into a persistent ChromaDB vector store.

Features:
- PDF Stream Noise Filtering: Automatically cleans/filters out corrupt binary PDF stream text.
- Incremental document hashing (.doc_hashes.json): skips unchanged files (ms updates).
- Cross-platform path normalization (Linux/WSL & Windows compatible).
- Type-aware chunking for PDFs, Markdown, XSD schemas, and XML datagrams.
- High-accuracy embedding model (BAAI/bge-small-en-v1.5).
- Enriched metadata (component, file type, relative path, page citations).

Usage:
  python eebus_ingest.py           # Incremental ingestion (fast)
  python eebus_ingest.py --force   # Force full re-indexing from scratch
"""

import os
import sys
import hashlib
import json
import shutil
import chromadb
from llama_index.core import (
    VectorStoreIndex,
    SimpleDirectoryReader,
    StorageContext,
    Settings,
)
from llama_index.core.node_parser import SentenceSplitter, MarkdownNodeParser
from llama_index.embeddings.huggingface import HuggingFaceEmbedding
from llama_index.vector_stores.chroma import ChromaVectorStore

# ─── Configuration ──────────────────────────────────────────────────────────────

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
EEBUS_DIR = os.path.join(BASE_DIR, "EEBUS")
PERSIST_DIR = os.path.join(BASE_DIR, "eebus_chroma_db")
HASHES_FILE = os.path.join(BASE_DIR, ".doc_hashes.json")
COLLECTION_NAME = "eebus_docs"
PRIMARY_EMBEDDING_MODEL = "BAAI/bge-small-en-v1.5"
FALLBACK_EMBEDDING_MODEL = "all-MiniLM-L6-v2"

# ─── Embedding Setup ────────────────────────────────────────────────────────────

def init_embedding_model():
    """Initialize BGE-small embedding model with automatic fallback."""
    try:
        print(f"⚙️  Loading embedding model ({PRIMARY_EMBEDDING_MODEL})...")
        return HuggingFaceEmbedding(model_name=PRIMARY_EMBEDDING_MODEL)
    except Exception as err:
        print(f"⚠️ Could not load {PRIMARY_EMBEDDING_MODEL} ({err}). Falling back to {FALLBACK_EMBEDDING_MODEL}...")
        return HuggingFaceEmbedding(model_name=FALLBACK_EMBEDDING_MODEL)


# ─── Text Sanitize & Noise Filter ──────────────────────────────────────────────

def is_valid_text_content(text: str) -> bool:
    """Check if extracted text is readable content and not raw/encoded PDF stream garbage."""
    if not text or len(text.strip()) < 25:
        return False
    
    # PDF stream markers commonly found in corrupt extracted text
    pdf_stream_markers = [
        "/Filter", "/FlateDecode", "/FontDescriptor", "%PDF-",
        "/XObject", "/MediaBox", "/Length ", "endstream", "endobj"
    ]
    
    marker_count = sum(1 for m in pdf_stream_markers if m in text)
    if marker_count >= 2:
        return False
        
    # Check ratio of printable characters
    printable_count = sum(1 for c in text if c.isprintable() or c in "\n\r\t")
    if len(text) > 0 and (printable_count / len(text)) < 0.85:
        return False
        
    return True


# ─── Metadata Extractor ─────────────────────────────────────────────────────────

def file_metadata_extractor(file_path: str) -> dict:
    """Extract component, file type, filename, and relative path metadata for each file."""
    parts = file_path.upper()
    component = "General"
    if "SHIP" in parts:
        component = "SHIP"
    elif "SPINE" in parts:
        component = "SPINE"
    elif "UC_" in parts or "USECASE" in parts:
        component = "UseCase"
        
    rel_path = os.path.relpath(file_path, EEBUS_DIR).replace("\\", "/")
    filename = os.path.basename(file_path)
    ext = os.path.splitext(filename)[1].lower()
    
    file_type = "pdf" if ext == ".pdf" else "schema" if ext == ".xsd" else "markdown" if ext in [".md", ".markdown"] else "xml_example" if ext == ".xml" else "text"
    
    return {
        "component": component,
        "filename": filename,
        "rel_path": rel_path,
        "file_type": file_type,
    }


# ─── Hashing & Incremental Ingestion Helpers ─────────────────────────────────────

def normalize_hash_key(key: str) -> str:
    """Normalize absolute paths or relative paths to standard relative format (cross-platform)."""
    norm = key.replace("\\", "/")
    if "/EEBUS/" in norm:
        norm = norm.split("/EEBUS/", 1)[1]
    elif "\\EEBUS\\" in key:
        norm = key.split("\\EEBUS\\", 1)[1].replace("\\", "/")
    return norm.lstrip("/")


def compute_file_hash(filepath: str) -> str:
    """Compute MD5 checksum of a file."""
    hasher = hashlib.md5()
    with open(filepath, "rb") as f:
        while chunk := f.read(65536):
            hasher.update(chunk)
    return hasher.hexdigest()


def get_current_hashes() -> dict:
    """Scan EEBUS directory and calculate current file hashes using normalized relative keys."""
    hashes = {}
    for root, _, files in os.walk(EEBUS_DIR):
        for f in files:
            ext = os.path.splitext(f)[1].lower()
            if ext in [".pdf", ".md", ".xsd", ".xml", ".txt"] and not any(k in f.upper() for k in ["KEO", ".XPR", "__PYCACHE__"]):
                full_path = os.path.join(root, f)
                rel_path = normalize_hash_key(os.path.relpath(full_path, EEBUS_DIR))
                hashes[rel_path] = compute_file_hash(full_path)
    return hashes


# ─── Main Ingestion Pipeline ────────────────────────────────────────────────────

def main():
    force_rebuild = "--force" in sys.argv or "--clean" in sys.argv

    print()
    print("╔══════════════════════════════════════════════════════════════╗")
    print("║     EEBUS Documentation Ingestion Pipeline (Production)      ║")
    print("╠══════════════════════════════════════════════════════════════╣")
    print(f"║  Source:     {EEBUS_DIR:<47s}║")
    print(f"║  Store:      {PERSIST_DIR:<47s}║")
    print(f"║  Mode:       {'FULL REBUILD (--force)' if force_rebuild else 'INCREMENTAL':<47s}║")
    print("╚══════════════════════════════════════════════════════════════╝")

    current_hashes = get_current_hashes()
    stored_hashes = {}
    
    if os.path.exists(HASHES_FILE) and not force_rebuild:
        try:
            with open(HASHES_FILE, "r", encoding="utf-8") as f:
                raw_hashes = json.load(f)
                stored_hashes = {normalize_hash_key(k): v for k, v in raw_hashes.items()}
        except Exception:
            stored_hashes = {}

    db_exists = os.path.exists(PERSIST_DIR)
    
    if force_rebuild and db_exists:
        print(f"\n🗑️  Force rebuild requested. Cleaning existing database at {PERSIST_DIR}...")
        shutil.rmtree(PERSIST_DIR)
        db_exists = False
        stored_hashes = {}

    # Determine file delta
    added_or_modified = []
    deleted = []
    
    if not db_exists or not stored_hashes:
        added_or_modified = list(current_hashes.keys())
    else:
        for rel_path, h in current_hashes.items():
            if rel_path not in stored_hashes or stored_hashes[rel_path] != h:
                added_or_modified.append(rel_path)
        for rel_path in stored_hashes:
            if rel_path not in current_hashes:
                deleted.append(rel_path)

    if db_exists and not added_or_modified and not deleted:
        print("\n✨ All EEBUS documents are up-to-date! No re-indexing required.")
        print("  Next step: Run the chatbot with  python qabot_gemini.py\n")
        
        with open(HASHES_FILE, "w", encoding="utf-8") as f:
            json.dump(current_hashes, f, indent=2)
        return

    print(f"\n📊 Change Detection: {len(added_or_modified)} added/modified files, {len(deleted)} deleted files.")

    # Initialize global settings
    Settings.embed_model = init_embedding_model()

    # 1. Connect to ChromaDB
    print("\n⚙️  Connecting to ChromaDB persistent storage...")
    db = chromadb.PersistentClient(path=PERSIST_DIR)
    chroma_collection = db.get_or_create_collection(COLLECTION_NAME)
    vector_store = ChromaVectorStore(chroma_collection=chroma_collection)
    storage_context = StorageContext.from_defaults(vector_store=vector_store)

    # 2. Clean outdated nodes if incremental
    if db_exists:
        for rel_path in added_or_modified + deleted:
            try:
                chroma_collection.delete(where={"rel_path": rel_path})
            except Exception:
                pass

    if not added_or_modified:
        with open(HASHES_FILE, "w", encoding="utf-8") as f:
            json.dump(current_hashes, f, indent=2)
        print(f"✅ Database updated. Total active chunks in collection: {chroma_collection.count()}")
        return

    # 3. Load documents for added / modified files
    print(f"\n📄 Loading {len(added_or_modified)} documents from {EEBUS_DIR}...")
    target_paths = [os.path.join(EEBUS_DIR, rel_path.replace("/", os.sep)) for rel_path in added_or_modified]
    
    reader = SimpleDirectoryReader(
        input_files=target_paths,
        file_metadata=file_metadata_extractor
    )
    raw_documents = reader.load_data()
    print(f"  → Loaded {len(raw_documents)} raw document pages/sections.")

    # Clean raw documents
    documents = []
    for doc in raw_documents:
        if is_valid_text_content(doc.text):
            documents.append(doc)
            
    print(f"  → Retained {len(documents)} clean document sections after noise filtering.")

    # 4. Type-Aware Splitters & Node Generation
    print(f"\n🔢 Chunking documents with type-aware splitters...")
    
    md_parser = MarkdownNodeParser()
    standard_splitter = SentenceSplitter(chunk_size=1200, chunk_overlap=150)
    code_splitter = SentenceSplitter(chunk_size=900, chunk_overlap=100)

    nodes = []
    for doc in documents:
        file_type = doc.metadata.get("file_type", "")
        if file_type == "markdown":
            doc_nodes = md_parser.get_nodes_from_documents([doc])
        elif file_type in ["schema", "xml_example"]:
            doc_nodes = code_splitter.get_nodes_from_documents([doc])
        else:
            doc_nodes = standard_splitter.get_nodes_from_documents([doc])
            
        for n in doc_nodes:
            if is_valid_text_content(n.get_content()):
                nodes.append(n)

    print(f"  → Created {len(nodes)} clean semantic nodes.")

    # 5. Ingest nodes into Index & ChromaDB
    print(f"\n🧠 Generating embeddings and updating ChromaDB...")
    index = VectorStoreIndex(
        nodes,
        storage_context=storage_context,
        show_progress=True
    )

    # 6. Save updated normalized hashes
    with open(HASHES_FILE, "w", encoding="utf-8") as f:
        json.dump(current_hashes, f, indent=2)

    total_chunks = chroma_collection.count()
    print()
    print("╔══════════════════════════════════════════════════════════════╗")
    print("║                    ✅  Ingestion Complete                   ║")
    print("╚══════════════════════════════════════════════════════════════╝")
    print(f"  → Processed documents:  {len(added_or_modified)}")
    print(f"  → Total database chunks: {total_chunks:,}")
    print("\n  Next step: Run the chatbot with  python qabot_gemini.py\n")


if __name__ == "__main__":
    main()
