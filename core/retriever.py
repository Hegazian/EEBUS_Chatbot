"""
EEBUS Hybrid Retriever & Fusion Algorithms
Combines dense vector embeddings with sparse BM25 lexical search using Reciprocal Rank Fusion.
"""

import os
from typing import List, Optional
from llama_index.core.retrievers import BaseRetriever
from llama_index.core.schema import NodeWithScore, QueryBundle, TextNode
from llama_index.retrievers.bm25 import BM25Retriever
from .config import BM25_PERSIST_DIR


class EEBUSHybridRetriever(BaseRetriever):
    """
    Production Hybrid Retriever combining:
    1. Dense semantic search (ChromaDB VectorIndex)
    2. Sparse lexical search (BM25 for protocol enums, hex IDs, XSD tags, and error codes)
    3. Component-level metadata filtering (SHIP, SPINE, UseCase)
    4. Reciprocal Rank Fusion (RRF) for balanced multi-modal passage scoring
    """
    def __init__(
        self,
        vector_retriever: BaseRetriever,
        bm25_retriever: Optional[BaseRetriever] = None,
        component_filter: str = "All Specifications",
        candidate_k: int = 16
    ):
        super().__init__()
        self.vector_retriever = vector_retriever
        self.bm25_retriever = bm25_retriever
        self.component_filter = component_filter
        self.candidate_k = candidate_k

    def _apply_component_filter(self, nodes: List[NodeWithScore]) -> List[NodeWithScore]:
        if not self.component_filter or self.component_filter in ["All", "All Specifications"]:
            return nodes
        
        filtered = []
        filter_lower = self.component_filter.lower()
        
        if "ship" in filter_lower:
            target = "SHIP"
        elif "spine" in filter_lower:
            target = "SPINE"
        elif "use" in filter_lower:
            target = "USECASE"
        else:
            target = self.component_filter.upper()

        for item in nodes:
            meta = item.node.metadata if hasattr(item, "node") else getattr(item, "metadata", {}) or {}
            comp = (meta.get("component") or "").upper()
            if target in comp or comp in target:
                filtered.append(item)
        return filtered

    def _retrieve(self, query_bundle: QueryBundle) -> List[NodeWithScore]:
        vector_nodes = self._apply_component_filter(self.vector_retriever.retrieve(query_bundle))
        
        bm25_nodes = []
        if self.bm25_retriever:
            try:
                bm25_nodes = self._apply_component_filter(self.bm25_retriever.retrieve(query_bundle))
            except Exception as err:
                print(f"⚠️ BM25 retrieve note: {err}")
                bm25_nodes = []

        if not bm25_nodes:
            return vector_nodes[:self.candidate_k]
        if not vector_nodes:
            return bm25_nodes[:self.candidate_k]

        # Reciprocal Rank Fusion (RRF, k=60) with Normative Document Weighting
        node_dict = {}
        rrf_scores = {}
        k = 60

        def get_doc_weight(meta: dict) -> float:
            doc_kind = str(meta.get("doc_kind", "")).lower()
            fname = str(meta.get("filename", "")).upper()
            file_type = str(meta.get("file_type", "")).lower()

            # Primary technical specifications & schema definitions
            if file_type == "schema" or "_TS_" in fname or "SPECIFICATION" in doc_kind:
                return 1.15
            # Implementation guides
            if "_IG_" in fname or "IMPLEMENTATION_GUIDE" in doc_kind:
                return 1.00
            # Overview documents, summaries, and technical reports get slightly lower weighting
            if "OVERVIEW" in fname or "_TR_" in fname or "REPORT" in doc_kind:
                return 0.70
            return 0.90

        for rank, item in enumerate(vector_nodes):
            nid = item.node.node_id
            node_dict[nid] = item.node
            meta = item.node.metadata if hasattr(item, "node") else {}
            weight = get_doc_weight(meta)
            rrf_scores[nid] = rrf_scores.get(nid, 0.0) + (weight * (1.0 / (k + rank + 1)))

        for rank, item in enumerate(bm25_nodes):
            nid = item.node.node_id
            if nid not in node_dict:
                node_dict[nid] = item.node
            meta = item.node.metadata if hasattr(item, "node") else {}
            weight = get_doc_weight(meta)
            rrf_scores[nid] = rrf_scores.get(nid, 0.0) + (weight * (1.0 / (k + rank + 1)))

        sorted_ids = sorted(rrf_scores.keys(), key=lambda x: rrf_scores[x], reverse=True)
        return [NodeWithScore(node=node_dict[nid], score=rrf_scores[nid]) for nid in sorted_ids[:self.candidate_k]]


def sync_bm25_from_chroma(chroma_collection, persist_dir: str = BM25_PERSIST_DIR):
    """Rebuild and persist BM25 index from all documents in ChromaDB collection."""
    print(f"\n🔍 Syncing BM25 sparse index at {persist_dir}...")
    try:
        data = chroma_collection.get(include=["documents", "metadatas"])
        if not data or not data["documents"]:
            print("  ℹ️ No documents in ChromaDB to build BM25 index.")
            return None
        
        all_nodes = [
            TextNode(text=doc, metadata=meta, id_=doc_id)
            for doc, meta, doc_id in zip(data["documents"], data["metadatas"], data["ids"])
        ]
        bm25_retriever = BM25Retriever.from_defaults(nodes=all_nodes)
        os.makedirs(persist_dir, exist_ok=True)
        bm25_retriever.persist(persist_dir)
        print(f"  → BM25 index successfully synced with {len(all_nodes):,} nodes.")
        return bm25_retriever
    except Exception as err:
        print(f"⚠️ Warning building BM25 index: {err}")
        return None
