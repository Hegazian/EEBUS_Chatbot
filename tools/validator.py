"""
EEBUS SPINE Datagram Syntax & Schema Validator
Validates SPINE XML datagrams against official W3C XML Schemas (SPINE TS 1.3.0).
Extracts semantic headers and provides AI diagnostics for compliance errors.
"""

import os
import re
import xml.etree.ElementTree as ET
from typing import Dict, Any, Optional

try:
    import xmlschema
except ImportError:
    xmlschema = None

from core.config import BASE_DIR, EEBUS_DIR

_CANDIDATE_XSD_PATHS = [
    os.path.join(EEBUS_DIR, "EEBus_SPINE_V1.3.0_Final_hp", "XSDs", "EEBus_SPINE_TS_Datagram.xsd"),
    os.path.join(EEBUS_DIR, "EEBus_SPINE_V1.3.0", "XSDs", "EEBus_SPINE_TS_Datagram.xsd")
]
DATAGRAM_XSD_PATH = next((p for p in _CANDIDATE_XSD_PATHS if os.path.exists(p)), _CANDIDATE_XSD_PATHS[0])

_SCHEMA_CACHE: Optional[Any] = None


def get_datagram_schema() -> Optional[Any]:
    """Load and cache the SPINE Datagram XML Schema."""
    global _SCHEMA_CACHE
    if _SCHEMA_CACHE is not None:
        return _SCHEMA_CACHE

    if xmlschema is None:
        return None

    if os.path.exists(DATAGRAM_XSD_PATH):
        try:
            _SCHEMA_CACHE = xmlschema.XMLSchema(DATAGRAM_XSD_PATH)
            return _SCHEMA_CACHE
        except Exception as err:
            print(f"⚠️ Error loading SPINE Datagram schema ({err})")
            return None
    return None


def validate_spine_datagram(xml_content: str) -> Dict[str, Any]:
    """
    Validate a SPINE XML datagram string against EEBus_SPINE_TS_Datagram.xsd.
    Extracts header, addressing, command classifier, and payload functions.
    """
    result = {
        "is_valid": False,
        "error_type": None,
        "error_message": None,
        "error_path": None,
        "line_number": None,
        "header": {},
        "functions": [],
        "raw_xml": xml_content.strip()
    }

    if not xml_content or not xml_content.strip():
        result["error_type"] = "Empty Input"
        result["error_message"] = "Please provide an XML datagram string to validate."
        return result

    # 1. Basic XML Well-Formedness Check
    try:
        root = ET.fromstring(xml_content.strip())
    except ET.ParseError as pe:
        result["error_type"] = "XML Syntax Error"
        result["error_message"] = f"Malformed XML: {pe}"
        line_match = re.search(r'line (\d+)', str(pe))
        if line_match:
            result["line_number"] = int(line_match.group(1))
        return result

    tag_clean = root.tag.split("}")[-1] if "}" in root.tag else root.tag
    if tag_clean != "datagram":
        result["error_type"] = "Root Tag Mismatch"
        result["error_message"] = f"Expected root element '<datagram>', found '<{tag_clean}>'."
        return result

    # 2. Extract Semantic Fields (regardless of schema validity)
    def find_val(elem, path):
        parts = path.split("/")
        curr = elem
        for part in parts:
            found = None
            for child in curr:
                c_tag = child.tag.split("}")[-1] if "}" in child.tag else child.tag
                if c_tag == part:
                    found = child
                    break
            if found is None:
                return None
            curr = found
        return curr.text.strip() if curr is not None and curr.text else None

    header_el = None
    payload_el = None
    for child in root:
        c_tag = child.tag.split("}")[-1] if "}" in child.tag else child.tag
        if c_tag == "header":
            header_el = child
        elif c_tag == "payload":
            payload_el = child

    if header_el is not None:
        result["header"] = {
            "specificationVersion": find_val(header_el, "specificationVersion"),
            "msgCounter": find_val(header_el, "msgCounter"),
            "cmdClassifier": find_val(header_el, "cmdClassifier"),
            "addressSource": {
                "device": find_val(header_el, "addressSource/device"),
                "entity": find_val(header_el, "addressSource/entity"),
                "feature": find_val(header_el, "addressSource/feature"),
            },
            "addressDestination": {
                "device": find_val(header_el, "addressDestination/device"),
                "entity": find_val(header_el, "addressDestination/entity"),
                "feature": find_val(header_el, "addressDestination/feature"),
            },
            "timestamp": find_val(header_el, "timestamp")
        }

    if payload_el is not None:
        for cmd in payload_el:
            c_tag = cmd.tag.split("}")[-1] if "}" in cmd.tag else cmd.tag
            if c_tag == "cmd":
                func_name = find_val(cmd, "function")
                if func_name:
                    result["functions"].append(func_name)

    # 3. W3C Schema Validation via xmlschema
    if xmlschema is None:
        result["is_valid"] = False
        result["error_type"] = "Dependency Missing"
        result["error_message"] = "The 'xmlschema' library is not installed in the active environment. Please install it via 'pip install xmlschema'."
        return result

    schema = get_datagram_schema()
    if not schema:
        result["is_valid"] = False
        result["error_type"] = "Schema File Not Found"
        result["error_message"] = f"Official XSD schema file was not found at {DATAGRAM_XSD_PATH}. Schema validation could not be completed."
        return result

    try:
        schema.validate(xml_content.strip())
        result["is_valid"] = True
    except Exception as ve:
        result["is_valid"] = False
        if xmlschema is not None and isinstance(ve, getattr(xmlschema, "XMLSchemaValidationError", type(None))):
            result["error_type"] = "SPINE Schema Violation"
            clean_reason = getattr(ve, "reason", str(ve))
            result["error_message"] = f"{clean_reason}"
            result["error_path"] = getattr(ve, "path", None)
            result["line_number"] = getattr(ve, "sourceline", None)
        else:
            result["error_type"] = "SPINE Schema Processing Error"
            result["error_message"] = str(ve)

    return result


