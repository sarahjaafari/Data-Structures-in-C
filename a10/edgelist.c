/*
 -------------------------------------
 File:    edgelist.c
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
#include "edgelist.h"

EDGELIST* new_edgelist() {
	EDGELIST *tp = malloc(sizeof(EDGELIST));
	tp->size = 0;
	tp->start = NULL;
	tp->end = NULL;
	return tp;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
	EDGENODE *newNode = malloc(sizeof(EDGENODE));
	newNode->from = from;
	newNode->to = to;
	newNode->weight = weight;
	newNode->next = NULL;

	if (g->end == NULL) { // Empty list
		g->start = g->end = newNode;
	} else {
		g->end->next = newNode;
		g->end = newNode;
	}
	g->size++;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
	EDGENODE *newNode = malloc(sizeof(EDGENODE));
	newNode->from = from;
	newNode->to = to;
	newNode->weight = weight;
	newNode->next = g->start;

	g->start = newNode;
	if (g->end == NULL) { // Empty list
		g->end = newNode;
	}
	g->size++;
}

void delete_edge(EDGELIST *g, int from, int to) {
	EDGENODE *temp = g->start, *prev = NULL;
	while (temp != NULL && (temp->from != from || temp->to != to)) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
		return; // Edge not found

	if (prev == NULL) { // Edge is the first node
		g->start = temp->next;
	} else {
		prev->next = temp->next;
	}

	if (temp == g->end) { // Edge is the last node
		g->end = prev;
	}

	free(temp);
	g->size--;
}

int weight_edgelist(EDGELIST *g) {
	int totalWeight = 0;
	EDGENODE *temp = g->start;
	while (temp != NULL) {
		totalWeight += temp->weight;
		temp = temp->next;
	}
	return totalWeight;
}

void clean_edgelist(EDGELIST **gp) {
	EDGELIST *g = *gp;
	EDGENODE *temp, *p = g->start;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(g);
	*gp = NULL;
}

void display_edgelist(EDGELIST *g) {
	if (g == NULL)
		return;
	printf("size %d ", g->size);
	printf("(from to weight) ");
	EDGENODE *p = g->start;
	while (p) {
		printf("(%d %d %d) ", p->from, p->to, p->weight);
		p = p->next;
	}
}
