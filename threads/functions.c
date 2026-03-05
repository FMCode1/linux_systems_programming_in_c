#include "functions.h"
/* FUNCTION: initialize
 * This function should initialize the array
 * to random values 0 (tails) and 1 (heads)
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */
int initialize(int *array, int length)
{
  srand(getpid());
  int i;

  for (i = 0; i < length; i++)
  {
    array[i] = rand() % 2;
  }

  return 0;
}
/* FUNCTION: countHeads
 * This function should find the number of 1s (heads) in the array and
 * return it through the argument numHeads.
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *     numHeads: set to the number of 1s (heads) in the array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */

 // divide to have a different start point for each thread, stop point and each array gets its own and add it on to the total, instead of having to go through the for loop
 // change the number of arguments to match the proper header with a void pointer

void *countHeads(void *arg)
{
  struct ArrayPackage *param = arg;
  int *array = param->array;
  int start = param->start;
  int end = param->end;

  int num_head = 0;
  for (int i = start; i < end; i++)
  {
      num_head += array[i];
  }

  pthread_mutex_lock(&headLock);
  NUM_HEADS += num_head;
  pthread_mutex_unlock(&headLock);

  free(arg);

  return NULL;
}


/*int countHeads(int *array, int length, int *numHeads)
{
  int i;
  *numHeads = 0;
  for (i = 0; i < length; i++)
  {
      *numHeads += arr/ Question 3 a
void *countHeads(void *arg)
{
  void **args = (void **)arg;
  int *array = (int *)args[0];
  int start = *(int *)args[1];
  int end = *(int *)args[2];

  int *start_value = (int *)malloc(sizeof(int));
  *start_value = array[start];

  pthread_mutex_lock(&headLock);
  NUM_HEADS += *start_value;
  pthread_mutex_unlock(&headLock);

  free(args[1]);
  free(args[2]);
  free(args);

  return (void *)start_value;
}
ay[i];
  }

  // update NUM_HEADS
  pthread_mutex_lock(&headLock);
  NUM_HEADS += *numHeads;
  pthread_mutex_unlock(&headLock);

  // ensure to clean up memory for the arguments in main

  return 0;
}
*/

/* FUNCTION: printArray
 * This function should print all the elements of the array
 * and separately counts the number of heads to verify threaded results.
 *
 * The arguments are:
 *     array: pointer to an array of integer values
 *     length: size of array
 *
 * It returns:
 *     0: on success
 *     non-zero: on an error
 */
int printArray(int *array, int length)
{
  int i;
  int checkHeads = 0;
  for (i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
    // add a newline character for readability
    if ((i + 1) % 15 == 0)
    {
      printf("\n");
    }
    checkHeads += array[i];
  }
  printf("\nChecking result: %i\n", checkHeads);
  return 0;
}
