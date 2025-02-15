/*
 -------------------------------------
 File:    myrecord_bst.h
 Project: a07
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-09
 -------------------------------------
 */
#ifndef MYRECORD_BST_H_
#define MYRECORD_BST_H_

#include "bst.h"

/* Define data type BSTSD contains pointer to a BST in which data are stored, and
 * stats count, mean, and stddev of the scores.
 */
typedef struct {
	BSTNODE *root;
	int count;
	float mean;
	float stddev;
} BSTDS;

/* Add a record data into the BSTDS and update its stats info incrementally.
 *
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void add_record(BSTDS *ds, RECORD record);

/* Delete a record of the given name from the BST tree of BSTDS
 * and update its stats info incrementally.
 * @parame ds - pointer to the BSTDS.
 * @parama record - RECORD data to be added.
 */
void remove_record(BSTDS *ds, char *name);

/* Clean BST tree of BSTDS and reset count, mean, stddev
 * @parame ds - pointer to the BSTDS.
 */
void clean_bstds(BSTDS *ds);

#endif /* MYRECORD_BST_H_ */
