"""
Verification Script: Phase 3 Session Isolation & Memory Protection
Verifies that datagram error diagnosis does not contaminate or pollute
the conversational ChatMemoryBuffer in Tab 1.
"""

import os
import sys

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from llama_index.core.memory import ChatMemoryBuffer
from llama_index.core.llms import ChatMessage, MessageRole
from llama_index.core.llms.mock import MockLLM
from llama_index.core.chat_engine import ContextChatEngine
from llama_index.core.schema import NodeWithScore, TextNode
from llama_index.core.retrievers import BaseRetriever

from tools.validator import validate_spine_datagram, diagnose_datagram_error, get_sample_datagrams


class DummyRetriever(BaseRetriever):
    def _retrieve(self, query_bundle):
        return [NodeWithScore(node=TextNode(text="EEBUS Protocol Context"), score=1.0)]


def run_phase3_verification():
    print("=" * 65)
    print("🛡️ Verifying Session Memory Isolation (Phase 3 Fixes)")
    print("=" * 65)

    mock_llm = MockLLM()
    memory = ChatMemoryBuffer.from_defaults(token_limit=8000)
    
    # Pre-seed user chat memory with 2 messages
    initial_messages = [
        ChatMessage(role=MessageRole.USER, content="Hello, what is SHIP?"),
        ChatMessage(role=MessageRole.ASSISTANT, content="SHIP is the Smart High-level Interface Protocol.")
    ]
    memory.set(initial_messages)
    
    chat_engine = ContextChatEngine.from_defaults(
        retriever=DummyRetriever(),
        memory=memory,
        llm=mock_llm
    )

    count_before = len(memory.get_all())
    print(f"  Initial Chat Memory Message Count: {count_before}")
    assert count_before == 2, f"Expected 2 messages, found {count_before}"

    # Run datagram validation and diagnosis
    samples = get_sample_datagrams()
    invalid_xml = samples["❌ Invalid: Illegal CmdClassifier Enum"]
    val_res = validate_spine_datagram(invalid_xml)
    assert not val_res["is_valid"], "Expected datagram to be invalid"

    print("  Triggering AI datagram diagnosis via diagnose_datagram_error()...")
    diag = diagnose_datagram_error(invalid_xml, val_res, chat_engine)
    print(f"  Diagnosis generated: {diag[:60]}...")

    # Check memory after diagnosis
    count_after = len(memory.get_all())
    print(f"  Chat Memory Message Count After Diagnosis: {count_after}")

    if count_after != count_before:
        print(f"  ❌ FAIL: Chat memory leaked! Count changed from {count_before} to {count_after}")
        return False

    # Verify memory contents do not contain any datagram validation prompt or error
    for msg in memory.get_all():
        if "failed schema validation" in str(msg.content) or "broadcast_alert" in str(msg.content):
            print(f"  ❌ FAIL: Validation error leaked into user chat memory: {msg.content}")
            return False

    print("  ✅ PASS: Datagram Inspector completely decoupled from conversational memory.")
    print("\n🎉 Phase 3 Session Isolation: ALL CHECKS PASSED!\n")
    return True


if __name__ == "__main__":
    success = run_phase3_verification()
    sys.exit(0 if success else 1)
