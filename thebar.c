/*
 * thebar.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"
#include "globals.h"

void printBanner();
void init();
void cleanup();

int num_threads;

sem_t* barstool;
sem_t* customerReady;
sem_t* bartenderReady;

/**
 * Main function
 */
int main(int argc, char *argv[]) {
	// TODO - read the command-line argument into the `num_threads` global (already declared)
	num_threads = atoi(argv[1]);

	printBanner();
	init(); // initialize semaphores

	pthread_t custThreads[num_threads];  // Array to store thread IDs
	pthread_t bartenderThread;

	unsigned int* custIDs[num_threads];  // save pointers
	for (int i = 0; i < num_threads; i++) {
		custIDs[i] = malloc(sizeof(unsigned int));
		*custIDs[i] = i + 1;
		pthread_create(&custThreads[i], NULL, customer, custIDs[i]);
	}

	// Create bartender thread
	pthread_create(&bartenderThread, NULL, bartender, NULL);

	// Wait for bartender thread
	pthread_join(bartenderThread, NULL);

	for (int i = 0; i < num_threads; i++) {
    pthread_join(custThreads[i], NULL);
    free(custIDs[i]);  // safe to free after thread has finished
	}

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner() {
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init() {

	// Force-unlink any leftover semaphores from previous runs
    sem_unlink("/aabrams_barstool");
    sem_unlink("/aabrams_customerReady");
    sem_unlink("/aabrams_bartenderReady");

    barstool = sem_open("/aabrams_barstool", O_CREAT, 0600, 1);
    if (barstool == SEM_FAILED) { perror("barstool"); exit(1); }
    
    customerReady = sem_open("/aabrams_customerReady", O_CREAT, 0600, 0);
    if (customerReady == SEM_FAILED) { perror("customerReady"); exit(1); }
    
    bartenderReady = sem_open("/aabrams_bartenderReady", O_CREAT, 0600, 0);
    if (bartenderReady == SEM_FAILED) { perror("bartenderReady"); exit(1); }
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup() {
	// TODO - close and destroy semaphores

	sem_close(barstool);
	sem_unlink("/aabrams_barstool");
	sem_close(customerReady);
	sem_unlink("/aabrams_customerReady");
	sem_close(bartenderReady);
	sem_unlink("/aabrams_bartenderReady");
}
