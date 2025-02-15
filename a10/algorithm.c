/*
 -------------------------------------
 File:    algorithm.c
 Project: a10
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-04-03
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "algorithm.h"

EDGELIST* mst_prim(GRAPH *g, int start) {
	int visited[g->order];
	memset(visited, 0, sizeof(visited));
	HEAP *pq = new_heap(g->order * g->order);
	for (ADJNODE *node = g->nodes[start]->neighbor; node != NULL;
			node = node->next) {
		HEAPDATA newEdge = { node->weight, (start << 16) | node->nid };
		heap_insert(pq, newEdge);
	}
	visited[start] = 1;

	EDGELIST *mst = new_edgelist();
	while (pq->size > 0) {
		HEAPDATA edge = heap_extract_min(pq);
		int from = edge.value >> 16;
		int to = edge.value & 0xFFFF;
		if (visited[to])
			continue;
		insert_edge_end(mst, from, to, edge.key);
		visited[to] = 1;
		for (ADJNODE *node = g->nodes[to]->neighbor; node != NULL;
				node = node->next) {
			if (!visited[node->nid]) {
				HEAPDATA newEdge = { node->weight, (to << 16) | node->nid };
				heap_insert(pq, newEdge);
			}
		}
	}

	heap_clean(&pq);
	return mst;
}

EDGELIST* spt_dijkstra(GRAPH *g, int start) {
	int dist[g->order], prev[g->order];
	memset(dist, 0x3f, sizeof(dist));
	memset(prev, -1, sizeof(prev));
	dist[start] = 0;
	HEAP *pq = new_heap(g->order);
	HEAPDATA startData = { 0, start };
	heap_insert(pq, startData);
	while (pq->size > 0) {
		HEAPDATA minData = heap_extract_min(pq);
		int u = minData.value;
		for (ADJNODE *node = g->nodes[u]->neighbor; node != NULL;
				node = node->next) {
			int v = node->nid;
			int weight = node->weight;
			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				prev[v] = u;
				HEAPDATA newData = { dist[v], v };
				heap_insert(pq, newData);
			}
		}
	}
	EDGELIST *spt = new_edgelist();
	for (int i = 0; i < g->order; i++) {
		if (i != start && prev[i] != -1) {
			int weight = get_edge_weight(g, prev[i], i);
			insert_edge_end(spt, prev[i], i, weight);
		}
	}

	heap_clean(&pq);
	return spt;
}

EDGELIST* sp_dijkstra(GRAPH *g, int start, int end) {
	int dist[g->order], prev[g->order];
	memset(dist, 0x3f, sizeof(dist));
	memset(prev, -1, sizeof(prev));
	dist[start] = 0;

	HEAP *pq = new_heap(g->order);
	HEAPDATA startData = { 0, start };
	heap_insert(pq, startData);

	while (pq->size > 0) {
		HEAPDATA minData = heap_extract_min(pq);
		int u = minData.value;
		if (u == end)
			break;
		for (ADJNODE *node = g->nodes[u]->neighbor; node != NULL;
				node = node->next) {
			int v = node->nid;
			int weight = node->weight;
			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				prev[v] = u;
				HEAPDATA newData = { dist[v], v };
				heap_insert(pq, newData);
			}
		}
	}
	EDGELIST *path = new_edgelist();
	for (int at = end; at != -1; at = prev[at]) {
		if (prev[at] != -1) {
			int weight = get_edge_weight(g, prev[at], at);
			insert_edge_start(path, prev[at], at, weight);
		}
	}

	heap_clean(&pq);
	return path;
}
