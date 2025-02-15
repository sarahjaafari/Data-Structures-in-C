/*
 -------------------------------------
 File:    queue.c
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
#include "queue.h"
#include "common.h"

void enqueue(QUEUE *qp, NODE *np) {

	if (qp->rear == NULL) {
		qp->front = np;
		qp->rear = np;
	} else {
		qp->rear->next = np;
		qp->rear = np;
	}
	qp->length++;
}

NODE* dequeue(QUEUE *qp) {

	if (qp->front == NULL) {
		return NULL;
	}

	NODE *temp_node = qp->front;
	qp->front = qp->front->next;

	if (qp->front == NULL) {
		qp->rear = NULL;
	}

	qp->length--;
	temp_node->next = NULL;
	return temp_node;

}

void clean_queue(QUEUE *qp) {
	clean(&(qp->front));
	qp->front = NULL;
	qp->rear = NULL;
	qp->length = 0;
}
