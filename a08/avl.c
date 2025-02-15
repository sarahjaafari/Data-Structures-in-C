/*
 -------------------------------------
 File:    avl.c
 Project: a08
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-16
 -------------------------------------
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

/* Create and return AVLNODE of given data
 * Use malloc()
 * @param data - data for the new node.
 * @return - pointer to the new AVLNODE.
 */
AVLNODE* new_node(RECORD data);

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor a the node,
 */
int balance_factor(AVLNODE *np);

/* This function does the left rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE* rotate_left(AVLNODE *np);

/* This function does the right rotation at a given node
 * @param np - pointer to the rotation node.
 * @return - the pointer to the replaced node.
 */
AVLNODE* rotate_right(AVLNODE *root);

AVLNODE* extract_smallest_node(AVLNODE **rootp);

AVLNODE* new_node(RECORD data) {
	AVLNODE *np = (AVLNODE*) malloc(sizeof(AVLNODE));
	if (np) {
		np->data = data;
		np->height = 1;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(AVLNODE *np) {
	if (np == NULL)
		return 0;
	return np->height;
}

int balance_factor(AVLNODE *np) {
	if (np == NULL)
		return 0;
	return height(np->left) - height(np->right);
}

AVLNODE* rotate_right(AVLNODE *y) {
	AVLNODE *x = y->left;
	AVLNODE *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

AVLNODE* rotate_left(AVLNODE *x) {
	AVLNODE *y = x->right;
	AVLNODE *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}

void avl_insert(AVLNODE **rootp, RECORD data) {
	// 1. Perform the normal BST insertion
	if (*rootp == NULL) {
		AVLNODE *np = (AVLNODE*) malloc(sizeof(AVLNODE));
		if (np) {
			np->data = data;
			np->height = 1;
			np->left = NULL;
			np->right = NULL;
		}
		*rootp = np;
	} else {

		AVLNODE *root = *rootp;

		if (strcmp(data.name, root->data.name) == 0)
			return;
		else if (strcmp(data.name, root->data.name) < 0) {
			avl_insert(&root->left, data);
		} else {
			avl_insert(&root->right, data);
		}

		// 2. update height of this ancestor node
		root->height = 1 + max(height(root->left), height(root->right));

		// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
		int balance = balance_factor(root);

		// 4. rebalance if not balanced
		if (balance > 1 && strcmp(data.name, root->left->data.name) < 0) {
			// Left Left Case
			*rootp = rotate_right(root);
		} else if (balance < -1
				&& strcmp(data.name, root->right->data.name) > 0) {
			// Right Right Case
			*rootp = rotate_left(root);
		} else if (balance > 1
				&& strcmp(data.name, root->left->data.name) > 0) {
			// Left Right Case
			root->left = rotate_left(root->left);
			*rootp = rotate_right(root);
		} else if (balance < -1
				&& strcmp(data.name, root->right->data.name) < 0) {
			// Right Left Case
			root->right = rotate_right(root->right);
			*rootp = rotate_left(root);
		}
	}
}

void avl_delete(AVLNODE **rootp, char *name) {
	AVLNODE *root = *rootp;
	AVLNODE *np;
	if (root == NULL)
		return;

	if (strcmp(name, root->data.name) == 0) {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			*rootp = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			np = root->left;
			free(root);
			*rootp = np;
		} else if (root->left == NULL && root->right != NULL) {
			np = root->right;
			free(root);
			*rootp = np;
		} else if (root->left != NULL && root->right != NULL) {
			np = extract_smallest_node(&root->right);
			np->left = root->left;
			np->right = root->right;
			free(root);
			*rootp = np;
		}
	} else {
		if (strcmp(name, root->data.name) < 0) {
			avl_delete(&root->left, name);
		} else {
			avl_delete(&root->right, name);
		}
	}

// If the tree had only one node then return
	if (*rootp == NULL)
		return;
	root = *rootp;

// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left), height(root->right));

// STEP 3: GET THE BALANCE FACTOR OF THIS NODE
	int balance = balance_factor(root);

// STEP 4: rebalance if not balanced
// Left Left Case
	if (balance > 1 && balance_factor(root->left) >= 0) {
		*rootp = rotate_right(root);
	}
	// Left Right Case
	else if (balance > 1 && balance_factor(root->left) < 0) {
		root->left = rotate_left(root->left);
		*rootp = rotate_right(root);
	}
	// Right Right Case
	else if (balance < -1 && balance_factor(root->right) <= 0) {
		*rootp = rotate_left(root);
	}
	// Right Left Case
	else if (balance < -1 && balance_factor(root->right) > 0) {
		root->right = rotate_right(root->right);
		*rootp = rotate_left(root);
	}

}

AVLNODE* avl_search(AVLNODE *root, char *name) {
	if (root == NULL || strcmp(name, root->data.name) == 0)
		return root;
	if (strcmp(name, root->data.name) > 0)
		return avl_search(root->right, name);
	return avl_search(root->left, name);
}

AVLNODE* extract_smallest_node(AVLNODE **rootp) {
	AVLNODE *p = *rootp, *parent = NULL;
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
void clean_avl(AVLNODE **rootp) {
	AVLNODE *root = *rootp;
	if (root) {
		if (root->left)
			clean_avl(&root->left);
		if (root->right)
			clean_avl(&root->right);
		free(root);
	}
	*rootp = NULL;
}
