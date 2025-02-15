/*
 -------------------------------------
 File:    myword.h
 Project: a03
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-03
 -------------------------------------
 */
#ifndef MYWORD_H_
#define MYWORD_H_
#include <stdio.h>

#define MAX_WORD 30
#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

typedef enum boolean {
	FALSE = 0, TRUE = 1
} BOOLEAN;

typedef struct word {
	char word[MAX_WORD];
	int count;
} WORD;

typedef struct wordstats {
	WORD word_array[MAX_WORDS];
	int line_count;
	int word_count;
	int keyword_count;
} WORDSTATS;

int create_dictionary(FILE *fp, char *dictrionay);

BOOLEAN contain_word(char *dictionary, char *word);

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary);

#endif /* MYWORD_H_ */
