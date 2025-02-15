/**
 * -------------------------------------
 * @file  queue_linked.c
 * Linked Queue Source Code File
 * -------------------------------------
 * @author name, ID, email
 *
 * @version 2024-02-22
 *
 * -------------------------------------
 */
// Includes
#include "queue_linked.h"

// Functions

queue_linked* queue_initialize() {

    // your code here

}

void queue_free(queue_linked **source) {

    // your code here

}

BOOLEAN queue_empty(const queue_linked *source) {

    // your code here

}

int queue_count(const queue_linked *source) {

    // your code here

}

void queue_insert(queue_linked *source, data_ptr item) {

    // your code here

}

BOOLEAN queue_peek(const queue_linked *source, data_ptr item) {

    // your code here

}

BOOLEAN queue_remove(queue_linked *source, data_ptr *item) {

    // your code here

}

void queue_print(const queue_linked *source) {
    char string[DATA_STRING_SIZE];
    queue_node *current = source->front;

    while(current != NULL) {
        printf("%s\n", data_string(string, sizeof string, current->item));
        current = current->next;
    }
    return;
}
