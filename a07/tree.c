/*
 -------------------------------------
 File:    tree.c
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
#include "queue_stack.h"
#include "tree.h"

int max(int a, int b) {
	return (a > b) ? a : b;
}

int tree_height(TNODE *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + max(tree_height(node->left), tree_height(node->right));
}

int tree_size(TNODE *node) {
	if (node == NULL)
		return 0;
	else
		return 1 + tree_size(node->left) + tree_size(node->right);
}

TPROPS tree_property(TNODE *root) {

	TPROPS prop;
	prop.order = tree_size(root);
	prop.height = tree_height(root);
	return prop;
}

void preorder(TNODE *root) {

	if (root != NULL) {
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TNODE *root) {

	if (root != NULL) {
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);
	}
}

void postorder(TNODE *root) {

	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%c ", root->data);
	}
}

void bforder(TNODE *root) {

	QUEUE q;
	q.front = q.rear = NULL;
	if (root != NULL) {
		enqueue(&q, root);
		while (q.front != NULL) {
			TNODE *temp = (TNODE*) dequeue(&q);
			printf("%c ", temp->data);
			if (temp->left != NULL)
				enqueue(&q, temp->left);
			if (temp->right != NULL)
				enqueue(&q, temp->right);
		}
	}
	clean_queue(&q);
}

TNODE* bfs(TNODE *root, char val) {

	QUEUE q;
	q.front = q.rear = NULL;
	if (root != NULL) {
		enqueue(&q, root);
		while (q.front != NULL) {
			TNODE *temp = (TNODE*) dequeue(&q);
			if (temp->data == val)
				return temp;
			if (temp->left != NULL)
				enqueue(&q, temp->left);
			if (temp->right != NULL)
				enqueue(&q, temp->right);
		}
	}
	clean_queue(&q);
	return NULL; // If not found
}

TNODE* dfs(TNODE *root, char val) {

	STACK s;
	s.top = NULL;
	if (root != NULL) {
		push(&s, root);
		while (s.top != NULL) {
			TNODE *temp = (TNODE*) pop(&s);
			if (temp->data == val)
				return temp;
			// Note: Push right child first so that left child is processed first
			if (temp->right != NULL)
				push(&s, temp->right);
			if (temp->left != NULL)
				push(&s, temp->left);
		}
	}
	clean_stack(&s);
	return NULL; // If not found
}
// the following functions are given, need to add to your program.

TNODE* new_node(char val) {
	TNODE *np = (TNODE*) malloc(sizeof(TNODE));
	if (np != NULL) {
		np->data = val;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

void clean_tree(TNODE **rootp) {
	TNODE *p = *rootp;
	if (p) {
		if (p->left)
			clean_tree(&p->left);
		if (p->right)
			clean_tree(&p->right);
		free(p);
	}
	*rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
	if (*rootp == NULL) {
		*rootp = new_node(val);
	} else {
		QUEUE queue = { 0 };
		TNODE *p;
		enqueue(&queue, *rootp);
		while (queue.front) {
			p = dequeue(&queue);
			if (p->left == NULL) {
				p->left = new_node(val);
				break;
			} else {
				enqueue(&queue, p->left);
			}

			if (p->right == NULL) {
				p->right = new_node(val);
				break;
			} else {
				enqueue(&queue, p->right);
			}
		}
	}
}
