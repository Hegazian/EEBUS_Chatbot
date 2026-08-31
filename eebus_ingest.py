"""
EEBUS Documentation Ingestion Pipeline (Production)
===================================================
Ingests the EEBUS standard documentation corpus into ChromaDB (dense) and BM25 (sparse).

Features:
- Structure-Aware XSD & XML Parsing: Pristine XML elements (<complexType>, <simpleType>) intact.
- High-fidelity PDF extraction with page-level citations.
- Incremental document hashing (.doc_hashes.json) to skip unchanged files.
- Cross-platform path normalization (Linux/WSL & Windows compatible).
- High-accuracy embedding model (BAAI/bge-small-en-v1.5) calibrated to <=400 token chunks.
- Auto-syncs persistent BM25 index for Hybrid Retrieval.

Usage:
  python eebus_ingest.py           # Incremental ingestion (fast)
  python eebus_ingest.py --force   # Force full re-indexing from scratch
"""

import os
import sys
import hashlib
import json
import shutil
from pathlib import Path
import chromadb
from llama_index.core import (
    VectorStoreIndex,
    SimpleDirectoryReader,
    StorageContext,
    Settings,
)
from llama_index.core.schema import TextNode
from llama_index.core.node_parser import SentenceSplitter, MarkdownNodeParser
from llama_index.vector_stores.chroma import ChromaVectorStore

from core.config import (
    BASE_DIR, EEBUS_DIR, PERSIST_DIR, BM25_PERSIST_DIR, HASHES_FILE,
    COLLECTION_NAME, EXCLUDE_SEGMENTS
)
from core.parsers import (
    PyPDFReader, StructureAwareXSDParser, is_valid_text_content
)
from core.retriever import sync_bm25_from_chroma
from core.engine import get_embedding_model


# ─── Path & Metadata Helpers ───────────────────────────────────────────────────

def is_excluded_path(rel_path: str) -> bool:
    """Exclude software implementations (KEO), build artifacts, and editor caches."""
    parts = set(p.upper() for p in rel_path.replace("\\", "/").split("/"))
    return bool(parts & EXCLUDE_SEGMENTS)


def normalize_hash_key(rel_path: str) -> str:
    """Normalize file paths to forward-slashes for cross-platform hash consistency."""
    return rel_path.replace("\\", "/").lstrip("./")


def compute_file_hash(file_path: str) -> str:
    """Compute SHA-256 hash of a file."""
    hasher = hashlib.sha256()
    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(65536), b""):
            hasher.update(chunk)
    return hasher.hexdigest()


def get_current_hashes() -> dict:
    """Scan EEBUS directory and compute hashes for all supported files."""
    hashes = {}
    for root, _, files in os.walk(EEBUS_DIR):
        for f in files:
            ext = os.path.splitext(f)[1].lower()
            if ext in [".pdf", ".md", ".xsd", ".xml", ".txt"]:
                full_path = os.path.join(root, f)
                rel_path = normalize_hash_key(os.path.relpath(full_path, EEBUS_DIR))
                if is_excluded_path(rel_path):
                    continue
                hashes[rel_path] = compute_file_hash(full_path)
    return hashes


