/*
 -------------------------------------
 File:    mystring.c
 Project: a03
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-03
 -------------------------------------
 */

#include "mystring.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a str
 * @return - return the number of words.
 */
int str_words(char *s) {
	int count = 0;
	int in_word = 0;

	while (*s) {
		if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) {
			if (!in_word) {
				in_word = 1;
				count++;
			}
		} else {
			in_word = 0;
		}
		s++;
	}

	return count;
}

/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a str
 * @return - return the number of actual flips.
 */
int str_lower(char *s) {
	int flips = 0;

	while (*s) {
		if (*s >= 'A' && *s <= 'Z') {
			*s += 32;
			flips++;
		}
		s++;
	}

	return flips;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a str
 */
void str_trim(char *s) {
	char *d = s;
	int space_found = 0;

	while (*s) {
		if (*s != ' ' || (d != s && !space_found)) {
			if (*s == ' ') {
				space_found = 1;
			} else {
				space_found = 0;
			}
			*d++ = *s;
		}
		s++;
	}

	if (*(d - 1) == ' ') {
		*(d - 1) = '\0';
	} else {
		*d = '\0';
	}
}
