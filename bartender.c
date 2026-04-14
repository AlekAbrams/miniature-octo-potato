/*
 * bartender.c
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void *bartender(void *args) {
	for (int i = 0; i < num_threads; i++) {
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 * TODO - SYNCHRONIZE ME
 */
void waitForCustomer() {
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 * TODO - SYNCHRONIZE ME
 */
void makeDrink() {
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
}

/**
 * Gets payment from the correct customer
 * TODO - SYNCHRONIZE ME
 */
void receivePayment() {
	// at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	// got paid by the customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
}