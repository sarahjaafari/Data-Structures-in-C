/*
 -------------------------------------
 File:    fibonacci.c
 Project: alja4425_a02
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-01-27
 -------------------------------------
 */

#include "fibonacci.h"

/**
 *  computes and returns the nth Fibonacci number F(n) using
 *  recursive algorithm, namely using recursion function.
 */
int recursive_fibonacci(int n) {
	if (n <= 1)
		return n;
	int a = 0, b = 1, c, i;
	for (i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

/**
 *  computes and returns the nth Fibonacci number F(n) using
 *  iterative algorithm, namely using a for or while loop.
 */
int iterative_fibonacci(int n) {
	if (n <= 1)
		return n;
	int a = 0, b = 1, c, i;
	for (i = 2; i <= n; i++) {
		c = a + b;
		a = b;
		b = c;
	}
	return b;
}

/**
 *  computes and returns the nth Fibonacci number F(n) using using
 *  dynamic programming bottom-up method with external array f[n+1]
 *  of initial value -1 for all elements.
 */
int dpbu_fibonacci(int *f, int n) {
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	return f[n];
}

/**
 *  computes and returns the Fibonacci number F(n) using dynamic
 *  programming top-down method with external array f[n+1] of
 *  initial value -1 for all elements.
 */
int dptd_fibonacci(int *f, int n) {
	if (f[n] != -1)
		return f[n];
	if (n <= 1)
		return f[n] = n;
	f[n] = dptd_fibonacci(f, n - 1) + dptd_fibonacci(f, n - 2);
	return f[n];
}
