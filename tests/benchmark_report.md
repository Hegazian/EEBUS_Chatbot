# 📊 EEBUS RAG Benchmark Evaluation Report

**Evaluated At:** 2026-08-31 10:48:14
**Total Knowledge Base Chunks:** `12,657`
**Retrieval Pipeline:** Hybrid (Dense BGE-Small + Sparse BM25 via RRF)
**Reranker:** Cross-Encoder MS-MARCO

## Overall Metrics

| Metric | Target | Benchmark Result | Status |
| :--- | :--- | :--- | :--- |
| **Hit Rate @ 1** | ≥ 65.0% | **88.0%** | ✅ PASS |
| **Hit Rate @ 3** | ≥ 80.0% | **92.0%** | ✅ PASS |
| **Hit Rate @ 5** | ≥ 85.0% | **100.0%** | ✅ PASS |
| **Mean Reciprocal Rank (MRR)** | ≥ 0.700 | **0.916** | ✅ PASS |
| **Structure-Aware XSD Precision** | 100.0% | **100.0%** | ✅ PASS |
| **Average Latency** | < 3,500 ms | **2443.1 ms** | ✅ PASS |

## Detailed Query Breakdown

| ID | Category | Query | Hit Rank | Top Retrieved Document | Latency |
| :--- | :--- | :--- | :--- | :--- | :--- |
| SHIP-01 | SHIP | What are the states in the SHIP connection handshake state machine (SME)? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2266.9ms |
| SHIP-02 | SHIP | How does mDNS discovery work in SHIP for discovering EEBUS services? | **#1** | `EEBus_SHIP_TestSpecification_V1.0.0.pdf` | 2227.4ms |
| SHIP-03 | SHIP | What TLS versions and cipher suites are mandated for SHIP? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2455.3ms |
| SHIP-04 | SHIP | What is the CMI Hello prolong mechanism in SHIP SME? | **#1** | `EEBus_SHIP_TestSpecification_V1.0.0.pdf` | 2066.0ms |
| SHIP-05 | SHIP | What are the WebSocket subprotocols used by SHIP for SPINE transport? | **#1** | `EEBus_SHIP_TS_Specification_v1.0.1.pdf` | 2547.8ms |
| SHIP-06 | SHIP | What PIN verification modes are defined in the SHIP connection handshake? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2638.8ms |
| SHIP-07 | SHIP | How are SHIP connection errors handled and signaled between peers? | **#2** | `EEBus_SPINE_IG_ProtocolAndResourceGuidelines_V1.0.0.pdf` | 2438.0ms |
| SHIP-08 | SHIP | What is the structure of a SHIP Connection Management Interface frame? | **#1** | `EEBus_SHIP_TS_Specification_v1.1.0.pdf` | 2443.2ms |
| SPINE-01 | SPINE | Explain the SPINE resource model: Device, Entity, and Feature. | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2555.9ms |
| SPINE-02 | SPINE | What are the SPINE command classifiers and their roles? | **#1** | `EEBus_SPINE_TR_Introduction.pdf` | 2569.5ms |
| SPINE-03 | SPINE | What is the root structure of an EEBUS SPINE Datagram? | **#1** | `EEBus_SPINE_TR_Introduction.pdf` | 2637.2ms |
| SPINE-04 | SPINE | How does subscription management work in SPINE NodeManagement? | **#5** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2439.4ms |
| SPINE-05 | SPINE | How is binding established between complementary SPINE features? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 2477.2ms |
| SPINE-06 | SPINE | What is the format of SPINE feature addressing in datagram headers? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 2405.5ms |
| SPINE-07 | SPINE | How does partial data read and write filtering operate in SPINE? | **#1** | `EEBus_SPINE_TS_ProtocolSpecification.pdf` | 2402.2ms |
| SPINE-08 | SPINE | What is the Heartbeat function in SPINE and how is keepalive signaled? | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2500.0ms |
| XSD-01 | XSD | What is the schema definition and fields of LoadControlLimitDataType? | **#1** | `EEBus_SPINE_TS_LoadControl.xsd` | 2566.9ms |
| XSD-02 | XSD | What fields are contained in DeviceClassificationUserDataDataType? | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2588.9ms |
| XSD-03 | XSD | What are the allowed enum values for LoadControlEventActionEnumType? | **#5** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2888.8ms |
| XSD-04 | XSD | What is the definition of MeasurementDescriptionDataType in SPINE? | **#1** | `EEBus_SPINE_TS_Measurement.xsd` | 2576.2ms |
| XSD-05 | XSD | What is the schema for ElectricalConnectionPermittedValueSetDataType? | **#1** | `EEBus_SPINE_TS_ElectricalConnection.xsd` | 2420.9ms |
| UC-01 | UseCase | How does Limitation of Power Consumption (LPC) operate in EEBUS? | **#1** | `EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf` | 2374.2ms |
| UC-02 | UseCase | How does Limitation of Power Production (LPP) control photovoltaic systems? | **#1** | `EEBus_UC_TS_LimitationOfPowerProduction_V1.0.0_public.pdf` | 1843.5ms |
| UC-03 | UseCase | What are the required SPINE function sets for EVSE charging control? | **#1** | `EEBus_SPINE_TS_ResourceSpecification.pdf` | 2394.4ms |
| UC-04 | UseCase | How does an Energy Management System (EMS) configure power limits for devices? | **#1** | `EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf` | 2353.7ms |