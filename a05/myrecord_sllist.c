/*
 -------------------------------------
 File:    myrecord_sllist.c
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
#include <string.h>
#include "myrecord_sllist.h"

NODE* sll_search(SLL *sllp, char *name) {

	NODE *r = NULL;
	NODE *np = sllp->start;
	while (np != NULL) {
		if (strcmp(np->data.name, name) == 0) { // if pattern matchr = np; // action
			r = np;
			break;
		} else {
			np = np->next;
		}
	}
	return r;
}

void sll_insert(SLL *sllp, char *name, float score) {

	NODE *np = (NODE*) malloc(sizeof(NODE));
	strcpy(np->data.name, name);
	np->data.score = score;
	np->next = NULL;

	NODE *prev = NULL;
	NODE *p = sllp->start;

	while (p != NULL) {
		if (strcmp(p->data.name, name) >= 0) {
			break;
		} else {
			prev = p;
			p = p->next;
		}
	}
	if (prev == NULL) {
		sllp->start = np;
		np->next = p;
	} else {

		prev->next = np;
		np->next = p;
	}
	sllp->length += 1;
}

int sll_delete(SLL *sllp, char *name) {

	NODE *ptr = sllp->start;
	NODE *prev = NULL;

	if (ptr == NULL) {
		return -1;
	}

	while (ptr->next != NULL && strcmp(ptr->data.name, name) != 0) {
		prev = ptr;
		ptr = ptr->next;
	}

	if (strcmp(ptr->data.name, name) != 0) {
		return -1;
	} else if (prev == NULL) {
		sllp->start = NULL;
		free(ptr);
		sllp->length -= 1;
	} else {
		prev->next = ptr->next;
		free(ptr);
		sllp->length -= 1;
	}

	return 1;
}

void sll_clean(SLL *sllp) {
	NODE *temp, *ptr = sllp->start;
	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
	sllp->start = NULL;
	sllp->length = 0;
}
