/*
 -------------------------------------
 File:    mysort.c
 Project: a04
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-02-10
 -------------------------------------
 */
#include "mysort.h"

void swap(float **a, float **b);
int partition(float *a[], int left, int right);

void select_sort_inc(float *a[], int left, int right) {

	int i, j, min_idx;
	float *temp;
	for (i = left; i < right; i++) {
		min_idx = i;
		for (j = i + 1; j <= right; j++)
			if (*a[j] < *a[min_idx])
				min_idx = j;

		if (min_idx != i) {
			// Swapping the pointers
			temp = a[i];
			a[i] = a[min_idx];
			a[min_idx] = temp;
		}
	}
}

void quick_sort_inc(float *a[], int left, int right) {

	if (left < right) {
		// Partitioning index
		int pi = partition(a, left, right);

		quick_sort_inc(a, left, pi - 1);  // Before pi
		quick_sort_inc(a, pi + 1, right); // After pi
	}
}

int partition(float *a[], int left, int right) {
	float *pivot = a[right]; // pivot
	int i = (left - 1); // Index of smaller element

	for (int j = left; j <= right - 1; j++) {
		// If current element is smaller than or equal to pivot
		if (*a[j] <= *pivot) {
			i++; // increment index of smaller element
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[right]);
	return (i + 1);
}

void swap(float **a, float **b) {
	float *temp = *a;
	*a = *b;
	*b = temp;

}
