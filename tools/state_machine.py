"""
EEBUS Protocol State Machine Models & Visualizers
Interactive Mermaid diagrams and state transition specifications for SHIP and SPINE.
"""

from typing import Dict, Any, List


STATE_MACHINES = {
    "ship_sme": {
        "title": "🔌 SHIP SME (Connection Handshake State Machine)",
        "standard": "EEBus SHIP TS Specification v1.1.0 — Section 12",
        "description": (
            "The State Machine Entity (SME) governs peer connection lifecycle in SHIP, "
            "including mDNS discovery, TLS 1.2 mutual authentication, CMI hello handshake, "
            "PIN verification, and transition to active SPINE data exchange."
        ),
        "mermaid": """graph TD
    classDef initStyle fill:#1e293b,stroke:#64748b,stroke-width:2px,color:#f8fafc;
    classDef handshakeStyle fill:#1e1b4b,stroke:#818cf8,stroke-width:2px,color:#f8fafc;
    classDef activeStyle fill:#064e3b,stroke:#34d399,stroke-width:2px,color:#f8fafc;
    classDef errorStyle fill:#450a0a,stroke:#f87171,stroke-width:2px,color:#f8fafc;

    S0((Start)) --> S1[sme_cmi_state_init]:::initStyle
    S1 -->|mDNS Discover| S2[sme_cmi_state_listen / client_send]:::initStyle
    S2 -->|TCP/TLS 1.2 Connected| S3[sme_hello_state_ready]:::handshakeStyle
    S3 -->|C_HELLO Msg Exchange| S4[sme_hello_state_ok]:::handshakeStyle
    S4 -->|Protocol Check| S5[sme_prot_h_state_client_init]:::handshakeStyle
    S5 -->|Protocol Approved| S6{PIN Required?}:::handshakeStyle
    S6 -->|Yes| S7[sme_pin_state_check]:::handshakeStyle
    S6 -->|No| S8[sme_approved]:::activeStyle
    S7 -->|PIN Validated| S8
    S8 -->|Access Methods Negotiated| S9[sme_complete / Data Exchange]:::activeStyle
    
    S3 -.->|Timeout / Rejected| S_ERR[sme_error / Close Connection]:::errorStyle
    S5 -.->|Version Mismatch| S_ERR
    S7 -.->|Invalid PIN| S_ERR
""",
        "states": [
            {
                "state": "sme_cmi_state_init",
                "phase": "Initialization",
                "trigger": "Device power up or network interface ready",
                "timeout": "None",
                "description": "Initializes SHIP stack, loads local certificates, and prepares mDNS service advertisement."
            },
            {
                "state": "sme_hello_state_ready",
                "phase": "Hello Handshake",
                "trigger": "WebSocket connection opened over TLS 1.2",
                "timeout": "T_hello_init (10,000 ms)",
                "description": "Peers exchange 'cmi_hello' frames containing SHIP ID and protocol versions."
            },
            {
                "state": "sme_hello_state_ok",
                "phase": "Hello Handshake",
                "trigger": "Both peers accept CMI hello parameters",
                "timeout": "T_hello_prolong (60,000 ms)",
                "description": "Handshake accepted. Connection prolongation timer active to avoid premature timeout."
            },
            {
                "state": "sme_prot_h_state_client_init",
                "phase": "Protocol Handshake",
                "trigger": "Transition from Hello OK",
                "timeout": "T_prot_h (10,000 ms)",
                "description": "Verifies supported formats (SPINE JSON/XML) and protocol versions."
            },
            {
                "state": "sme_pin_state_check",
                "phase": "Security Verification",
                "trigger": "Peer requires out-of-band PIN pairing",
                "timeout": "T_pin_verify (120,000 ms)",
                "description": "User enters display PIN to authenticate mutual device ownership."
            },
            {
                "state": "sme_complete",
                "phase": "Active Data Exchange",
                "trigger": "Handshake successfully finalized",
                "timeout": "Heartbeat Keepalive (every 30s)",
                "description": "Full bidirectional SPINE datagram transport over SHIP WebSocket channel is active."
            }
        ]
    },

    "spine_subscription": {
        "title": "🧱 SPINE Subscription Lifecycle",
        "standard": "EEBus SPINE TS Protocol Specification v1.3.0 — Section 4 & 5",
        "description": (
            "Subscriptions enable event-driven architectures in SPINE. A client subscribes "
            "to a server's feature, prompting the server to automatically send 'notify' datagrams "
            "whenever measurement or state data changes."
        ),
        "mermaid": """graph TD
    classDef clientStyle fill:#1e3a8a,stroke:#38bdf8,stroke-width:2px,color:#f8fafc;
    classDef serverStyle fill:#581c87,stroke:#c084fc,stroke-width:2px,color:#f8fafc;
    classDef streamStyle fill:#064e3b,stroke:#34d399,stroke-width:2px,color:#f8fafc;

    subgraph Client [Client Feature]
        C1[1. Discover Features]:::clientStyle
        C2[2. Send Subscription Request]:::clientStyle
        C3[4. Process Notifications]:::streamStyle
        C4[5. Send Unsubscribe]:::clientStyle
    end

    subgraph Server [Server Feature NodeManagement]
        S1[Subscription Table Entry]:::serverStyle
        S2[3. Send Result/Ack Success]:::serverStyle
        S3[Data Changed: Emit Notify]:::streamStyle
        S4[Delete Subscription Entry]:::serverStyle
    end

    C1 -->|read deviceClassification| S1
    C2 -->|call subscriptionManagementRequestCall| S1
    S1 --> S2
    S2 -->|resultData / success| C3
    S3 -->|notify payload| C3
    C4 -->|call subscriptionManagementDeleteCall| S4
""",
        "states": [
            {
                "state": "Feature Discovery",
                "phase": "Discovery",
                "trigger": "Client requests NodeManagement feature list",
                "timeout": "5,000 ms",
                "description": "Discovers supported feature types (e.g., Measurement, LoadControl, ElectricalConnection)."
            },
            {
                "state": "Subscription Request",
                "phase": "Subscription Handshake",
                "trigger": "Client issues 'call' with subscriptionManagementRequestCall",
                "timeout": "10,000 ms",
                "description": "Provides client addressSource and server addressDestination for binding."
            },
            {
                "state": "Subscription Active",
                "phase": "Event Notification",
                "trigger": "Server sends 'result' with errorNumber=0 (success)",
                "timeout": "Ongoing until unbind",
                "description": "Server pushes asynchronous 'notify' datagrams whenever monitored values change."
            },
            {
                "state": "Unsubscribe",
                "phase": "Teardown",
                "trigger": "Client sends subscriptionManagementDeleteCall",
                "timeout": "5,000 ms",
                "description": "Removes subscriber from the server's notification dispatch table."
            }
        ]
    },

    "spine_binding": {
        "title": "🔗 SPINE Binding Lifecycle",
        "standard": "EEBus SPINE TS Protocol Specification v1.3.0 — Section 6",
        "description": (
            "Bindings establish a persistent functional association between two complementary "
            "features (e.g. an EVSE Client and an Energy Manager Server) allowing ongoing interaction."
        ),
        "mermaid": """graph TD
    classDef nodeStyle fill:#0f172a,stroke:#38bdf8,stroke-width:2px,color:#f8fafc;
    classDef boundStyle fill:#064e3b,stroke:#34d399,stroke-width:2px,color:#f8fafc;

    B0[Unbound State]:::nodeStyle -->|Read Feature Support| B1[Discovery Complete]:::nodeStyle
    B1 -->|bindingManagementRequestCall| B2[Binding Pending]:::nodeStyle
    B2 -->|resultData: Success| B3[Bound / Operational]:::boundStyle
    B3 -->|Direct Function Calls / Commands| B3
    B3 -->|bindingManagementDeleteCall| B0
""",
        "states": [
            {
                "state": "Unbound",
                "phase": "Initial",
                "trigger": "Initial connection establish",
                "timeout": "None",
                "description": "Device entities are connected via SHIP but not functionally coupled."
            },
            {
                "state": "Binding Request",
                "phase": "Negotiation",
                "trigger": "Client requests functional binding",
                "timeout": "10,000 ms",
                "description": "NodeManagement stores client feature and server feature in binding table."
            },
            {
                "state": "Bound",
                "phase": "Operational",
                "trigger": "Binding confirmation acknowledged",
                "timeout": "Persistent across sessions",
                "description": "Features interact directly via read, write, call, and notify commands."
            }
        ]
    }
}


def get_state_machine_data(machine_key: str = "ship_sme") -> Dict[str, Any]:
    """Retrieve state machine diagram and metadata by key."""
    return STATE_MACHINES.get(machine_key, STATE_MACHINES["ship_sme"])