def diagnose_datagram_error(xml_content: str, validation_result: Dict[str, Any], chat_engine) -> str:
    """
    Use RAG context from the knowledge base to diagnose a validation failure and propose an exact fix.
    Retrieves authoritative schema definitions and specification clauses without polluting
    the conversational chat history buffer.
    """
    if validation_result.get("is_valid"):
        return "✅ Datagram is fully compliant with EEBUS SPINE Specification TS 1.3.0. No corrections required."

    error_type = validation_result.get("error_type", "Schema Error")
    error_msg = validation_result.get("error_message", "Unknown error")
    error_path = validation_result.get("error_path", "N/A")
    line_no = validation_result.get("line_number", "N/A")

    # 1. Extract search query targets from validation result
    funcs = validation_result.get("functions") or []
    header = validation_result.get("header") or {}
    cmd_class = header.get("cmdClassifier") or ""
    
    search_terms = []
    if funcs:
        search_terms.extend(funcs)
    if error_path and error_path not in ["Root", "N/A"]:
        clean_path_elem = str(error_path).rstrip("/").split("/")[-1].split(":")[-1]
        if clean_path_elem:
            search_terms.append(clean_path_elem)
    if cmd_class:
        search_terms.append(f"cmdClassifier {cmd_class}")
    
    query_str = f"SPINE Datagram schema {' '.join(search_terms)} {error_type}".strip()

    # 2. Retrieve grounded schema context using retriever from chat_engine
    context_chunks = []
    retriever = getattr(chat_engine, "_retriever", None) or getattr(chat_engine, "retriever", None)
    if retriever:
        try:
            retrieved_nodes = retriever.retrieve(query_str)
            for node in retrieved_nodes[:3]:
                snippet = node.node.get_content().strip() if hasattr(node, "node") else getattr(node, "text", "")
                if snippet:
                    meta = (node.node.metadata if hasattr(node, "node") else getattr(node, "metadata", {})) or {}
                    fname = meta.get("filename", "SPINE Specification")
                    context_chunks.append(f"--- Document: {fname} ---\n{snippet[:800]}")
        except Exception as ret_err:
            print(f"⚠️ Retrieval note during datagram diagnosis: {ret_err}")

    context_section = ""
    if context_chunks:
        context_section = "OFFICIAL EEBUS SPECIFICATION CONTEXT:\n" + "\n\n".join(context_chunks) + "\n\n"

    prompt = f"""{context_section}The following EEBUS SPINE Datagram failed schema validation:

Validation Error: {error_type}
Error Path: {error_path}
Line Number: {line_no}
Reason: {error_msg}

XML Payload:
```xml
{xml_content[:1500]}
```

As the EEBUS Protocol Expert:
1. Ground your diagnosis in the provided EEBUS specification context and SPINE TS 1.3.0 rules.
2. Explain specifically what is wrong (e.g. invalid enumeration, missing mandatory elements, incorrect tag names, or misplaced sequence).
3. Provide the corrected, fully compliant XML snippet.
"""
    try:
        llm = getattr(chat_engine, "_llm", None) or getattr(chat_engine, "llm", None)
        if llm:
            response = llm.complete(prompt)
            return str(response)
        return "⚠️ Diagnostic engine unavailable: isolated LLM completion interface not found on chat engine."
    except Exception as e:
        return f"⚠️ Diagnostic engine unavailable: {e}"


