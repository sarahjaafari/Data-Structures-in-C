/*
 -------------------------------------
 File:    mychar.c
 Project: alja4425_a01
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-01-20
 -------------------------------------
 */

#include <mychar.h>
#include <stdio.h>

int mytype(char c) {
	int r = -1; // default return value for characters that don't match any category

	if (c >= '0' && c <= '9') {
		r = 0; // Character is a digit
	} else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		r = 2; // Character is an English letter
	} else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
		r = 1; // Character is an arithmetic operator
	}

	return r; // Return the result
}

char case_flip(char c) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a' + 'A';
	} else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 'a';
	} else {
		return c; // unchanged if not an English letter
	}
}

int char_to_int(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else {
		return -1; // not a digit
	}
}
