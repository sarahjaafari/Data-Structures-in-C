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
#include <stdio.h>
#include <math.h>
#include "polynomial.h"

#define EPSILON 1e-6

/**
 *  computes and returns the value of the following polynomial
 *  p(x) of order n and coefficients p[0], …, p[n-1]
 */
float horner(float *p, int n, float x) {
	float result = p[0];
	for (int i = 1; i < n; i++) {
		result = result * x + p[i];
	}
	return result;
}

/**
 *  finds an approximate real root c in interval [a, b] of
 *  polynomial P(x), using the bisection method
 */
float bisection(float *p, int n, float a, float b) {
	const float TOLERANCE = 1e-6;
	float c;

	while ((b - a) >= TOLERANCE) {
		c = (a + b) / 2;
		if (horner(p, n, c) == 0.0)
			break;
		else if (horner(p, n, c) * horner(p, n, a) < 0)
			b = c;
		else
			a = c;
	}
	return c;
}