def get_sample_datagrams() -> Dict[str, str]:
    """Curated SPINE Datagram samples for testing and demonstration."""
    return {
        "✅ Valid: Device Classification Notify": """<?xml version="1.0" encoding="UTF-8"?>
<datagram xmlns="http://docs.eebus.org/spine/xsd/v1"
 xsi:schemaLocation="http://docs.eebus.org/spine/xsd/v1 file:../../XSDs/EEBus_SPINE_TS_Datagram.xsd"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <header>
        <specificationVersion>1.3.0</specificationVersion>
        <addressSource>
            <device>d:_i:46925_TestDevice-S</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressSource>
        <addressDestination>
            <device>d:_i:46925_TestDevice-C</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressDestination>
        <msgCounter>24</msgCounter>
        <cmdClassifier>notify</cmdClassifier>
        <timestamp>2023-08-31T10:00:00.0Z</timestamp>
    </header>
    <payload>
        <cmd>
            <function>deviceClassificationUserData</function>
            <deviceClassificationUserData>
                <userLabel>Smart Heat Pump Controller</userLabel>
            </deviceClassificationUserData>
        </cmd>
    </payload>
</datagram>""",

        "✅ Valid: LoadControl Read Request": """<?xml version="1.0" encoding="UTF-8"?>
<datagram xmlns="http://docs.eebus.org/spine/xsd/v1"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <header>
        <specificationVersion>1.3.0</specificationVersion>
        <addressSource>
            <device>d:_i:10001_EVSE-Station</device>
            <entity>1</entity>
            <feature>2</feature>
        </addressSource>
        <addressDestination>
            <device>d:_i:10002_EnergyManager</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressDestination>
        <msgCounter>105</msgCounter>
        <cmdClassifier>read</cmdClassifier>
    </header>
    <payload>
        <cmd>
            <function>loadControlLimitListData</function>
            <filter>
                <cmdControl>
                    <partial/>
                </cmdControl>
            </filter>
        </cmd>
    </payload>
</datagram>""",

        "❌ Invalid: Illegal CmdClassifier Enum": """<?xml version="1.0" encoding="UTF-8"?>
<datagram xmlns="http://docs.eebus.org/spine/xsd/v1"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <header>
        <specificationVersion>1.3.0</specificationVersion>
        <addressSource>
            <device>d:_i:10001_TestDevice</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressSource>
        <addressDestination>
            <device>d:_i:10002_RemoteDevice</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressDestination>
        <msgCounter>42</msgCounter>
        <cmdClassifier>broadcast_alert</cmdClassifier>
    </header>
    <payload>
        <cmd>
            <function>deviceDiagnosisStateData</function>
        </cmd>
    </payload>
</datagram>""",

        "❌ Invalid: Missing Required Payload Section": """<?xml version="1.0" encoding="UTF-8"?>
<datagram xmlns="http://docs.eebus.org/spine/xsd/v1"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <header>
        <specificationVersion>1.3.0</specificationVersion>
        <addressSource>
            <device>d:_i:10001_TestDevice</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressSource>
        <addressDestination>
            <device>d:_i:10002_TargetDevice</device>
            <entity>1</entity>
            <feature>1</feature>
        </addressDestination>
        <msgCounter>99</msgCounter>
        <cmdClassifier>notify</cmdClassifier>
    </header>
</datagram>"""
    }
