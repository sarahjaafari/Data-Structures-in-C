/*
 -------------------------------------
 File:    expression_symbol.c
 Project: a09
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-03-23
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_queue_stack.h"
#include "expression_symbol.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
	QUEUE queue = { 0 };
	STACK stack = { 0 };
	char *p = infixstr;
	int sign = 1;
	int num = 0;
	char symbol[11] = { 0 };

	while (*p) {
		if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
			sign = -1;
		} else if (*p >= '0' && *p <= '9') {
			num = *p - '0';
			while ((*(p + 1) >= '0' && *(p + 1) <= '9')) {
				num = num * 10 + *(p + 1) - '0';
				p++;
			}
			enqueue(&queue, new_node(sign * num, 0));
			sign = 1;
		} else if (*p == '(') {
			push(&stack, new_node('(', 2));
		} else if (*p == ')') {
			while (stack.top) {
				if (stack.top->type == 2) {
					free(pop(&stack));
					break;
				}
				enqueue(&queue, pop(&stack));
			}
		} else if (*p == '/' || *p == '*' || *p == '%' || *p == '+'
				|| *p == '-') {
			while (stack.top && stack.top->type == 1
					&& get_priority(stack.top->data) >= get_priority(*p))
				enqueue(&queue, pop(&stack));
			push(&stack, new_node(*p, 1));
		} else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			char *sp = symbol;
			*sp = *p;
			while ((*(p + 1) >= 'a' && *(p + 1) <= 'z')
					|| (*(p + 1) >= 'A' && *(p + 1) <= 'Z')
					|| (*(p + 1) >= '0' && *(p + 1) <= '9')) {
				p++;
				sp++;
				*sp = *p;
			}
			*(sp + 1) = '\0';

			// your code, get the value of the symobol from the hash table, then enqueue the value
			HASHNODE *symbolNode = hashtable_search(ht, symbol);
			if (symbolNode != NULL) {
				enqueue(&queue, new_node(symbolNode->value, 0));
			} else {
				printf("Error: Symbol '%s' not found in hashtable.\n", symbol);
			}
		}
		p++;
	}

	while (stack.top) {
		enqueue(&queue, pop(&stack));
	}

	return queue;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
	QUEUE postfixQueue = infix_to_postfix_symbol(ht, infixstr);
	return evaluate_postfix(postfixQueue);
}

int evaluate_postfix(QUEUE queue) {
	STACK stack = { 0 };

	int type = 0;
	NODE *p = queue.front;

	while (p) {
		type = p->type;

		if (type == 0) {
			push(&stack, new_node(p->data, 0));
		} else if (type == 1) {
			int operator = p->data;
			NODE *oprand2 = pop(&stack);

			if (operator == '+')
				stack.top->data = stack.top->data + oprand2->data;
			else if (operator == '-')
				stack.top->data = stack.top->data - oprand2->data;
			else if (operator == '*')
				stack.top->data = stack.top->data * oprand2->data;
			else if (operator == '/')
				stack.top->data = stack.top->data / oprand2->data;

			free(oprand2);
		}
		p = p->next;
	}

	int result = stack.top->data;
	clean_stack(&stack);
	return result;
}

HASHDATA evaluate_statement(HASHTABLE *ht, char *statement) {
	HASHDATA hd = { 0 };
	char line[80] = { 0 };
	strcpy(line, statement);
	char *p = line, *dp = line;
	while (*p) {
		if (*p != ' ') {
			*dp = *p;
			dp++;
		}
		p++;
	}
	char name[20] = { 0 };
	char *eqp = strstr(line, "=");
	if (eqp) {
		//*eqp='\0'; strcpy(name, line);
		for (p = line, dp = name; p != eqp; p++)
			*dp = *p;
		if ((name[0] >= 'a' && name[0] <= 'z')
				|| (name[0] >= 'A' && name[0] <= 'Z')) {
			int value = evaluate_infix_symbol(ht, eqp + 1);
			hashtable_insert(ht, name, value);
			strcpy(hd.key, name);
			hd.value = value;
		}
	} else {
		strcpy(name, line);
		if ((name[0] >= 'a' && name[0] <= 'z')
				|| (name[0] >= 'A' && name[0] <= 'Z')) {
			HASHNODE *hnp = hashtable_search(ht, name);
			if (hnp) {
				strcpy(hd.key, name);
				hd.value = hnp->value;
			}
		}
	}
	return hd;
}

