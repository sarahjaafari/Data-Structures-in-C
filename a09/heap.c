/*
 -------------------------------------
 File:    heap.c
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
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
	int r = 0;
	if (a < b)
		r = -1;
	else if (a > b)
		r = 1;
	return r;
}

HEAP* new_heap(int capacity) {
	HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
	if (hp == NULL)
		return NULL;
	hp->hda = (HEAPDATA*) malloc(sizeof(HEAPDATA) * capacity);
	if (hp->hda == NULL) {
		free(hp);
		return NULL;
	};
	hp->capacity = capacity;
	hp->size = 0;
	return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) {
	while (index > 0 && cmp(hda[(index - 1) / 2].key, hda[index].key) > 0) {
		HEAPDATA temp = hda[index];
		hda[index] = hda[(index - 1) / 2];
		hda[(index - 1) / 2] = temp;
		index = (index - 1) / 2;
	}
	return index;
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index) {
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left < n && hda[left].key < hda[smallest].key) {
		smallest = left;
	}
	if (right < n && hda[right].key < hda[smallest].key) {
		smallest = right;
	}
	if (smallest != index) {
		HEAPDATA temp = hda[index];
		hda[index] = hda[smallest];
		hda[smallest] = temp;
		smallest = heapify_down(hda, n, smallest);
	}
	return smallest;
}

void heap_insert(HEAP *heap, HEAPDATA new_node) {
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;
		heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
	}
	heap->hda[heap->size] = new_node;
	heap->size++;
	heapify_up(heap->hda, heap->size - 1);
}

HEAPDATA heap_find_min(HEAP *heap) {
	if (heap->size == 0) {
		HEAPDATA null_data = { 0, 0 };
		return null_data;
	}
	return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap) {
	if (heap->size == 0) {
		HEAPDATA null_data = { 0, 0 };
		return null_data;
	}
	HEAPDATA min = heap->hda[0];
	heap->hda[0] = heap->hda[heap->size - 1];
	heap->size--;
	heapify_down(heap->hda, heap->size, 0);
	if (heap->size <= (heap->capacity / 4) && heap->capacity > 4) {
		heap->capacity /= 2;
		heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
	}
	return min;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
	if (index < 0 || index >= heap->size) {
		return -1; // Invalid index
	}
	KEYTYPE old_key = heap->hda[index].key;
	heap->hda[index].key = new_key;
	if (new_key < old_key) {
		return heapify_up(heap->hda, index);
	} else {
		return heapify_down(heap->hda, heap->size, index);
	}
}

int heap_search_data(HEAP *heap, VALUETYPE data) {
	for (int i = 0; i < heap->size; i++) {
		if (heap->hda[i].value == data) {
			return i; // Found the element, return its index
		}
	}
	return -1;
}

void heap_clean(HEAP **heapp) {
	if (heapp) {
		HEAP *heap = *heapp;
		if (heap->capacity > 0) {
			heap->capacity = 0;
			heap->size = 0;
			free(heap->hda);
			free(heap);
		}
		*heapp = NULL;
	}
}
