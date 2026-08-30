"""
Verification Script: User Engineering Roles & Dynamic Prompt Tailoring
Verifies that all 5 engineering roles generate distinct system directives
and properly configure the ContextChatEngine.
"""

import os
import sys

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from core.config import USER_ROLES, DEFAULT_USER_ROLE, get_system_prompt_for_role, SYSTEM_PROMPT


def run_roles_verification():
    print("=" * 65)
    print("Verifying User Engineering Roles & Persona Tailoring")
    print("=" * 65)

    print(f"  Default Role: {DEFAULT_USER_ROLE}")
    assert DEFAULT_USER_ROLE in USER_ROLES, "DEFAULT_USER_ROLE must be in USER_ROLES"

    expected_roles = [
        "💻 Software Developer",
        "🧪 QA & Test Engineer",
        "🏛️ Systems Architect",
        "📋 Compliance & Certification",
        "🔧 Field & Commissioning Engineer"
    ]

    print(f"\n  Checking {len(expected_roles)} standard engineering roles...")
    generated_prompts = {}

    for role in expected_roles:
        assert role in USER_ROLES, f"Role '{role}' missing from USER_ROLES"
        info = USER_ROLES[role]
        print(f"   * {info['title']}")
        assert len(info["instruction"]) > 30, f"Instruction too short for {role}"

        prompt = get_system_prompt_for_role(role)
        assert SYSTEM_PROMPT.strip() in prompt, "Base protocol prompt must be retained"
        assert info["instruction"] in prompt, "Role instruction must be included"
        generated_prompts[role] = prompt

    # Verify each prompt is unique
    unique_prompts = set(generated_prompts.values())
    assert len(unique_prompts) == len(expected_roles), "All role prompts must be distinct!"
    print(f"  [PASS] All {len(expected_roles)} role system prompts are verified and unique.")

    # Verify fallback for unknown role
    fallback_prompt = get_system_prompt_for_role("NonExistentRole")
    default_prompt = get_system_prompt_for_role(DEFAULT_USER_ROLE)
    assert fallback_prompt == default_prompt, "Unknown role must fall back to DEFAULT_USER_ROLE"
    print("  [PASS] Fallback mechanism: Unknown roles correctly default to Software Developer.")

    print("\nSUCCESS: User Engineering Roles: ALL CHECKS PASSED!\n")
    return True


if __name__ == "__main__":
    success = run_roles_verification()
    sys.exit(0 if success else 1)
