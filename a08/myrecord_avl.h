/*
 -------------------------------------
 File:    myrecord_avl.h
 Project: a08
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-16
 -------------------------------------
 */
#ifndef MYRECORD_AVL_H_
#define MYRECORD_AVL_H_

/*  This structure holds the root pointer of AVL tree data structure,
 *  and count, mean and stddev of the data.score in the AVL tree.
 */
typedef struct {
	AVLNODE *root;
	int count;
	float mean;
	float stddev;
} AVLDS;

/*  Merge source AVL tree into destination AVL tree. No change to source tree.
 *  @parame rootp_dest   - pointer to pointer of root of destination tree
 *  @parame rootp_source - pointer to pointer of root of source tree
 */
void merge_avl(AVLNODE **rootp_dest, AVLNODE **rootp_source);

/*  Merge source AVLDS to destination AVLDS. Clean source AVLDS
 *  @parame source - pointer to the source AVLDS
 *  @parame dest - pointer to the destination AVLDS
 */
void merge_avlds(AVLDS *dest, AVLDS *source);

/*  Clean its AVL tree and set count=0, mean=0, stddev=0
 *  @parame ds - pointer to the AVLDS
 */
void clean_avlds(AVLDS *ds);

// The following two functions are similar to that of A7Q3.
void add_record(AVLDS *ds, RECORD data);
void remove_record(AVLDS *ds, char *name);

#endif /* MYRECORD_AVL_H_ */
