"""
EEBUS RAG Automated Evaluation Benchmark Suite
Evaluates Context Recall@K, Mean Reciprocal Rank (MRR), Structure-Aware XSD Precision,
Reranker Efficiency, and End-to-End Latency across 25 curated ground-truth test cases.
"""

import os
import sys
import time
import json
from typing import List, Dict, Any

# Ensure project root is in sys.path
BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from core.engine import create_chat_engine
from core.config import BASE_DIR

# ─── 25 Golden Ground-Truth Evaluation Queries ─────────────────────────────────

GOLDEN_EVALUATION_DATASET: List[Dict[str, Any]] = [
    # ── SHIP Protocol Questions (1-8)
    {
        "id": "SHIP-01",
        "category": "SHIP",
        "query": "What are the states in the SHIP connection handshake state machine (SME)?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf", "SHIP_Protocol_Implementation_Guide.md"],
        "target_keywords": ["sme_hello", "sme_cmi", "sme_complete", "handshake"]
    },
    {
        "id": "SHIP-02",
        "category": "SHIP",
        "query": "How does mDNS discovery work in SHIP for discovering EEBUS services?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf", "SHIP_Protocol_Implementation_Guide.md"],
        "target_keywords": ["_ship._tcp", "mDNS", "TXT", "DNS-SD"]
    },
    {
        "id": "SHIP-03",
        "category": "SHIP",
        "query": "What TLS versions and cipher suites are mandated for SHIP?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf", "SHIP_Protocol_Implementation_Guide.md"],
        "target_keywords": ["TLS 1.2", "cipher", "certificate", "ECDHE"]
    },
    {
        "id": "SHIP-04",
        "category": "SHIP",
        "query": "What is the CMI Hello prolong mechanism in SHIP SME?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf"],
        "target_keywords": ["prolong", "T_hello", "cmi", "sme_hello"]
    },
    {
        "id": "SHIP-05",
        "category": "SHIP",
        "query": "What are the WebSocket subprotocols used by SHIP for SPINE transport?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf", "SHIP_Protocol_Implementation_Guide.md"],
        "target_keywords": ["ship", "websocket", "binary", "subprotocol"]
    },
    {
        "id": "SHIP-06",
        "category": "SHIP",
        "query": "What PIN verification modes are defined in the SHIP connection handshake?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf"],
        "target_keywords": ["pin", "sme_pin", "verification", "out-of-band"]
    },
    {
        "id": "SHIP-07",
        "category": "SHIP",
        "query": "How are SHIP connection errors handled and signaled between peers?",
        "expected_docs": ["EEBus_SHIP_TS_Specification_v1.1.0.pdf"],
        "target_keywords": ["connectionClose", "error", "sme_error"]
    },
    {
        "id": "SHIP-08",
        "category": "SHIP",
        "query": "What is the structure of a SHIP Connection Management Interface frame?",
        "expected_docs": ["EEBus_SHIP_TS_TransferProtocol.xsd", "EEBus_SHIP_TS_Specification_v1.1.0.pdf"],
        "target_keywords": ["cmi", "header", "connectionHello", "messageType"]
    },

    # ── SPINE Architecture & Protocol Questions (9-16)
    {
        "id": "SPINE-01",
        "category": "SPINE",
        "query": "Explain the SPINE resource model: Device, Entity, and Feature.",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_ResourceSpecification.pdf"],
        "target_keywords": ["device", "entity", "feature", "address"]
    },
    {
        "id": "SPINE-02",
        "category": "SPINE",
        "query": "What are the SPINE command classifiers and their roles?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_CommandFrame.xsd"],
        "target_keywords": ["read", "reply", "notify", "write", "call", "result"]
    },
    {
        "id": "SPINE-03",
        "category": "SPINE",
        "query": "What is the root structure of an EEBUS SPINE Datagram?",
        "expected_docs": ["EEBus_SPINE_TS_Datagram.xsd", "EEBus_SPINE_TS_ProtocolSpecification.pdf"],
        "target_keywords": ["datagram", "header", "payload", "cmd", "specificationVersion"]
    },
    {
        "id": "SPINE-04",
        "category": "SPINE",
        "query": "How does subscription management work in SPINE NodeManagement?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_SubscriptionManagement.xsd"],
        "target_keywords": ["subscriptionManagementRequestCall", "subscription", "notify"]
    },
    {
        "id": "SPINE-05",
        "category": "SPINE",
        "query": "How is binding established between complementary SPINE features?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_BindingManagement.xsd"],
        "target_keywords": ["bindingManagementRequestCall", "binding", "client", "server"]
    },
    {
        "id": "SPINE-06",
        "category": "SPINE",
        "query": "What is the format of SPINE feature addressing in datagram headers?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_CommonDataTypes.xsd"],
        "target_keywords": ["featureAddress", "device", "entity", "feature"]
    },
    {
        "id": "SPINE-07",
        "category": "SPINE",
        "query": "How does partial data read and write filtering operate in SPINE?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_CommandFrame.xsd"],
        "target_keywords": ["cmdControl", "partial", "filter"]
    },
    {
        "id": "SPINE-08",
        "category": "SPINE",
        "query": "What is the Heartbeat function in SPINE and how is keepalive signaled?",
        "expected_docs": ["EEBus_SPINE_TS_ProtocolSpecification.pdf", "EEBus_SPINE_TS_ResourceSpecification.pdf", "EEBus_SPINE_TS_DeviceDiagnosis.xsd"],
        "target_keywords": ["heartbeat", "deviceDiagnosis", "timestamp"]
    },

    # ── XSD Data Types & Schema Structure (17-21)
    {
        "id": "XSD-01",
        "category": "XSD",
        "query": "What is the schema definition and fields of LoadControlLimitDataType?",
        "expected_docs": ["EEBus_SPINE_TS_LoadControl.xsd", "EEBus_SPINE_TS_ResourceSpecification.pdf"],
        "target_keywords": ["LoadControlLimitDataType", "limitId", "limitValue", "value"]
    },
    {
        "id": "XSD-02",
        "category": "XSD",
        "query": "What fields are contained in DeviceClassificationUserDataDataType?",
        "expected_docs": ["EEBus_SPINE_TS_DeviceClassification.xsd", "EEBus_SPINE_TS_ResourceSpecification.pdf"],
        "target_keywords": ["deviceClassification", "userLabel", "DeviceClassification"]
    },
    {
        "id": "XSD-03",
        "category": "XSD",
        "query": "What are the allowed enum values for LoadControlEventActionEnumType?",
        "expected_docs": ["EEBus_SPINE_TS_LoadControl.xsd"],
        "target_keywords": ["pause", "resume", "reduce", "increase", "emergency", "normal"]
    },
    {
        "id": "XSD-04",
        "category": "XSD",
        "query": "What is the definition of MeasurementDescriptionDataType in SPINE?",
        "expected_docs": ["EEBus_SPINE_TS_Measurement.xsd", "EEBus_SPINE_TS_ResourceSpecification.pdf"],
        "target_keywords": ["measurementId", "measurementType", "unit", "scopeType"]
    },
    {
        "id": "XSD-05",
        "category": "XSD",
        "query": "What is the schema for ElectricalConnectionPermittedValueSetDataType?",
        "expected_docs": ["EEBus_SPINE_TS_ElectricalConnection.xsd", "EEBus_SPINE_TS_ResourceSpecification.pdf"],
        "target_keywords": ["ElectricalConnection", "permittedValueSet", "minValue", "maxValue"]
    },

    # ── Energy Use Cases (22-25)
    {
        "id": "UC-01",
        "category": "UseCase",
        "query": "How does Limitation of Power Consumption (LPC) operate in EEBUS?",
        "expected_docs": ["EEBus_UC_TS_LimitationOfPowerConsumption_V1.0.0_public.pdf", "EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf"],
        "target_keywords": ["LPC", "power consumption", "limit", "obligation"]
    },
    {
        "id": "UC-02",
        "category": "UseCase",
        "query": "How does Limitation of Power Production (LPP) control photovoltaic systems?",
        "expected_docs": ["EEBus_UC_TS_LimitationOfPowerProduction_V1.0.0_public.pdf"],
        "target_keywords": ["LPP", "PV", "production", "curtailment"]
    },
    {
        "id": "UC-03",
        "category": "UseCase",
        "query": "What are the required SPINE function sets for EVSE charging control?",
        "expected_docs": ["EEBus_UC_TS_EVSECommissioningAndConfiguration_V1.0.0_public.pdf", "EEBus_UC_TS_EVSupplyEquipmentState_V1.0.0_public.pdf"],
        "target_keywords": ["EVSE", "charging", "state", "configuration"]
    },
    {
        "id": "UC-04",
        "category": "UseCase",
        "query": "How does an Energy Management System (EMS) configure power limits for devices?",
        "expected_docs": ["EEBus_UC_TS_LimitationOfPowerConsumption_V1.0.0_public.pdf", "EEBus_UC_IG_LimitationOfPowerConsumption_V1.0.0.pdf", "EEBus_SPINE_TS_LoadControl.xsd"],
        "target_keywords": ["EMS", "limit", "loadControl", "power"]
    }
]


