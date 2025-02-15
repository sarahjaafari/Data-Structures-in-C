/*
 -------------------------------------
 File:    expression.c
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
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

int precedence(char operator) {
	switch (operator) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

QUEUE infix_to_postfix(char *infixstr) {
	QUEUE queue = { 0 };
	STACK stack = { 0 };

	for (char *p = infixstr; *p; p++) {
		if (isdigit(*p)) {
			int num = 0;
			while (isdigit(*p)) {
				num = num * 10 + (*p - '0');
				p++;
			}
			p--;  // Step back after the last digit
			enqueue(&queue, new_node(num, 0));
		} else if (*p == '(') {
			push(&stack, new_node(*p, 1));
		} else if (*p == ')') {
			while (stack.top && stack.top->data != '(') {
				enqueue(&queue, pop(&stack));
			}
			pop(&stack);  // Pop the '('
		} else {  // Operator
			while (stack.top && precedence(stack.top->data) >= precedence(*p)) {
				enqueue(&queue, pop(&stack));
			}
			push(&stack, new_node(*p, 1));
		}
	}

	while (stack.top) {
		enqueue(&queue, pop(&stack));
	}

	return queue;
}

int evaluate_postfix(QUEUE queue) {
	STACK stack = { 0 };

	while (queue.front) {
		NODE *node = dequeue(&queue);
		if (node->type == 0) {  // Operand
			push(&stack, node);
		} else {  // Operator
			int right = pop(&stack)->data;
			int left = pop(&stack)->data;
			switch (node->data) {
			case '+':
				push(&stack, new_node(left + right, 0));
				break;
			case '-':
				push(&stack, new_node(left - right, 0));
				break;
			case '*':
				push(&stack, new_node(left * right, 0));
				break;
			case '/':
				push(&stack, new_node(left / right, 0));
				break;
			}
			free(node);
		}
	}

	int result = pop(&stack)->data;
	clean_stack(&stack);
	return result;
}

int evaluate_infix(char *infixstr) {
	QUEUE postfix = infix_to_postfix(infixstr);
	int result = evaluate_postfix(postfix);
	clean_queue(&postfix);
	return result;
}
