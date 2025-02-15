/*
 -------------------------------------
 File:    myrecord.c
 Project: a04
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-10
 -------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
	GRADE r = { "F" };
	if (score >= 90)
		strcpy(r.letter_grade, score <= 100 ? "A+" : "A");
	else if (score >= 85)
		strcpy(r.letter_grade, "A");
	else if (score >= 80)
		strcpy(r.letter_grade, "A-");
	else if (score >= 77)
		strcpy(r.letter_grade, "B+");
	else if (score >= 73)
		strcpy(r.letter_grade, "B");
	else if (score >= 70)
		strcpy(r.letter_grade, "B-");
	else if (score >= 67)
		strcpy(r.letter_grade, "C+");
	else if (score >= 63)
		strcpy(r.letter_grade, "C");
	else if (score >= 60)
		strcpy(r.letter_grade, "C-");
	else if (score >= 57)
		strcpy(r.letter_grade, "D+");
	else if (score >= 53)
		strcpy(r.letter_grade, "D");
	else if (score >= 50)
		strcpy(r.letter_grade, "D-");
	return r;
}

STATS process_data(RECORD *dataset, int count) {
	STATS stats;
	float sum = 0.0, sum_sq_diff = 0.0, mean, stddev, median;
	float *scores = (float*) malloc(count * sizeof(float));

	for (int i = 0; i < count; i++) {
		scores[i] = dataset[i].score;
		sum += scores[i];
	}
	mean = sum / count;

	for (int i = 0; i < count; i++) {
		sum_sq_diff += pow(scores[i] - mean, 2);
	}
	stddev = sqrt(sum_sq_diff / count);

	// Sort scores to find the median
	float *ptrs[count];
	for (int i = 0; i < count; i++)
		ptrs[i] = &scores[i];
	quick_sort_inc(ptrs, 0, count - 1);

	if (count % 2 == 0) {
		median = (*(ptrs[count / 2 - 1]) + *(ptrs[count / 2])) / 2.0;
	} else {
		median = *(ptrs[count / 2]);
	}

	free(scores);

	stats.count = count;
	stats.mean = mean;
	stats.stddev = stddev;
	stats.median = median;

	return stats;
}

int import_data(FILE *fp, RECORD *dataset) {
	int count = 0;
	while (fscanf(fp, "%20[^,],%f\n", dataset[count].name,
			&dataset[count].score) != EOF) {
		count++;
	}
	return count;
}

int report_data(FILE *fp, RECORD *dataset, int count) {
	if (count < 1)
		return 0;
	for (int i = 0; i < count; i++) {
		GRADE g = grade(dataset[i].score);
		fprintf(fp, "%s,%.1f,%s\n", dataset[i].name, dataset[i].score,
				g.letter_grade);
	}
	return 1;
}
