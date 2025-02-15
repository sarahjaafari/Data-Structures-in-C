/*
 -------------------------------------
 File:    mymortgage.c
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
#include <math.h>
#include <mymortgage.h>

float monthly_payment(float principal_amount, float annual_interest_rate,
		int years) {
	float monthly_rate = annual_interest_rate / 100 / 12; // Convert to monthly and decimal rate
	int total_payments = years * 12;

	// The formula for monthly mortgage payment
	float payment = (principal_amount * monthly_rate)
			/ (1 - pow(1 + monthly_rate, -total_payments));

	return payment;
}

float total_payment(float principal_amount, float annual_interest_rate,
		int years) {
	float monthly_payment_amount = monthly_payment(principal_amount,
			annual_interest_rate, years);
	return monthly_payment_amount * years * 12;
}

float total_interest(float principal_amount, float annual_interest_rate,
		int years) {
	float total_payment_amount = total_payment(principal_amount,
			annual_interest_rate, years);
	return total_payment_amount - (principal_amount);
}
