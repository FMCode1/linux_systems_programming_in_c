#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Package of arguments for each thread */
struct ArrayPackage
{
    int *array; // pointer to the array
    int start;  // start index for this thread
    int end;    // end index for this thread
};

extern int NUM_HEADS;            // global variable to hold total number of heads
extern pthread_mutex_t headLock; // mutex to safely update NUM_HEADS

// Function declarations
int initialize(int *array, int length);
void *countHeads(void *arg);
// int countHeads(int *array, int length, int *numHeads); // non-threaded version
int printArray(int *array, int length);
void *threadFunction(void *arg); // function pointer for pthread_create

#endif