# SHIP (Smart Home IP) Protocol Implementation Guide

**Based on:** EEBus Technical Specification - Smart Home IP v1.1.0  
**Date:** 2025-09-22  
**Source:** EEBus_SHIP_TS_Specification_v1.1.0.pdf

---

## Table of Contents

1. [Protocol Overview](#1-protocol-overview)
2. [Stack Architecture](#2-stack-architecture)
3. [Node Parameters & Defaults](#3-node-parameters--defaults)
4. [Discovery (mDNS/DNS-SD)](#4-discovery-mdnsdns-sd)
5. [TCP Layer](#5-tcp-layer)
6. [TLS Layer](#6-tls-layer)
7. [WebSocket Layer](#7-websocket-layer)
8. [Message Representation (JSON)](#8-message-representation-json)
9. [Key Management](#9-key-management)
10. [Verification Procedures & Trust Levels](#10-verification-procedures--trust-levels)
11. [SHIP Message Exchange (SME)](#11-ship-message-exchange-sme)
12. [SME Connection States](#12-sme-connection-states)
13. [Connection Termination](#13-connection-termination)
14. [Well-known protocolId](#14-well-known-protocolid)
15. [Registration & Reconnection](#15-registration--reconnection)
16. [SHIP Commissioning Tool](#16-ship-commissioning-tool)

---

## 1. Protocol Overview

SHIP (Smart Home IP) is a secure TCP/IP-based protocol for interoperable machine-to-machine communication in smart home environments.

**Key Features of SHIP 1.1:**
- Report of certificate changes between SHIP nodes
- Management of "foreign" certificates via SHIP commissioning tool
- Support of additional cryptographic curves (brainpoolP256r1, brainpoolP384r1)
- Discovery/ranking of additional TLS ECC curves/public keys (TLS probing)

**Key Design Principles:**
- Scalability from constrained devices to cloud solutions
- Downward compatible extensibility
- Mutual TLS authentication
- JSON-based message representation

---

## 2. Stack Architecture

```
+--------------------------------------------------+
|              SHIP Message Exchange (SME)           |
|  (JSON-UTF8 encoding, XSD-derived structures)      |
+--------------------------------------------------+
|                   WebSocket (RFC 6455)             |
|  - Binary frames (0x2) only                        |
|  - Subprotocol: "ship"                             |
|  - wss:// URI scheme                               |
+--------------------------------------------------+
|              TLS 1.2 (RFC 5246)                    |
|  - Mutual authentication required                  |
|  - ECDHE_ECDSA cipher suites                       |
|  - secp256r1 mandatory, brainpoolP* optional       |
+--------------------------------------------------+
|              TCP (RFC 793)                         |
+--------------------------------------------------+
|              IPv4/IPv6                             |
+--------------------------------------------------+
|              mDNS/DNS-SD (Discovery)               |
+--------------------------------------------------+
```

---

## 3. Node Parameters & Defaults

| Parameter | Section | Default/Recommendation |
|-----------|---------|----------------------|
| Initial TCP retransmission count | 8.3 | 2 |
| Initial TCP retransmission timeout | 8.4 | 1s |
| Maximum TCP retransmission timeout | 8.4 | 120s |
| MTU | 8 | 1500 bytes |
| Max fragment length (TLS) | 9.2 | 512 bytes |
| Connection Keepalive ping min interval | 10.4 | 50s |
| Connection Keepalive pong timeout | 10.4 | 10s |
| SKI length | 12.2 | 20 bytes (40 hex digits) |
| PIN length | 12.5 | 8-16 hex digits |
| Max "auto accept" time window | 12.3.1.1 | ≤120s (recommended: 60s) |
| User trust level for general SHIP comms | 12.3.2 | ≥8 |
| User trust / second factor for SHIP commissioning | 12.3.2 | ≥32 |
| CmiTimeout | 13.4 | 10-30s (recommended: 30s) |
| Wait-For-Ready-Timer initial | 13.4.4.1 | 60-240s (recommended: 120s) |
| Wait-For-Ready-Timer prolongation | 13.4.4.1 | 60-240s (recommended: 120s) |
| PIN entry penalty after 3rd invalid | 13.4.4.3 | 10-15s (recommended: 15s) |
| PIN entry penalty after 6th invalid | 13.4.4.3 | 60-90s (recommended: 90s) |
| Certificate update transition stage | 12.1.3.2 | ≥1 month (25% of cert lifetime) |
| Cert update connection retry period | 12.1.3.2 | ≥5 minutes |
| keyMaterialState timeout | 12.1.3.2 | ≥30s (recommended: 30s) |
| keyMaterialStateResponse timely sending | 12.1.3.2 | ≤20s |

---

## 4. Discovery (mDNS/DNS-SD)

### Service Definition
- **Service name:** `ship`
- **Service type:** `_ship._tcp`
- **Protocol:** mDNS/DNS-SD (RFC 6762, RFC 6763)
- **TTL recommendation:** 2 minutes
- **TXT record max size:** 400 bytes

### Mandatory TXT Record Keys

| Key | Value | Example | Runtime |
|-----|-------|---------|---------|
| `txtvers` | Version number (must be 1) | `txtvers=1` | Static |
| `id` | Globally unique SHIP ID (≤63 bytes UTF-8) | `id=EXAMPLEBRAND-EEB01M3EU-001122334455` | Static |
| `path` | wss path (≤32 bytes UTF-8) | `path=/ship/` | Static |
| `ski` | 40 hex digit secp256r1 SKI | `ski=1234AAAAFFFF1111CCCC3333EEEEDDDD99992222` | Dynamic |
| `register` | Boolean | `register=false` | Dynamic |
| `ecc` | Boolean (SHIP ≥1.1) | `ecc=true` | Dynamic |

### Optional TXT Record Keys

| Key | Value | Example |
|-----|-------|---------|
| `brand` | Manufacturer brand (≤32 bytes) | `brand=ExampleBrand` |
| `type` | Device type (≤32 bytes) | `type=Dishwasher` |
| `model` | Model (≤32 bytes) | `model=EEB01M3EU` |

### Service Instance Name Format
```
<Instance>._ship._tcp.local.
```
Example: `Dishwasher ExampleCompany EEB01M3EU._ship._tcp.local.`

### mDNS Host Name
- ≤63 bytes
- Should use unique ID from TXT record
- Example: `EXAMPLEBRAND-EEB01M3EU-001122334455.local.`

---

## 5. TCP Layer

### Requirements
- TCP SHALL be used for communication
- MTU SHALL NOT exceed 1500 bytes
- Port set via DNS-SD SRV record

### Limited Connection Capabilities
- Minimum: 1 simultaneous active connection
- Constrained nodes (1 connection): Close server port when acting as client; close client ASAP and reopen server
- Nodes with x connections: Reserve 1 for server, use max x-1 for client; reserve 1 for client, use max x-1 for server

### Connection Establishment
- SYN retransmitted twice if no response
- RST packet SHOULD NOT be blocked
- Max connection establishment: ~10 seconds (1 + 3 + 6)

### Retransmission Timeout
- Follow RFC 6298
- Initial RTO: 1 second
- After first retransmission: minimum RTO 3 seconds (historical)
- Exponential backoff (double each retransmission)
- Max RTO: 120 seconds

---

## 6. TLS Layer

### Requirements
- **TLS 1.2 is MANDATORY** (RFC 5246)
- Mutual authentication SHALL be used
- TLS 1.3 not considered in this version

### Cipher Suites
| Cipher Suite | Status |
|-------------|--------|
| `TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256` (RFC 5289) | **MUST** |
| `TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8` | OPTIONAL |
| `TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256` | OPTIONAL |

### Supported ECC Curves
| Curve | Status |
|-------|--------|
| secp256r1 | **SHALL** |
| brainpoolP256r1 | MAY |
| brainpoolP384r1 | MAY |

### Curve Ranking (for TLS ECC extension)
1. brainpoolP384r1 (highest priority - if supported)
2. brainpoolP256r1
3. secp256r1 (lowest priority - mandatory)

### Maximum Fragment Length
- RFC 6066 extension SHOULD be supported
- If used: only support 1024 bytes
- Outgoing fragments SHALL NOT exceed 1024 bytes even without extension

### TLS Compression
- **MUST NOT** be used

### Server Name Indication
- SNI extension MUST be supported
- Local SHIP nodes SHALL ignore SNI
- Server name = mDNS hostname (local) or DNS hostname (web server)

### Renegotiation
- **SHALL NOT** be supported

### Session Resumption
- SHOULD be supported for fast reconnections
- Session state (master secret + session ID) SHOULD be stored

### TLS Probing
- Required for discovering non-secp256r1 SKIs
- Establish connection to get TLS Server Certificate, derive SKI
- Stop probing connection after receiving Server Certificate if SKI not trusted
- TLS probing and auto accept MUST be treated independently

---

## 7. WebSocket Layer

### Compliance
- Strict compliance with RFC 6455 (no draft versions)
- Based on TCP + TLS

### Opening Handshake
- URI scheme: **wss://** (TLS required)
- `Sec-WebSocket-Version`: 13
- `Sec-WebSocket-Protocol`: `ship` (MUST be included, no other subprotocols)
- `Sec-WebSocket-Extensions`: MUST NOT be sent
- `Origin`: MAY be absent
- Host, port, resource name from SHIP discovery

### Data Framing
- All non-control frames: **type 0x2 (binary)**
- Type 0x1 (text): terminate with status 1003
- Types 0x3-0x7, 0xB-0xF: terminate with status 1002
- Reserved bits MUST be 0
- Fragmentation supported per RFC 6455, no interleaving

### Connection Keepalive
- Ping interval: **minimum 50 seconds**
- Pong timeout: **10 seconds**
- Keep connections alive whenever resources permit

---

## 8. Message Representation (JSON)

### Base Format
- JSON-UTF8 representation as basis
- SHIP prepared for other formats (JSON-UTF16, ASN.1)
- Structures defined using XSD, transformed to JSON

### XSD-to-JSON Mapping

| XSD Type | JSON Type |
|----------|-----------|
| `xs:boolean` | Boolean |
| `xs:double`, `xs:byte`, `xs:unsignedByte`, `xs:short`, `xs:unsignedShort`, `xs:integer`, `xs:unsignedInt`, `xs:nonNegativeInteger`, `xs:unsignedLong` | Number |
| `xs:dateTime`, `xs:duration`, `xs:time` | String |
| `xs:language`, `xs:string` | String |
| `xs:hexBinary` | String |

### Key Transformation Rules
1. Element names become JSON object keys
2. Numbers recognized as JSON numbers
3. Booleans recognized as JSON booleans
4. Empty elements → empty JSON array `[]`
5. `nil` elements → JSON `null`
6. `maxOccurs > 1` → JSON array
7. SHIP namespace prefixes omitted
8. `xs:sequence` / `xs:choice` within `xs:complexType` → Array
9. `xs:all` within `xs:complexType` → Object

---

## 9. Key Management

### Key Material Types
1. **Public keys** + SKI (Subject Key Identifier) for authentication
2. **Private keys** - MUST be kept secret (secure element recommended)
3. **Symmetric keys** - for efficient reconnection
4. **PIN** - optional second factor

### Certificates
- Every SHIP node MUST have a certificate
- Self-signed or PKI-based accepted
- Public/private key pair: one per certificate
- One certificate: one SHIP node
- No mandatory PKI specified
- Certificate validation: **baseline = verify public key matches trusted SKI**
- Optional checks (PKI, lifetime, etc.) SHALL NOT break baseline interoperability

### SKI (Subject Key Identifier)
- Generated per RFC 3280 §4.2.1.2 method (1): SHA-1 of public key (encoded with DER, prefixed with 00 04 40 for uncompressed key)
- 20 bytes → 40 hex digits
- **User presentation:**
  - secp256r1: `SKI XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX` (prefix "SKI ")
  - brainpoolP256r1: `BSKI XXXX XXXX ...` (prefix "BSKI ")
  - brainpoolP384r1: `B2SKI XXXX XXXX ...` (prefix "B2SKI ")
  - Spaces every 4 hex digits

### SKI Accessibility
At least one of: Label, User interface (display), Local communication interface (NFC), Cloud-based UI

### Public Key Storage
- Trusted foreign SKIs stored with trust level
- `updateCounter` stored alongside
- Persistent storage STRONGLY RECOMMENDED
- User MUST be able to remove trusted keys (at least factory reset)

### Double Connection Prevention
- After TLS handshake, if duplicate connections found:
  - Node with **larger** 160-bit SKI closes older connections (keeps most recent)
  - 3-second timeout for resolution
  - Smaller SKI node may use WebSocket ping to probe

### Certificate Updates
- **4 certificate states:** initial, predecessor, current, successor
- Transition stage: **minimum 1 month**
- `updateCounter` starts at 1 (factory new), incremented on changes
- Key material state transmitted via SME `keyMaterialState` message
- If no `keyMaterialStateResponse` within 30s: resend; if another 30s: close and retry
- Connection retry for updates: max every 5 minutes
- Downgrade (decreased `updateCounter`) SHALL be ignored

---

## 10. Verification Procedures & Trust Levels

### Trust Level Categories
1. **User trust** (primary)
2. **PKI trust** (optional)
3. **Second factor trust** (PIN-based)

### Trust Level Table

| Mechanism | User Trust | Second Factor Trust |
|-----------|-----------|-------------------|
| Untrusted | 0 | - |
| Auto accept | 8 | - |
| Auto accept + PIN | 8 | 16 or 32 |
| User verified | 32 | - |
| Commissioned (manufacturer) | 32-96 | - |
| User input | 64 | - |
| SHIP commissioning (auto accept + PIN) | 8 | 32 |
| SHIP commissioning (user verified) | 32 | - |
| Optional PKI | 0-65535 (PKI trust) | - |

### Public Key Verification Modes

#### 1. Auto Accept (Trust Level: 8)
- Only for devices without user interface
- Triggered by push button
- Time window: ≤120 seconds
- Only ONE foreign key accepted per window
- After acceptance: mode instantly deactivated

#### 2. Auto Accept + PIN (Second Factor: 16-32)
- Counter man-in-the-middle attacks
- PIN state can be set to "required" only if SHIP commissioning supported

#### 3. User Verification (Trust Level: 32)
- Display or communication interface required
- Must inform user of unknown SKIs
- Only highest-ranked curve SKI shown to user

#### 4. Manufacturer Specific Commissioning (Trust Level: 32-96)
- Manufacturer-specific commissioning tool
- Trust level depends on tool trustworthiness

#### 5. User Input (Trust Level: 64)
- Manual SKI entry
- Useful for SHIP commissioning tools

#### 6. SHIP Commissioning
- Interoperable commissioning via SHIP commissioning tool
- Requires pre-existing trust (user verify OR auto accept + PIN)
- Trust limitation rules apply when distributing foreign SKIs

### PIN Verification (State Machine)
Refer to §13.4.4.3 for complete state machine:
- `SME_PIN_STATE_INIT` → evaluate vs own PIN requirement
- `SME_PIN_STATE_ASK` tree: PROCESS / RESTRICTED_OK / OK
- PIN error penalty timers after 3rd and 6th failed attempts
- `connectionPinState.pinState` values: `none`, `required`, `optional`, `pinOk`
- `connectionPinState.inputPermission`: `ok`, `busy`

---

## 11. SHIP Message Exchange (SME)

### Message Types

| MessageType | Value | Description |
|-------------|-------|-------------|
| `control` | `%x01` | SME control messages |
| `data` | `%x02` | Application data messages |
| `end` | `%x03` | Connection close messages |
| `reserved` | `%x00` | Reserved |

### Message Format
Each SHIP WebSocket message consists of:
- 1 octet: MessageType
- Remaining octets: MessageValue (structure defined per message type, encoded in agreed format)

### SME Connection States (in order)

| # | State | Description |
|---|-------|-------------|
| 1 | Connection Mode Initialization (CMI) | Initial role determination |
| 2 | Hello | Trust confirmation & capability exchange |
| 3 | Protocol Handshake | Message format negotiation |
| 4 | PIN Verification | Optional PIN-based auth |
| 5 | Connection Data Exchange | Application data transfer |
| 6 | Access Methods Identification | Optional access method exchange |
| 7 | Key Material Exchange | Certificate/key update |
| 8 | Connection Termination | Graceful close |

### 11.1 CMI (Connection Mode Initialization)

**SME "connection mode request" message:**
```
MessageType = %x01 (control)
```
Sent by the client to the server. No message value.

**SME "connection mode response" message:**
```
MessageType = %x01 (control)
```
Response from server. No message value.

**Rules for client:**
- After WebSocket established, send `connection mode request`
- Wait for `connection mode response` within CmiTimeout (10-30s)
- If timeout: close connection, or retry as server

**Rules for server:**
- Wait for `connection mode request` within CmiTimeout
- If received: send `connection mode response`, proceed to Hello
- If timeout: close connection, may retry as client

### 11.2 Hello

**Purpose:** Confirm trustworthiness, exchange capabilities.

**SME "hello" message structure (SmeHelloValue):**

| Element | M/O | Description |
|---------|-----|-------------|
| `hello` | M | Root element |
| `hello.shipVersion` | M | SHIP version string (e.g., "1.0", "1.1") |
| `hello.register` | M | Boolean: whether node is in registration phase |
| `hello.keyMaterialState.updateCounter` | O | Current key material state counter (SHIP ≥1.1) |

**Rules for DEV-A (initiator of Hello):**
1. Send SME "hello" with own version and register flag
2. Wait for SME "hello" from DEV-B within Wait-For-Ready-Timer (initial: 60-240s)
3. If register flag true in received hello → this is a registration, not reconnection
4. If partner is trusted → store credentials (SKI, trust level)
5. May send prolongation request if more time needed

**Rules for DEV-B:**
1. Wait for SME "hello" from DEV-A within Wait-For-Ready-Timer
2. If received: respond with own SME "hello"
3. Ready flag now considered set

**Prolongation:**
- If a node needs more preparation time, sends SME "prolong" message
- Wait-For-Ready-Timer restarts with prolongation value (60-240s)
- Max 3 prolongation requests per connection

### 11.3 Protocol Handshake

**Purpose:** Negotiate message format for all subsequent messages.

**SME "Protocol Handshake" message structure:**

| Element | M/O | Description |
|---------|-----|-------------|
| `messageProtocolHandshake` | M | Root element |
| `messageProtocolHandshake.protocol` | M | Array of supported protocols |
| `messageProtocolHandshake.protocol[].id` | M | Protocol identifier (e.g., "json-utf8") |
| `messageProtocolHandshake.protocol[].version` | M | Protocol version string |
| `messageProtocolHandshake.protocol[].majorVersion` | O | Major version number |
| `messageProtocolHandshake.protocol[].minorVersion` | O | Minor version number |

**Supported protocol IDs:**
- `json-utf8` (MUST be supported)
- `json-utf16` (OPTIONAL)

**SME "Protocol Handshake Error" message:**

| Element | M/O | Description |
|---------|-----|-------------|
| `messageProtocolHandshakeError` | M | Root element |
| `messageProtocolHandshakeError.error` | M | Error code (0=unspecific, 1=negotiation failed, other RFU) |

**Process:**
1. First message sender sends SME "Protocol Handshake" with supported protocols
2. Second node responds with SME "Protocol Handshake" listing intersection of supported protocols, best match first
3. If intersection empty → send SME "Protocol Handshake Error" → close connection
4. First message sender evaluates response, selects common format
5. Both sides now use agreed format

### 11.4 PIN Verification

See §13.4.4.3 for full state machine. Messages:

- **SME "PIN state"** (`connectionPinState`): `pinState` (none/required/optional/pinOk), `inputPermission` (ok/busy)
- **SME "PIN input"** (`connectionPinInput`): `pin` (hex string 8-16 digits)
- **SME "PIN error"** (`connectionPinError`): `error` (1=wrong PIN)

**PIN penalty rules:**
- After 3rd invalid attempt: wait 10-15s before next attempt
- After 6th invalid attempt: wait 60-90s before next attempt

### 11.5 Connection Data Exchange

**Messages:**

| Element | M/O | Description |
|---------|-----|-------------|
| `data.header` | M | Header for payload |
| `data.header.protocolId` | M | Identifies payload specification (e.g., "ee1.0") |
| `data.payload` | M | Higher-level protocol data |
| `data.extension` | O | Manufacturer-specific extensions |
| `data.extension.extensionId` | O | Extension identifier |
| `data.extension.binary` | O | Binary extension data |
| `data.extension.string` | O | Textual extension data |

**Message format:**
```
MessageType = %x02 ; data
MessageValue = DataValue
DataValue = *OCTET
```

**Compatibility Rules:**
- Base specification defines forward compatibility
- Each version has 0 or 1 immediate successors
- Each version has 0 or 1 immediate predecessors
- Unknown `protocolId` → silently skip message

---

## 12. SME Connection States (Detailed)

### 12.1 CMI Process

```
Client                    Server
  |                         |
  |--- WS established --->  |
  |                         |
  |--- connection mode req->|
  |<- connection mode resp--|
  |                         |
  |--- hello ------------>  |
  |<--- hello ------------- | 
  |                         |
```

### 12.2 Hello with Prolongation

```
Node A                    Node B
  |                         |
  |--- hello ------------>  |
  |<--- prolong ----------- |  (B needs more time)
  |                         |  (Wait-For-Ready restarts)
  |<--- hello ------------- |
  |                         |
```

### 12.3 Protocol Handshake

```
Initiator                 Responder
  |                         |
  |--- ProtocolHS --------> |  (supports json-utf8, json-utf16)
  |<-- ProtocolHS --------- |  (selects json-utf8)
  |                         |
  | (agreed: json-utf8)     |
  |--- data message ----->  |
  |                         |
```

### 12.4 PIN Verification Flow

1. Both sides exchange SME "PIN state" messages
2. Evaluate own PIN requirement and partner's PIN state
3. If PIN required: user enters PIN → SME "PIN input" sent
4. Partner validates → sends updated SME "PIN state"
5. On success: proceed to Connection Data Exchange
6. On failure: SME "PIN error" sent, retry or close

---

## 13. Connection Termination

### SME "close" Message

```
MessageType = %x03 (end)
```

| Element | M/O | Description |
|---------|-----|-------------|
| `connectionClose.phase` | M | "announce" or "confirm" |
| `connectionClose.maxTime` | O | Time in ms before forced close |
| `connectionClose.reason` | O | Termination reason |

### Reason Values
- **unspecific** - Temporary disconnection (likely reconnectable)
- **removedConnection** - Node removed from known devices

### Termination Process
**DEV-A (initiator):**
1. Send SME "close" with `phase=announce`, `maxTime`, `reason`
2. Close connection latest after `maxTime` elapsed
3. If confirmation received before `maxTime` → close immediately

**DEV-B (responder):**
1. Prepare to stop data exchange before `maxTime` expires
2. Send SME "close" with `phase=confirm`
3. Close connection

**Simultaneous close:**
- Both sides may initiate close at same time
- First confirmation received closes the connection
- `removedConnection` reason takes priority over `unspecific`

**Note:** Format for close message is always JSON-UTF8 (regardless of negotiated format).

---

## 14. Well-known protocolId

| protocolId | Definition |
|-----------|-----------|
| `ee1.0` | EEBus SPINE specifications compatible with SPINE data model specification base version 1.0 |

---

## 15. Registration & Reconnection

### Registration Flow
1. Verify public key (one of the verification modes)
2. If auto accept: set register flag to true
3. Discover nodes with matching SKI
4. Establish TCP/TLS/WebSocket connection
5. Verify public key matches trusted SKI
6. SME CMI → Hello → Protocol Handshake → (PIN) → Data Exchange

### Successful Registration
When both sides have confirmed trust via SME "hello" → registration complete.
All subsequent connections = reconnections until one side aborts hello.

### Reconnection Flow
1. Connect to IP:port (from discovery or stored)
2. Check public key still matches trusted SKI
3. SME exchange (no user interaction needed)
4. If key material changed → use `keyMaterialState` mechanism

### Pre-trust vs Post-trust
- **Pre-trust:** Trust before any SME exchange (TLS handshake requires prior trust)
- **Post-trust:** Trust within SME Hello state (temporarily accept TLS, verify user)

---

## 16. SHIP Commissioning Tool

### Purpose
Distribute trustworthy SKIs between SHIP nodes via a single user interface (smartphone, web server, dedicated device).

### Messages
- SME `commissioning request` / `commissioning response`
- SME `key material request`
- SME `key material` (with entries containing curve, SKI, publicKey, userTrust, id, note)
- SME `key material response`
- SME `key material delete` / `key material delete response`
- SME `key material state` (SHIP ≥1.1)
- SME `key material state response` (SHIP ≥1.1)
- SME `key material state request` (SHIP ≥1.1)

### Trust Requirements
For a SHIP node to accept a commissioning request:
- User trust ≥ 32, OR
- Second factor trust ≥ 32 AND user trust ≥ 8

### Trust Limitation
When distributing SKIs via commissioning tool, the new trust level is capped at:
```
max(userTrust_of_tool, secondFactorTrust_of_tool, existing_userTrust_of_SKI)
```

### QR Code (§12.7)
QR Code can encode SKI + PIN for easy commissioning:
- QR Code Model 2, "low" ECC level
- Module size: 0.33mm minimum
- Contains: SKI (various curve types), PIN, optional SHIP ID
- Enables easy mutual authentication via smartphone camera

---

## Implementation Checklist

### Minimal SHIP Node (Constrained Device)
- [ ] mDNS/DNS-SD discovery (TXT record with txtvers, id, path, ski, register, ecc)
- [ ] TCP server port (at least 1 connection)
- [ ] TLS 1.2 with mutual auth (TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256)
- [ ] secp256r1 ECC curve support
- [ ] WebSocket (RFC 6455) with binary frames and "ship" subprotocol
- [ ] SME CMI, Hello, Protocol Handshake (json-utf8), Data Exchange
- [ ] At least one PK verification mode (auto accept + PIN recommended)
- [ ] Connection termination (SME close)

### Full SHIP 1.1 Node
- [ ] All minimal requirements
- [ ] Optional ECC curves: brainpoolP256r1, brainpoolP384r1
- [ ] TLS probing support
- [ ] Certificate update mechanism (keyMaterialState exchange)
- [ ] SHIP commissioning support
- [ ] Access Methods Identification
- [ ] Key material deletion and state management
- [ ] Session resumption
- [ ] Maximum fragment length negotiation

---

## References

- IETF RFC 793: TCP
- IETF RFC 5246: TLS 1.2
- IETF RFC 5289: TLS ECC Cipher Suites
- IETF RFC 6066: TLS Extensions
- IETF RFC 6455: WebSocket
- IETF RFC 6762: Multicast DNS
- IETF RFC 6763: DNS-Based Service Discovery
- IETF RFC 8422: ECC TLS Extensions
- IETF RFC 3280/5280: X.509 PKI Certificates
- IETF RFC 2119: Key words for requirement levels
