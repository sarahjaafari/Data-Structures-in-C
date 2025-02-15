/*
 -------------------------------------
 File:    queue.h
 Project: a06
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-02
 -------------------------------------
 */
#ifndef QUEUE_H_
#define QUEUE_H_
#include "common.h"

/*
 * Define a structure QUEUE containing length and pointers of front and rare node.
 * int length - maintains the length of queue,
 * NODE *front - pointer to the front node of linked list queue
 * NODE *rear - points to the rare node of linked list queue
 */
typedef struct queue {
	int length;
	NODE *front;
	NODE *rear;
} QUEUE;

/*
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue
 * @param NODE *np - pointer to the node.
 */
void enqueue(QUEUE *qp, NODE *np);

/*
 * Dequeue and return the pointer of the removed node.
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL
 */
NODE* dequeue(QUEUE *qp);

/*
 * Clean the linked list queue
 */
void clean_queue(QUEUE *qp);

#endif /* QUEUE_H_ */
