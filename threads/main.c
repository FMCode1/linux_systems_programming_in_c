#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int NUM_HEADS = 0; /*Used when you implement the thread function */
pthread_mutex_t headLock;

int main(int argc, char *argv[])
{
  int *array;
  struct ArrayPackage onePackage;
  int size = 0;
  int numHeads = 0;
  int numThreads;
  int increments;
  pthread_t *threadIds;
  void *pStatus;

  if (pthread_mutex_init(&headLock, NULL) != 0)
  {
    perror("Could not create mutex for numHeads: ");
    return 1;
  }
  printf("How many threads? ");
  scanf("%d", &numThreads);
  threadIds = (pthread_t *)malloc(sizeof(pthread_t *) * numThreads);

  do
  {
    printf("How big is the array (100 elements or more)?");
    scanf("%i", &size);        return 1; //
  } while (size < 100);
  array = (int *)malloc(sizeof(int) * size);

  increments = size / numThreads; //10/3 -> 3r1 0123456789

  if (initialize(array, size) != 0)
  {
    printf("initialization error\n");
    exit(1);
  }

  printArray(array, size);

  for (int i = 0; i < numThreads; i++)
  {
    struct ArrayPackage *onePack = (struct ArrayPackage *)malloc(sizeof(struct ArrayPackage));
    /*-------------------------------------------------------------------*/
    /* Store the array, the start, and the end into the onePack instance */
    onePack->array = array;
    onePack->start = i * increments; // always increment away from previous
    onePack->end = (i == numThreads - 1) ? size : (i + 1) * increments; // increment more than start, for the last thread, the end index will be the size of the array

    /*---------------------------------------------------------------------*/
    /* Call the pthread_create */

    // check if thread creation is successful
    // pthread_create( pointer to pthread_t to dtore id's, default attributes, routine function, arguments to the function)
    if (pthread_create(&threadIds[i], NULL, threadFunction, (void *)onePack) != 0)
    {
      perror("Could not create thread: ");
      return 1;
    }    
  }
  
  for (int i = 0; i < numThreads; i++)
  {
    /*---------------------------------------------------------------------*/
    /*Call the join added */
    
    if (pthread_join(threadIds[i], &pStatus) != 0)
    {
      perror("Could not join thread: ");
      return 1;
    } 
     int *result = (int *)pStatus; 
    printf("Thread %d returned value at start index: %d\n", i, *result);
    free(result);    
  }
  /*-----------------------------------------------------------------------*/
  /* The following call to countHeads will be taken out when you implement the thread function*/
    



  /*-----------------------------------------------------------------------*/
  /* The following line will have to be changed */
  pthread_mutex_lock(&headLock);
  printf("The number of heads coin tosses is: %i\n", NUM_HEADS);
  pthread_mutex_unlock(&headLock);
  
  free(array);
  free(threadIds);

  // Free up unneded mutexes
  pthread_mutex_destroy(&headLock);

  return 0;
}