# ─── Evaluation Engine ─────────────────────────────────────────────────────────

def run_rag_benchmark(eval_top_k: int = 5) -> Dict[str, Any]:
    """
    Run the 25-query benchmark through the production Hybrid Retriever + Reranker pipeline.
    Computes HitRate@1, HitRate@3, HitRate@5, MRR, Structure Precision, and Average Latency.
    """
    print("=" * 70)
    print("🚀 Running EEBUS RAG Benchmark Evaluation Suite")
    print(f"   Golden Test Queries: {len(GOLDEN_EVALUATION_DATASET)}")
    print(f"   Retrieval Top-K:    {eval_top_k}")
    print("=" * 70)

    # Initialize production engine
    chat_engine, total_chunks = create_chat_engine(
        top_k=eval_top_k,
        component_filter="All Specifications",
        use_reranker=True,
        llm_provider="Mock"  # Fast evaluation focused on retrieval & ranking
    )

    retriever = chat_engine._retriever
    postprocessors = chat_engine._node_postprocessors

    results = []
    latencies = []
    hits_at_1 = 0
    hits_at_3 = 0
    hits_at_5 = 0
    reciprocal_ranks = []
    structural_hits = 0
    structural_queries = 0

    for idx, item in enumerate(GOLDEN_EVALUATION_DATASET, 1):
        q_id = item["id"]
        category = item["category"]
        query = item["query"]
        expected_docs = item["expected_docs"]
        
        t0 = time.time()
        
        # 1. Retrieve candidates via Hybrid Retriever
        retrieved_nodes = retriever.retrieve(query)
        
        # 2. Re-rank via Cross-Encoder
        if postprocessors:
            for p in postprocessors:
                retrieved_nodes = p.postprocess_nodes(retrieved_nodes, query_str=query)
                
        latency_ms = (time.time() - t0) * 1000
        latencies.append(latency_ms)

        # Check document match
        hit_rank = None
        for rank, node in enumerate(retrieved_nodes[:eval_top_k], 1):
            filename = node.metadata.get("filename", "")
            if any(exp.lower() in filename.lower() for exp in expected_docs):
                hit_rank = rank
                break

        if hit_rank == 1:
            hits_at_1 += 1
        if hit_rank and hit_rank <= 3:
            hits_at_3 += 1
        if hit_rank and hit_rank <= 5:
            hits_at_5 += 1

        rr = (1.0 / hit_rank) if hit_rank else 0.0
        reciprocal_ranks.append(rr)

        # Check structure-aware XSD match
        if category == "XSD":
            structural_queries += 1
            has_structural = any(
                n.metadata.get("schema_element_type") in ["complexType", "simpleType", "element"]
                for n in retrieved_nodes[:eval_top_k]
            )
            if has_structural:
                structural_hits += 1

        status_icon = "🟢" if hit_rank == 1 else "🟡" if hit_rank else "🔴"
        top_source = retrieved_nodes[0].metadata.get("filename", "None") if retrieved_nodes else "None"
        
        results.append({
            "id": q_id,
            "category": category,
            "query": query,
            "hit_rank": hit_rank,
            "top_source": top_source,
            "latency_ms": round(latency_ms, 1)
        })

        print(f"[{idx:02d}/25] {status_icon} {q_id:<8s} Rank: {str(hit_rank):<4s} | {latency_ms:5.1f}ms | Top: {top_source}")

    total = len(GOLDEN_EVALUATION_DATASET)
    hit_rate_1 = (hits_at_1 / total) * 100
    hit_rate_3 = (hits_at_3 / total) * 100
    hit_rate_5 = (hits_at_5 / total) * 100
    mrr = sum(reciprocal_ranks) / total
    avg_latency = sum(latencies) / total
    structure_prec = (structural_hits / structural_queries * 100) if structural_queries else 100.0

    scorecard = {
        "total_queries": total,
        "hit_rate_at_1": round(hit_rate_1, 1),
        "hit_rate_at_3": round(hit_rate_3, 1),
        "hit_rate_at_5": round(hit_rate_5, 1),
        "mrr": round(mrr, 3),
        "structure_precision": round(structure_prec, 1),
        "avg_latency_ms": round(avg_latency, 1),
        "total_chunks": total_chunks,
        "results": results
    }

    print("\n" + "=" * 70)
    print("📊 EEBUS RAG BENCHMARK SCORECARD")
    print("=" * 70)
    print(f"  Hit Rate @ 1:         {hit_rate_1:.1f}%")
    print(f"  Hit Rate @ 3:         {hit_rate_3:.1f}%")
    print(f"  Hit Rate @ 5:         {hit_rate_5:.1f}%")
    print(f"  Mean Reciprocal Rank: {mrr:.3f}")
    print(f"  XSD Structure Prec:   {structure_prec:.1f}%")
    print(f"  Average Latency:      {avg_latency:.1f} ms")
    print("=" * 70)

    # Save Markdown Report
    report_path = os.path.join(BASE_DIR, "tests", "benchmark_report.md")
    with open(report_path, "w", encoding="utf-8") as f:
        f.write(generate_markdown_report(scorecard))
    print(f"\n📄 Saved detailed report to: {report_path}\n")

    return scorecard


