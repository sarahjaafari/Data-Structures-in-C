/*
 -------------------------------------
 File:    myword.c
 Project: a03
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-03
 -------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "myword.h"
#include "mystring.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

// You can copy here the functions in mysttring.c if you want to use them in the
// following functions. You can also add other auxiliary functions here.

/*
 * Load word data from file, and insert words a directory represented by char array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored.
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */
int create_dictionary(FILE *fp, char *dictionary) {
	char line[MAX_LINE_LEN];
	int count = 0;
	dictionary[0] = '\0';
	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		char *token = strtok(line, ",\n");
		while (token != NULL) {
			for (int i = 0; token[i]; i++) {
				token[i] = tolower(token[i]);
			}
			strcat(dictionary, token);
			strcat(dictionary, ",");
			token = strtok(NULL, ",\n");
			count++;
		}
	}
	return count;
}

/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */
BOOLEAN contain_word(char *dictionary, char *word) {
	char temp[25] = ",";
	strcat(temp, word);
	strcat(temp, ",");
	if (strstr(dictionary, temp) != NULL) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
	WORDSTATS ws = { 0 };
	char line[MAX_LINE_LEN];
	char *word_token;

	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		ws.line_count++;
		str_lower(line);
		word_token = strtok(line, " ,.;!\n");
		while (word_token != NULL) {
			ws.word_count++;

			if (!contain_word(dictionary, word_token)) {
				int j = 0;
				while (j < ws.keyword_count
						&& strcmp(word_token, words[j].word) != 0) {
					j++;
				}
				if (j < ws.keyword_count) {
					words[j].count++;
				} else {
					strcpy(words[ws.keyword_count].word, word_token);
					words[ws.keyword_count].count = 1;
					ws.keyword_count++;
				}
			}
			word_token = strtok(NULL, " ,.;!\n");
		}
	}

	return ws;
}
