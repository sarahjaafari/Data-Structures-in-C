/*
 -------------------------------------
 File:    bst.c
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
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BSTNODE* new_bstnode(RECORD data);
BSTNODE* extract_smallest_node(BSTNODE **rootp);

BSTNODE* bst_search(BSTNODE *root, char *key) {

	if (root == NULL || strcmp(root->data.name, key) == 0) {
		return root;
	} else if (strcmp(key, root->data.name) < 0) {
		return bst_search(root->left, key);
	} else {
		return bst_search(root->right, key);
	}
}

void bst_insert(BSTNODE **rootp, RECORD data) {

	if (*rootp == NULL) {
		*rootp = new_bstnode(data);
	} else if (strcmp(data.name, (*rootp)->data.name) < 0) {
		bst_insert(&((*rootp)->left), data);
	} else if (strcmp(data.name, (*rootp)->data.name) > 0) {
		bst_insert(&((*rootp)->right), data);
	}
}

void bst_delete(BSTNODE **rootp, char *key) {

	if (*rootp == NULL)
		return;

	if (strcmp(key, (*rootp)->data.name) < 0) {
		bst_delete(&((*rootp)->left), key);
	} else if (strcmp(key, (*rootp)->data.name) > 0) {
		bst_delete(&((*rootp)->right), key);
	} else {
		// Node with only one child or no child
		if ((*rootp)->left == NULL) {
			BSTNODE *temp = *rootp;
			*rootp = (*rootp)->right;
			free(temp);
		} else if ((*rootp)->right == NULL) {
			BSTNODE *temp = *rootp;
			*rootp = (*rootp)->left;
			free(temp);
		} else {
			// Node with two children: Get the inorder successor
			BSTNODE *temp = extract_smallest_node(&((*rootp)->right));
			(*rootp)->data = temp->data;
			bst_delete(&((*rootp)->right), temp->data.name);
			free(temp);
		}
	}
}

BSTNODE* new_bstnode(RECORD data) {
	BSTNODE *np = (BSTNODE*) malloc(sizeof(BSTNODE));
	if (np) {
		np->data = data; // Correctly assign the data field
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

BSTNODE* extract_smallest_node(BSTNODE **rootp) {
	BSTNODE *p = *rootp, *parent = NULL;
	if (p) {
		while (p->left) {
			parent = p;
			p = p->left;
		}

		if (parent == NULL)
			*rootp = p->right;
		else
			parent->left = p->right;

		p->left = NULL;
		p->right = NULL;
	}

	return p;
}

void clean_bst(BSTNODE **rootp) {
	BSTNODE *root = *rootp;
	if (root) {
		if (root->left)
			clean_bst(&root->left);
		if (root->right)
			clean_bst(&root->right);
		free(root);
	}
	*rootp = NULL;
}
