/*
 -------------------------------------
 File:    stack.c
 Project: a06
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-02
 -------------------------------------
 */

#include <stdio.h>
#include "stack.h"

void push(STACK *sp, NODE *np) {

	np->next = sp->top;
	sp->top = np;
	sp->length++;
}

NODE* pop(STACK *sp) {

	if (sp->top == NULL) {
		return NULL;
	}

	NODE *temp_node = sp->top;
	sp->top = sp->top->next;
	sp->length--;
	temp_node->next = NULL;
	return temp_node;
}

void clean_stack(STACK *sp) {
	clean(&(sp->top));
	sp->top = NULL;
	sp->length = 0;
}
