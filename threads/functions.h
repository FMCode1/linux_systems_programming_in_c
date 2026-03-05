#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct ArrayPackage
{
  int *array;
  int start; 
  int end;  
};

extern int NUM_HEADS;
extern pthread_mutex_t headLock;

int initialize(int *array, int length);
void *countHeads(void *arg);
// int countHeads(int *array, int length, int *numHeads);
int printArray(int *array, int length);
void *threadFunction(void *arg); // Add this line

#endif