def file_metadata_extractor(file_path: str) -> dict:
    """Extract component, file type, document kind, subdomain, filename, and relative path metadata."""
    rel_path = os.path.relpath(file_path, EEBUS_DIR).replace("\\", "/")
    filename = os.path.basename(file_path)
    ext = os.path.splitext(filename)[1].lower()
    
    parts = rel_path.upper()
    
    # 1. Component classification (SHIP, SPINE, UseCase, General)
    top_folder = parts.split("/")[0] if "/" in parts else parts
    if "SHIP" in parts:
        component = "SHIP"
    elif "SPINE" in parts:
        component = "SPINE"
    elif any(k in parts for k in [
        "USE CASE", "USECASE", "USE_CASE", "UC_", "TEST CASE", "TEST_CASE",
        "E-MOBILITY", "GRID", "INVERTER", "HVAC", "14A", "LPC", "LPP", "MGCP", "MPC"
    ]) or any(k in top_folder for k in ["USE CASE", "TEST CASE", "TEST SPECIFICATION"]):
        component = "UseCase"
    else:
        component = "General"
    
    # 2. File type
    file_type = (
        "pdf" if ext == ".pdf"
        else "schema" if ext == ".xsd"
        else "markdown" if ext in [".md", ".markdown"]
        else "xml_example" if ext == ".xml"
        else "excel" if ext in [".xlsx", ".xls"]
        else "text"
    )

    # 3. Document Kind (specification, test, implementation guide, schema, example)
    if ext == ".xsd":
        doc_kind = "schema"
    elif ext == ".xml":
        doc_kind = "xml_example"
    elif "TEST" in parts:
        doc_kind = "test_specification"
    elif "IMPLEMENTATION GUIDES" in parts or "_IG_" in parts:
        doc_kind = "implementation_guide"
    elif "SPECIFICATION" in parts or "_TS_" in parts:
        doc_kind = "specification"
    elif "TECHNICAL REPORT" in parts or "_TR_" in parts:
        doc_kind = "technical_report"
    else:
        doc_kind = "documentation"

    # 4. Subdomain
    subdomain = "Core"
    if "E-MOBILITY" in parts:
        subdomain = "E-Mobility"
    elif "GRID" in parts or "14A" in parts:
        subdomain = "Grid & §14a"
    elif "INVERTER" in parts:
        subdomain = "Inverter & PV"
    elif "HVAC" in parts:
        subdomain = "HVAC & Heat Pump"
    elif "TEST" in parts:
        subdomain = "Testing & Conformance"
    
    return {
        "component": component,
        "file_type": file_type,
        "doc_kind": doc_kind,
        "subdomain": subdomain,
        "filename": filename,
        "rel_path": rel_path
    }


# ─── Main Ingestion Pipeline ────────────────────────────────────────────────────

