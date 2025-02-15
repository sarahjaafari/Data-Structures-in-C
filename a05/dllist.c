/*
 -------------------------------------
 File:    dllist.c
 Project: a05
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-17
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

NODE* new_node(char data) {

	NODE *node = (NODE*) malloc(sizeof(NODE));
	if (node == NULL) {
		// Handle memory allocation failure
		exit(1);
	}
	node->data = data;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void dll_insert_start(DLL *dllp, NODE *np) {

	NODE *temp = dllp->start;
	dllp->start = np;
	np->next = temp;
	np->prev = NULL;
	dllp->length += 1;
	if (dllp->end == NULL) {
		dllp->end = np;
	} else {
		temp->prev = np;
	}
}

void dll_insert_end(DLL *dllp, NODE *np) {

	NODE *temp = dllp->end;
	dllp->end = np;
	np->prev = temp;
	np->next = NULL;
	dllp->length += 1;
	if (dllp->start == NULL) {
		dllp->start = np;
	} else {
		temp->next = np;
	}
}

void dll_delete_start(DLL *dllp) {

	if (dllp->start == NULL) {
		// List is empty, nothing to delete
		return;
	}

	NODE *temp = dllp->start;
	if (dllp->start == dllp->end) {
		// Only one element in the list
		dllp->start = NULL;
		dllp->end = NULL;
	} else {
		dllp->start = dllp->start->next;
		dllp->start->prev = NULL;
	}

	free(temp);
	dllp->length -= 1;
}

void dll_delete_end(DLL *dllp) {

	if (dllp->end == NULL) {
		return;
	}

	NODE *temp = dllp->end;
	if (dllp->start == dllp->end) {
		dllp->start = NULL;
		dllp->end = NULL;
	} else {
		dllp->end = dllp->end->prev;
		dllp->end->next = NULL;
	}

	free(temp);
	dllp->length -= 1;
}

void dll_clean(DLL *dllp) {

	NODE *curr = dllp->start;
	NODE *prev = NULL;

	while (curr != NULL) {

		prev = curr;
		curr = curr->next;
		free(prev);
	}

	dllp->start = NULL;
	dllp->end = NULL;
	dllp->length = 0;
}
