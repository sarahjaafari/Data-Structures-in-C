/*
 -------------------------------------
 File:    polynomial.c
 Project: alja4425_a02
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-01-27
 -------------------------------------
 */

#include "matrix.h"
#include <math.h>

/**
 * Compute and return the norm of vector v, namely, the square root of the sum of
 * squares of elements of v.
 */
float norm(float *v, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += v[i] * v[i];
	}
	return sqrt(sum);
}

/**
 * Compute and return the dot product of vectors v1[n] and v2[n],
 * namely the sum of product of corresponding elements of v1 and v2.
 */
float dot_product(float *v1, float *v2, int n) {
	float sum = 0;
	for (int i = 0; i < n; i++) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

/**
 * Compute the multiplication of matrix and vector.
 */
void matrix_multiply_vector(float *m, float *v, float *vout, int n) {
	for (int i = 0; i < n; i++) {
		vout[i] = 0;
		for (int j = 0; j < n; j++) {
			vout[i] += m[i * n + j] * v[j];
		}
	}
}

/**
 * Compute the multiplication of two n by matrices.
 */
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m3[i * n + j] = 0;
			for (int k = 0; k < n; k++) {
				m3[i * n + j] += m1[i * n + k] * m2[k * n + j];
			}
		}
	}
}