def main():
    force_rebuild = "--force" in sys.argv or "--clean" in sys.argv

    print()
    print("╔══════════════════════════════════════════════════════════════╗")
    print("║     EEBUS Documentation Ingestion Pipeline (Production)      ║")
    print("╠══════════════════════════════════════════════════════════════╣")
    print(f"║  Source:     {EEBUS_DIR:<47s}║")
    print(f"║  ChromaDB:   {PERSIST_DIR:<47s}║")
    print(f"║  BM25 Store: {BM25_PERSIST_DIR:<47s}║")
    print(f"║  Mode:       {'FULL REBUILD (--force)' if force_rebuild else 'INCREMENTAL':<47s}║")
    print("╚══════════════════════════════════════════════════════════════╝")

    if not os.path.exists(EEBUS_DIR):
        print(f"\n❌ Error: The source directory '{EEBUS_DIR}' does not exist.")
        print("Please ensure the 'EEBUS' directory with standard documents is present.\n")
        sys.exit(1)

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
    
    if force_rebuild:
        if db_exists:
            print(f"\n🗑️  Force rebuild requested. Cleaning existing database at {PERSIST_DIR}...")
            shutil.rmtree(PERSIST_DIR)
            db_exists = False
            stored_hashes = {}
        if os.path.exists(BM25_PERSIST_DIR):
            shutil.rmtree(BM25_PERSIST_DIR)

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

    # Setup Embedding Model & ChromaDB Client
    Settings.embed_model = get_embedding_model()
    chroma_client = chromadb.PersistentClient(path=PERSIST_DIR)
    chroma_collection = chroma_client.get_or_create_collection(
        name=COLLECTION_NAME,
        metadata={"hnsw:space": "cosine"}
    )
    vector_store = ChromaVectorStore(chroma_collection=chroma_collection)
    storage_context = StorageContext.from_defaults(vector_store=vector_store)

    if db_exists and not added_or_modified and not deleted:
        print("\n✨ All EEBUS documents are up-to-date! No re-indexing required.")
        if not os.path.exists(BM25_PERSIST_DIR):
            sync_bm25_from_chroma(chroma_collection)
        with open(HASHES_FILE, "w", encoding="utf-8") as f:
            json.dump(current_hashes, f, indent=2)
        print(f"  Next step: Run the chatbot with  python qabot.py\n")
        return

    print(f"\n📊 Document Status:")
    print(f"  → Total files in EEBUS: {len(current_hashes)}")
    print(f"  → Added / Modified:     {len(added_or_modified)}")
    print(f"  → Deleted:              {len(deleted)}")

    # Clean outdated nodes if incremental
    if db_exists:
        for rel_path in added_or_modified + deleted:
            try:
                chroma_collection.delete(where={"rel_path": rel_path})
            except Exception:
                pass

    if not added_or_modified:
        if deleted or not os.path.exists(BM25_PERSIST_DIR):
            sync_bm25_from_chroma(chroma_collection)
        with open(HASHES_FILE, "w", encoding="utf-8") as f:
            json.dump(current_hashes, f, indent=2)
        print(f"✅ Database updated. Total active chunks in collection: {chroma_collection.count()}")
        return

    # Load and process documents
    print(f"\n📄 Loading and parsing {len(added_or_modified)} documents from {EEBUS_DIR}...")
    
    pdf_files = []
    md_files = []
    xsd_files = []
    xml_files = []
    txt_files = []
    
    for rel_path in added_or_modified:
        full_path = os.path.join(EEBUS_DIR, rel_path.replace("/", os.sep))
        ext = os.path.splitext(full_path)[1].lower()
        if ext == ".pdf":
            pdf_files.append(full_path)
        elif ext == ".xsd":
            xsd_files.append(full_path)
        elif ext == ".xml":
            xml_files.append(full_path)
        elif ext in [".md", ".markdown"]:
            md_files.append(full_path)
        elif ext == ".txt":
            txt_files.append(full_path)

    all_nodes = []

    # 1. Structure-Aware XSD Parsing (complexType, simpleType, element)
    if xsd_files:
        print(f"  📐 Parsing {len(xsd_files)} XSD schemas into structural XML nodes...")
        for xsd_path in xsd_files:
            meta = file_metadata_extractor(xsd_path)
            docs = StructureAwareXSDParser.parse_xsd_file(xsd_path, meta)
            for d in docs:
                all_nodes.append(TextNode(text=d.text, metadata=d.metadata))

    # 2. Structure-Aware XML Datagram Examples
    if xml_files:
        print(f"  📋 Parsing {len(xml_files)} XML datagram example files...")
        for xml_path in xml_files:
            meta = file_metadata_extractor(xml_path)
            docs = StructureAwareXSDParser.parse_xml_example(xml_path, meta)
            for d in docs:
                all_nodes.append(TextNode(text=d.text, metadata=d.metadata))

    # 3. PDF Files (Page-by-page extraction via PyPDFReader)
    if pdf_files:
        print(f"  📄 Loading {len(pdf_files)} PDF specifications via PyPDFReader...")
        pdf_reader = SimpleDirectoryReader(
            input_files=pdf_files,
            file_metadata=file_metadata_extractor,
            file_extractor={".pdf": PyPDFReader()}
        )
        raw_pdfs = pdf_reader.load_data()
        clean_pdfs = [p for p in raw_pdfs if is_valid_text_content(p.text)]
        pdf_splitter = SentenceSplitter(chunk_size=400, chunk_overlap=50)
        pdf_nodes = pdf_splitter.get_nodes_from_documents(clean_pdfs)
        all_nodes.extend([n for n in pdf_nodes if is_valid_text_content(n.get_content())])

    # 4. Markdown & Text Files
    if md_files or txt_files:
        print(f"  📝 Parsing Markdown and Text documentation...")
        other_files = md_files + txt_files
        reader = SimpleDirectoryReader(
            input_files=other_files,
            file_metadata=file_metadata_extractor
        )
        other_docs = reader.load_data()
        md_parser = MarkdownNodeParser()
        txt_splitter = SentenceSplitter(chunk_size=400, chunk_overlap=50)
        for doc in other_docs:
            if not is_valid_text_content(doc.text):
                continue
            if doc.metadata.get("file_type") == "markdown":
                all_nodes.extend(md_parser.get_nodes_from_documents([doc]))
            else:
                all_nodes.extend(txt_splitter.get_nodes_from_documents([doc]))

    print(f"\n🔢 Total pristine semantic nodes generated: {len(all_nodes):,}")

    # Ingest nodes into Index & ChromaDB
    print(f"\n🧠 Generating embeddings and updating ChromaDB...")
    index = VectorStoreIndex(
        all_nodes,
        storage_context=storage_context,
        show_progress=True
    )

    # Sync persistent BM25 index from full collection
    sync_bm25_from_chroma(chroma_collection)

    # Save updated hashes
    with open(HASHES_FILE, "w", encoding="utf-8") as f:
        json.dump(current_hashes, f, indent=2)

    total_chunks = chroma_collection.count()
    print()
    print("╔══════════════════════════════════════════════════════════════╗")
    print("║                    ✅  Ingestion Complete                   ║")
    print("╚══════════════════════════════════════════════════════════════╝")
    print(f"  → Processed documents:  {len(added_or_modified)}")
    print(f"  → Total database chunks: {total_chunks:,}")
    print("\n  Next step: Run the chatbot with  python qabot.py\n")


if __name__ == "__main__":
    main()
