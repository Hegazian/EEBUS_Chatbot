"""
Verification Script: Phase 4 Datagram Validator & State Machines
Tests W3C schema validation across all 4 sample datagrams, semantic header extraction,
and verifies state machine models and TLS 1.2 protocol alignment.
"""

import os
import sys

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from tools.validator import validate_spine_datagram, get_sample_datagrams
from tools.state_machine import get_state_machine_data, STATE_MACHINES


def run_phase4_verification():
    print("=" * 65)
    print("🔬 Verifying Datagram Validator & State Machines (Phase 4)")
    print("=" * 65)

    # 1. Test Datagram Validation
    samples = get_sample_datagrams()
    print(f"  Testing {len(samples)} curated sample datagrams...")

    # Sample 1: Valid Device Classification
    s1 = samples["✅ Valid: Device Classification Notify"]
    v1 = validate_spine_datagram(s1)
    print(f"   • Sample 1 (Notify): valid={v1['is_valid']}")
    assert v1["is_valid"], f"Sample 1 should be valid: {v1.get('error_message')}"
    assert v1["header"]["cmdClassifier"] == "notify"
    assert "deviceClassificationUserData" in v1["functions"]

    # Sample 2: Valid LoadControl Read
    s2 = samples["✅ Valid: LoadControl Read Request"]
    v2 = validate_spine_datagram(s2)
    print(f"   • Sample 2 (Read): valid={v2['is_valid']}")
    assert v2["is_valid"], f"Sample 2 should be valid: {v2.get('error_message')}"
    assert v2["header"]["cmdClassifier"] == "read"

    # Sample 3: Invalid Illegal CmdClassifier
    s3 = samples["❌ Invalid: Illegal CmdClassifier Enum"]
    v3 = validate_spine_datagram(s3)
    print(f"   • Sample 3 (Illegal Enum): valid={v3['is_valid']} (error: {v3.get('error_type')})")
    assert not v3["is_valid"], "Sample 3 should be invalid"
    assert v3["error_type"] in ["SPINE Schema Violation", "Schema Error"]

    # Sample 4: Invalid Missing Payload
    s4 = samples["❌ Invalid: Missing Required Payload Section"]
    v4 = validate_spine_datagram(s4)
    print(f"   • Sample 4 (Missing Payload): valid={v4['is_valid']}")
    assert not v4["is_valid"], "Sample 4 should be invalid"

    print("  ✅ All 4 datagram samples validated with 100% expected compliance outcomes.")

    # 2. Test State Machine Models & Protocol Alignment
    print("\n  Verifying Protocol State Machine Models...")
    expected_keys = ["ship_sme", "spine_subscription", "spine_binding"]
    for key in expected_keys:
        data = get_state_machine_data(key)
        assert data is not None, f"State machine {key} not found"
        assert len(data["mermaid"]) > 50, f"Mermaid graph empty for {key}"
        assert len(data["states"]) > 0, f"States list empty for {key}"
        print(f"   • {data['title']}: {len(data['states'])} states, {len(data['mermaid'])} chars Mermaid")

    # Check SHIP TLS version alignment (TLS 1.2 per RFC 5246, not TLS 1.3)
    ship_data = get_state_machine_data("ship_sme")
    assert "TLS 1.2" in ship_data["mermaid"], "SHIP state machine Mermaid must reference TLS 1.2"
    assert "TLS 1.3" not in ship_data["mermaid"], "SHIP state machine Mermaid must NOT reference TLS 1.3"
    print("  ✅ Protocol Accuracy: SHIP SME correctly mandates TLS 1.2 (RFC 5246).")

    print("\n🎉 Phase 4 Validator & State Machines: ALL CHECKS PASSED!\n")
    return True


if __name__ == "__main__":
    success = run_phase4_verification()
    sys.exit(0 if success else 1)
