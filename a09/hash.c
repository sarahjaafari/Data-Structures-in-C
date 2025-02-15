/*
 -------------------------------------
 File:    hash.c
 Project: a09
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-23
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HASHNODE* hashtable_search(HASHTABLE *ht, char *key) {
	int index = hash(key, ht->size);
	HASHNODE *current = ht->hna[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

int hashtable_insert(HASHTABLE *ht, char *key, int value) {
	HASHNODE *newNode = hashtable_search(ht, key);
	if (newNode != NULL) {
		newNode->value = value;
		return 0;
	} else {
		int index = hash(key, ht->size);
		newNode = (HASHNODE*) malloc(sizeof(HASHNODE));
		if (!newNode) {
			return -1;
		}
		strcpy(newNode->key, key);
		newNode->value = value;
		newNode->next = NULL;

		if (ht->hna[index] == NULL) {
			ht->hna[index] = newNode;
		} else {
			HASHNODE *current = ht->hna[index];
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = newNode;
		}

		ht->count++;
		return 1;
	}
}

int hashtable_delete(HASHTABLE *ht, char *key) {
	int index = hash(key, ht->size);
	HASHNODE *current = ht->hna[index];
	HASHNODE *previous = NULL;
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			if (previous == NULL) {
				ht->hna[index] = current->next;
			} else {
				previous->next = current->next;
			}
			free(current);
			ht->count--;
			return 1;
		}
		previous = current;
		current = current->next;
	}
	return 0;
}

int hash(char *key, int size) {
	unsigned int hash = 0;
	while (*key) {
		hash += *key++;
	}
	return hash % size;
}

HASHTABLE* new_hashtable(int size) {
	HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
	ht->hna = (HASHNODE**) malloc(sizeof(HASHNODE**) * size);
	int i;
	for (i = 0; i < size; i++)
		*(ht->hna + i) = NULL;

	ht->size = size;
	ht->count = 0;
	return ht;
}

void hashtable_clean(HASHTABLE **htp) {
	if (*htp == NULL)
		return;
	HASHTABLE *ht = *htp;
	HASHNODE *p, *temp;
	int i;
	for (i = 0; i < ht->size; i++) {
		p = ht->hna[i];
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		ht->hna[i] = NULL;
	}
	free(ht->hna);
	ht->hna = NULL;
	*htp = NULL;
}
