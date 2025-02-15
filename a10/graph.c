/*
 -------------------------------------
 File:    graph.c
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
#include "queue_stack.h"
#include "graph.h"

GRAPH* new_graph(int order) {
	GRAPH *gp = malloc(sizeof(GRAPH));
	gp->nodes = malloc(order * sizeof(GNODE*));

	int i;
	for (i = 0; i < order; i++) {
		gp->nodes[i] = malloc(sizeof(GNODE));
		gp->nodes[i]->nid = i;
		strcpy(gp->nodes[i]->name, "null");
		gp->nodes[i]->neighbor = NULL;
	}

	gp->order = order;
	gp->size = 0;

	return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
	if (!g || from >= g->order || to >= g->order)
		return;

	ADJNODE **curr = &(g->nodes[from]->neighbor);
	while (*curr) {
		if ((*curr)->nid == to) {
			(*curr)->weight = weight; // Edge exists, update weight
			return;
		}
		curr = &((*curr)->next);
	}
	// Edge does not exist, add new
	ADJNODE *newEdge = (ADJNODE*) malloc(sizeof(ADJNODE));
	if (!newEdge)
		return; // Memory allocation check
	newEdge->nid = to;
	newEdge->weight = weight;
	newEdge->next = NULL;
	*curr = newEdge; // Link the new edge
	g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to) {
	if (!g || from >= g->order || to >= g->order)
		return;

	ADJNODE **curr = &(g->nodes[from]->neighbor);
	while (*curr) {
		if ((*curr)->nid == to) {
			ADJNODE *temp = *curr;
			*curr = (*curr)->next; // Remove from list
			free(temp); // Free memory
			g->size--;
			return;
		}
		curr = &((*curr)->next);
	}
}

int get_edge_weight(GRAPH *g, int from, int to) {
	if (from < 0 || from >= g->order || to < 0 || to >= g->order)
		return -1; // Invalid indices

	ADJNODE *p = g->nodes[from]->neighbor;
	while (p) {
		if (p->nid == to) {
			return p->weight; // Edge found
		}
		p = p->next;
	}
	return -1;
}

void traverse_bforder(GRAPH *g, int nid) {
	int visited[g->order];
	memset(visited, 0, sizeof(visited));

	QUEUE q;
	q.front = q.rear = NULL;

	enqueue(&q, g->nodes[nid]);
	visited[nid] = 1;

	while (q.front != NULL) {
		GNODE *node = (GNODE*) dequeue(&q);
		printf("(%d %s) ", node->nid, node->name);

		ADJNODE *neighbor = node->neighbor;
		while (neighbor != NULL) {
			if (!visited[neighbor->nid]) {
				enqueue(&q, g->nodes[neighbor->nid]);
				visited[neighbor->nid] = 1;
			}
			neighbor = neighbor->next;
		}
	}

	clean_queue(&q);
	printf("\n");
}

// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid) {
	if (nid < 0 || nid >= g->order)
		return; // Invalid index

	int visited[g->order];
	for (int i = 0; i < g->order; i++)
		visited[i] = 0;

	STACK s;
	s.top = NULL;

	push(&s, g->nodes[nid]);

	while (s.top) {
		GNODE *node = (GNODE*) pop(&s);
		if (!visited[node->nid]) {
			visited[node->nid] = 1;
			printf("%d ", node->nid);

			ADJNODE *p = node->neighbor;
			while (p) {
				if (!visited[p->nid]) {
					push(&s, g->nodes[p->nid]);
				}
				p = p->next;
			}
		}
	}
}

void clean_graph(GRAPH **gp) {
	int i;
	GRAPH *g = *gp;
	ADJNODE *temp, *ptr;
	for (i = 0; i < g->order; i++) {
		ptr = g->nodes[i]->neighbor;
		while (ptr != NULL) {
			temp = ptr;
			ptr = ptr->next;
			free(temp);
		}
		free(g->nodes[i]);
	}
	free(g->nodes);
	free(g);
	*gp = NULL;
}

void display_graph(GRAPH *g) {
	if (g) {
		printf("order %d ", g->order);
		printf("size %d ", g->size);
		printf("(from to weight) ");
		int i;
		ADJNODE *ptr;
		for (i = 0; i < g->order; i++) {
			//printf("\n%d:", g->nodes[i]->nid);
			ptr = g->nodes[i]->neighbor;
			while (ptr != NULL) {
				printf("(%d %d %d) ", i, ptr->nid, ptr->weight);
				ptr = ptr->next;
			}
		}
	}
}
