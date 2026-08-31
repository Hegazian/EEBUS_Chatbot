"""
EEBUS UI Tabs Package
"""
from .chat_tab import create_chat_tab
from .inspector_tab import create_inspector_tab
from .state_machines_tab import create_state_machines_tab
from .benchmark_tab import create_benchmark_tab

__all__ = [
    "create_chat_tab",
    "create_inspector_tab",
    "create_state_machines_tab",
    "create_benchmark_tab",
]
