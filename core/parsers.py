"""
EEBUS Document Parsers
Includes PyPDFReader, StructureAwareXSDParser, and content filtering routines.
"""

import os
import re
import xml.etree.ElementTree as ET
from typing import List, Dict, Optional
from pypdf import PdfReader
from llama_index.core.readers.base import BaseReader
from llama_index.core.schema import Document


# ─── Content Sanitization Helpers ──────────────────────────────────────────────

def is_valid_text_content(text: str) -> bool:
    """Filter out binary noise, PDF raw streams, and malformed fragments."""
    if not text or len(text.strip()) < 20:
        return False
    pdf_stream_markers = ["/Filter", "/FlateDecode", "/FontDescriptor", "%PDF-", "/XObject", "endstream", "endobj"]
    if sum(1 for m in pdf_stream_markers if m in text) >= 2:
        return False
    non_printable = sum(1 for c in text if ord(c) < 32 and c not in '\n\r\t')
    if non_printable / len(text) > 0.05:
        return False
    return True


def is_clean_node(text: str) -> bool:
    """Validate retrieved node text before displaying in citation cards."""
    return is_valid_text_content(text)


# ─── High-Fidelity PyPDFReader ──────────────────────────────────────────────────

class PyPDFReader(BaseReader):
    """
    Robust PDF Reader that extracts text page-by-page and captures accurate page labels.
    """
    def load_data(self, file_path: str, extra_info: Optional[Dict] = None) -> List[Document]:
        documents = []
        try:
            reader = PdfReader(file_path)
            for idx, page in enumerate(reader.pages):
                page_text = page.extract_text() or ""
                page_text = page_text.strip()
                if not is_valid_text_content(page_text):
                    continue
                metadata = dict(extra_info or {})
                metadata["page_label"] = idx + 1
                metadata["total_pages"] = len(reader.pages)
                documents.append(Document(text=page_text, metadata=metadata))
        except Exception as e:
            print(f"⚠️ Warning loading PDF '{os.path.basename(file_path)}': {e}")
        return documents


# ─── Structure-Aware XSD & XML Parser ──────────────────────────────────────────

class StructureAwareXSDParser:
    """
    Parses XSD specifications into self-contained, valid structural units
    (complexType, simpleType, element) preserving XML hierarchy, documentation,
    and type definitions.
    """
    @staticmethod
    def parse_xsd_file(file_path: str, base_metadata: Optional[Dict] = None) -> List[Document]:
        documents = []
        filename = os.path.basename(file_path)
        meta_base = dict(base_metadata or {})
        
        try:
            tree = ET.parse(file_path)
            root = tree.getroot()
            
            # Find targetNamespace and version
            target_ns = root.attrib.get("targetNamespace", "")
            version = root.attrib.get("version", "")
            
            header_doc = f"<!-- Schema: {filename} | TargetNamespace: {target_ns} | Version: {version} -->"

            for child in root:
                tag = child.tag.split("}")[-1] if "}" in child.tag else child.tag
                if tag in ["complexType", "simpleType", "element", "group", "attributeGroup"]:
                    name = child.attrib.get("name", "")
                    if not name:
                        continue
                    
                    xml_repr = ET.tostring(child, encoding="unicode").strip()
                    
                    # Clean redundant root-level namespace prefixes for cleaner LLM context
                    xml_repr = re.sub(r'\s+xmlns(:\w+)?="[^"]+"', '', xml_repr)
                    
                    content = f"{header_doc}\n<{tag} name=\"{name}\">\n{xml_repr}\n</{tag}>" if not xml_repr.startswith(f"<{tag}") else f"{header_doc}\n{xml_repr}"
                    
                    doc_meta = dict(meta_base)
                    doc_meta["schema_element_type"] = tag
                    doc_meta["schema_element_name"] = name
                    doc_meta["file_type"] = "schema"
                    
                    documents.append(Document(text=content, metadata=doc_meta))
                    
        except Exception as e:
            print(f"⚠️ Structure-aware XSD parse failed for '{filename}' ({e}). Falling back to raw text.")
            try:
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    raw_text = f.read()
                if is_valid_text_content(raw_text):
                    doc_meta = dict(meta_base)
                    doc_meta["file_type"] = "schema"
                    documents.append(Document(text=raw_text, metadata=doc_meta))
            except Exception:
                pass
                
        return documents

    @staticmethod
    def parse_xml_example(file_path: str, base_metadata: Optional[Dict] = None) -> List[Document]:
        """Loads intact SPINE datagram examples."""
        filename = os.path.basename(file_path)
        meta_base = dict(base_metadata or {})
        try:
            with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read().strip()
            if is_valid_text_content(content):
                meta_base["file_type"] = "xml_example"
                return [Document(text=content, metadata=meta_base)]
        except Exception as e:
            print(f"⚠️ Warning loading XML example '{filename}': {e}")
        return []
