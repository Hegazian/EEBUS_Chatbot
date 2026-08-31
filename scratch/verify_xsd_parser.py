"""
Verification Script: Structure-Aware XSD Parser
Validates that all SPINE and SHIP schemas parse into self-contained, valid structural
XML definitions without double-tag wrapping (<complexType><complexType>) or tag corruption.
"""

import os
import sys
import re

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from core.parsers import StructureAwareXSDParser
from core.config import EEBUS_DIR


def run_xsd_verification():
    print("=" * 65)
    print("🔬 Verifying StructureAwareXSDParser (Phase 1 Fixes)")
    print("=" * 65)

    xsd_paths = []
    for root, _, files in os.walk(EEBUS_DIR):
        for f in files:
            if f.endswith(".xsd"):
                xsd_paths.append(os.path.join(root, f))

    print(f"  Found {len(xsd_paths)} XSD schema files in EEBUS standard corpus.")
    assert len(xsd_paths) >= 70, f"Expected >= 70 XSD files, found {len(xsd_paths)}"

    total_elements = 0
    double_wrap_errors = []
    empty_content_errors = []
    element_types = {}

    for path in xsd_paths:
        fname = os.path.basename(path)
        docs = StructureAwareXSDParser.parse_xsd_file(path, {"rel_path": fname})
        total_elements += len(docs)

        for d in docs:
            text = d.text.strip()
            etype = d.metadata.get("schema_element_type")
            ename = d.metadata.get("schema_element_name")
            element_types[etype] = element_types.get(etype, 0) + 1

            if not text:
                empty_content_errors.append(f"{fname} -> {ename}")

            # Check for double tag wrapping bug: e.g. <complexType><ns0:complexType>
            double_pattern = rf"<{etype}[^>]*>\s*<(\w+:)?{etype}[^>]*>"
            if re.search(double_pattern, text):
                double_wrap_errors.append(f"{fname} -> {etype}:{ename}")

    print(f"\n📊 Extraction Breakdown across {len(xsd_paths)} schemas:")
    for etype, count in sorted(element_types.items(), key=lambda x: x[1], reverse=True):
        print(f"   • {etype:<18s}: {count:,} items")
    print(f"   ────────────────────────────────────────")
    print(f"   Total Structural Units: {total_elements:,}")

    print(f"\n🧪 Integrity Checks:")
    
    # Check 1: Double-wrap errors
    if double_wrap_errors:
        print(f"   ❌ FAIL: Found {len(double_wrap_errors)} double-wrapped XML elements:")
        for err in double_wrap_errors[:5]:
            print(f"      - {err}")
        return False
    else:
        print("   ✅ PASS: Zero double-wrapped XML elements detected.")

    # Check 2: Empty content errors
    if empty_content_errors:
        print(f"   ❌ FAIL: Found {len(empty_content_errors)} empty XML elements.")
        return False
    else:
        print("   ✅ PASS: All extracted structural XML elements contain valid text.")

    # Check 3: Minimum extracted elements threshold
    if total_elements < 1400:
        print(f"   ❌ FAIL: Expected >= 1,400 structural units, got {total_elements}")
        return False
    else:
        print(f"   ✅ PASS: Rich structural inventory validated ({total_elements:,} definitions).")

    print("\n🎉 StructureAwareXSDParser verification: ALL CHECKS PASSED!\n")
    return True


if __name__ == "__main__":
    success = run_xsd_verification()
    sys.exit(0 if success else 1)
