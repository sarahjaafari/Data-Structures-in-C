/*
 -------------------------------------
 File:    myrecord_bst.c
 Project: a07
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-09
 -------------------------------------
 */
#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {

	bst_insert(&(ds->root), record);

	ds->count++;
	float old_mean = ds->mean;
	ds->mean += (record.score - ds->mean) / ds->count;
	ds->stddev = sqrt(
			((ds->stddev * ds->stddev + old_mean * old_mean) * (ds->count - 1)
					+ record.score * record.score) / ds->count
					- ds->mean * ds->mean);
}

void remove_record(BSTDS *ds, char *name) {

	BSTNODE *node = bst_search(ds->root, name);
	if (node != NULL) {
		float score = node->data.score;
		bst_delete(&(ds->root), name);
		if (ds->count > 1) {
			float old_mean = ds->mean;
			ds->count--;
			ds->mean = ((ds->count + 1) * old_mean - score) / ds->count;
			if (ds->count > 1) {
				ds->stddev =
						sqrt(
								((ds->count + 1)
										* (ds->stddev * ds->stddev
												+ old_mean * old_mean)
										- ds->mean * ds->mean * ds->count
										- score * score) / ds->count);
			} else {
				ds->stddev = 0;
			}
		} else {
			ds->count = 0;
			ds->mean = 0;
			ds->stddev = 0;
		}
	}
}

void clean_bstds(BSTDS *ds) {
	clean_bst(&ds->root);
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}