def generate_markdown_report(scorecard: Dict[str, Any]) -> str:
    """Generate clean Markdown benchmark report."""
    md = [
        "# 📊 EEBUS RAG Benchmark Evaluation Report\n",
        f"**Evaluated At:** {time.strftime('%Y-%m-%d %H:%M:%S')}",
        f"**Total Knowledge Base Chunks:** `{scorecard['total_chunks']:,}`",
        f"**Retrieval Pipeline:** Hybrid (Dense BGE-Small + Sparse BM25 via RRF)",
        f"**Reranker:** Cross-Encoder MS-MARCO\n",
        "## Overall Metrics\n",
        "| Metric | Target | Benchmark Result | Status |",
        "| :--- | :--- | :--- | :--- |",
        f"| **Hit Rate @ 1** | ≥ 65.0% | **{scorecard['hit_rate_at_1']}%** | {'✅ PASS' if scorecard['hit_rate_at_1'] >= 65 else '⚠️ WARN'} |",
        f"| **Hit Rate @ 3** | ≥ 80.0% | **{scorecard['hit_rate_at_3']}%** | {'✅ PASS' if scorecard['hit_rate_at_3'] >= 80 else '⚠️ WARN'} |",
        f"| **Hit Rate @ 5** | ≥ 85.0% | **{scorecard['hit_rate_at_5']}%** | {'✅ PASS' if scorecard['hit_rate_at_5'] >= 85 else '⚠️ WARN'} |",
        f"| **Mean Reciprocal Rank (MRR)** | ≥ 0.700 | **{scorecard['mrr']}** | {'✅ PASS' if scorecard['mrr'] >= 0.70 else '⚠️ WARN'} |",
        f"| **Structure-Aware XSD Precision** | 100.0% | **{scorecard['structure_precision']}%** | {'✅ PASS' if scorecard['structure_precision'] == 100 else '⚠️ WARN'} |",
        f"| **Average Latency** | < 3,500 ms | **{scorecard['avg_latency_ms']} ms** | {'✅ PASS' if scorecard['avg_latency_ms'] < 3500 else '⚠️ WARN'} |\n",
        "## Detailed Query Breakdown\n",
        "| ID | Category | Query | Hit Rank | Top Retrieved Document | Latency |",
        "| :--- | :--- | :--- | :--- | :--- | :--- |"
    ]
    for r in scorecard["results"]:
        rank_str = f"**#{r['hit_rank']}**" if r["hit_rank"] else "❌ Miss"
        md.append(f"| {r['id']} | {r['category']} | {r['query']} | {rank_str} | `{r['top_source']}` | {r['latency_ms']}ms |")

    return "\n".join(md)


if __name__ == "__main__":
    run_rag_benchmark()
