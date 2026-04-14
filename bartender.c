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
	//So this is a weird one, but the behavior of the bartender doesn't change
	//until the customer places an order, so we can just wait for the customerReady 
	//semaphore to be posted (this is what this is representing)

	//wait for customer to order drink
	sem_wait(customerReady);

}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 * TODO - SYNCHRONIZE ME
 */
void makeDrink() {
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
	//get a random time between 5 ms and 1000 ms
	unsigned int makeTime = 5 + (rand() % 996);
	//sleep for that time (usleep takes microseconds, so multiply by 1000
	usleep(makeTime * 1000);
	
	//after making the drink, post to the bartenderReady semaphore to let the customer know
	sem_post(bartenderReady);

	//no need to wait for the customer to finish looking at art, the bartender
	//can do that while waiting for the customer to pay
}

/**
 * Gets payment from the correct customer
 * TODO - SYNCHRONIZE ME
 */
void receivePayment() {
	// at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");

	//wait for the customer to pay at the register
	sem_wait(customerReady);

	// got paid by the customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");

	//confirm payment is recieved so the customer can leave
	sem_post(bartenderReady);
}