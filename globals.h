/*
 * globals.h
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

// number of customer threads
extern int num_threads;

// TODO - declare some semaphores
extern sem_t* barstool;
extern sem_t* customerReady;
extern sem_t* bartenderReady;


#endif /* GLOBALS_H_ */
