/*
 -------------------------------------
 File:    factorial.c
 Project: alja4425_a01
 file description
 -------------------------------------
 Author:  Sara Aljaafari
 ID:      169044425
 Email:   alja4425@mylaurier.ca
 Version  2024-01-20
 -------------------------------------
 */
#include <stdio.h>
#include <factorial.h>

int factorial(int n) {
	int f = 1;

	if (n >= 1) {
		for (int i = 1; i <= n; ++i) {
			int temp = f;
			f = f * i;
			// Overflow detection
			if (f / i != temp) {
				return 0; // overflow occurred
			}
		}
	}

	return f; // if no overflow, return the factorial
}
