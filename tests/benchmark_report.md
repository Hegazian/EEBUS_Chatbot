# 📊 EEBUS RAG Benchmark Evaluation Report

**Evaluated At:** 2026-08-27 21:28:51
**Total Knowledge Base Chunks:** `5,957`
**Retrieval Pipeline:** Hybrid (Dense BGE-Small + Sparse BM25 via RRF)
**Reranker:** Cross-Encoder MS-MARCO

## Overall Metrics

| Metric | Target | Benchmark Result | Status |
| :--- | :--- | :--- | :--- |
| **Hit Rate @ 1** | ≥ 80.0% | **68.0%** | ⚠️ WARN |
| **Hit Rate @ 3** | ≥ 90.0% | **84.0%** | ⚠️ WARN |
| **Hit Rate @ 5** | ≥ 95.0% | **88.0%** | ⚠️ WARN |
| **Mean Reciprocal Rank (MRR)** | ≥ 0.850 | **0.763** | ⚠️ WARN |
| **Structure-Aware XSD Precision** | 100.0% | **100.0%** | ✅ PASS |
| **Average Latency** | < 250 ms | **2816.2 ms** | ⚠️ WARN |

## Detailed Query Breakdown

| ID | Category | Query | Hit Rank | Top Retrieved Document | Latency |
| :--- | :--- | :--- | :--- | :--- | :--- |
| SHIP-01 | SHIP | What are the states in the SHIP connection handshake state machine (SME)? | **#1** | `SHIP_Protocol_Implementation_Guide.md` | 3684.3ms |
| SHIP-02 | SHIP | How does mDNS discovery work in SHIP for discovering EEBUS services? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2807.9ms |
| SHIP-03 | SHIP | What TLS versions and cipher suites are mandated for SHIP? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2661.7ms |
| SHIP-04 | SHIP | What is the CMI Hello prolong mechanism in SHIP SME? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2875.7ms |
| SHIP-05 | SHIP | What are the WebSocket subprotocols used by SHIP for SPINE transport? | **#1** | `SHIP_Protocol_Implementation_Guide.md` | 2810.8ms |
| SHIP-06 | SHIP | What PIN verification modes are defined in the SHIP connection handshake? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2591.8ms |
| SHIP-07 | SHIP | How are SHIP connection errors handled and signaled between peers? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2815.3ms |
| SHIP-08 | SHIP | What is the structure of a SHIP Connection Management Interface frame? | **#2** | `SHIP_Protocol_Implementation_Guide.md` | 2805.3ms |
| SPINE-01 | SPINE | Explain the SPINE resource model: Device, Entity, and Feature. | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2597.2ms |
| SPINE-02 | SPINE | What are the SPINE command classifiers and their roles? | **#2** | `EEBus_SPINE_TR_Introduction.pdf` | 3003.5ms |
| SPINE-03 | SPINE | What is the root structure of an EEBUS SPINE Datagram? | **#2** | `EEBus_SPINE_TR_Introduction.pdf` | 2662.5ms |
| SPINE-04 | SPINE | How does subscription management work in SPINE NodeManagement? | **#3** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2570.3ms |
| SPINE-05 | SPINE | How is binding established between complementary SPINE features? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 2743.6ms |
| SPINE-06 | SPINE | What is the format of SPINE feature addressing in datagram headers? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 3208.1ms |
| SPINE-07 | SPINE | How does partial data read and write filtering operate in SPINE? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 3167.0ms |
| SPINE-08 | SPINE | What is the Heartbeat function in SPINE and how is keepalive signaled? | ❌ Miss | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 3045.4ms |
| XSD-01 | XSD | What is the schema definition and fields of LoadControlLimitDataType? | **#1** | `EEBus_SPINE_TS_LoadControl.xsd` | 2911.6ms |
| XSD-02 | XSD | What fields are contained in DeviceClassificationUserDataDataType? | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2696.2ms |
| XSD-03 | XSD | What are the allowed enum values for LoadControlEventActionEnumType? | **#4** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2633.0ms |
| XSD-04 | XSD | What is the definition of MeasurementDescriptionDataType in SPINE? | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2720.2ms |
| XSD-05 | XSD | What is the schema for ElectricalConnectionPermittedValueSetDataType? | **#1** | `EEBus_SPINE_TS_ElectricalConnection.xsd` | 2631.6ms |
| UC-01 | UseCase | How does Limitation of Power Consumption (LPC) operate in EEBUS? | **#1** | `EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf` | 2618.0ms |
| UC-02 | UseCase | How does Limitation of Power Production (LPP) control photovoltaic systems? | **#1** | `EEBus_UC_TS_LimitationOfPowerProduction_V1.0.0_public.pdf` | 2855.6ms |
| UC-03 | UseCase | What are the required SPINE function sets for EVSE charging control? | ❌ Miss | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2654.2ms |
| UC-04 | UseCase | How does an Energy Management System (EMS) configure power limits for devices? | ❌ Miss | `EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf` | 2634.2ms |