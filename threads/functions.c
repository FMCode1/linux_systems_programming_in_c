#include "functions.h"

/* FUNCTION: initialize
 * Fills an integer array with random values 0 (tails) and 1 (heads)
 *
 * Arguments:
 *     array  - pointer to an integer array
 *     length - size of the array
 *
 * Returns:
 *     0 on success, non-zero on error
 */
int initialize(int *array, int length)
{
    srand(getpid()); // seed random number generator with process id for variability
    int i;

    for (i = 0; i < length; i++)
    {
        array[i] = rand() % 2; // generate 0 or 1
    }

    return 0;
}

/* FUNCTION: countHeads
 * Threaded function to count the number of heads (1s) in a section of the array.
 *
 * Arguments:
 *     arg - pointer to a struct ArrayPackage containing array, start index, end index
 *
 * Returns:
 *     NULL (result is stored in global NUM_HEADS)
 */
void *countHeads(void *arg)
{
    struct ArrayPackage *param = arg;
    int *array = param->array;
    int start = param->start;
    int end = param->end;

    int num_head = 0;
    // Count the number of 1s (heads) in this segment of the array
    for (int i = start; i < end; i++)
    {
        num_head += array[i];
    }

    // Safely update global NUM_HEADS using mutex lock
    pthread_mutex_lock(&headLock);
    NUM_HEADS += num_head;
    pthread_mutex_unlock(&headLock);

    free(arg); // free the memory allocated for this thread's arguments

    return NULL;
}

/* FUNCTION: printArray
 * Prints the contents of an array and checks the number of heads
 *
 * Arguments:
 *     array  - pointer to an integer array
 *     length - size of the array
 *
 * Returns:
 *     0 on success, non-zero on error
 */
int printArray(int *array, int length)
{
    int i;
    int checkHeads = 0;

    for (i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
        // Add a newline after every 15 elements for readability
        if ((i + 1) % 15 == 0)
        {
            printf("\n");
        }
        checkHeads += array[i]; // count heads in array
    }

    printf("\nChecking result: %i\n", checkHeads);
    return 0;
}

// Thread function to count heads in a portion of the array
void *threadFunction(void *arg)
{
    struct ArrayPackage *param = (struct ArrayPackage *)arg;
    int *array = param->array;
    int start = param->start;
    int end = param->end;

    int count = 0;
    for (int i = start; i < end; i++)
        count += array[i];

    // Update global NUM_HEADS safely
    pthread_mutex_lock(&headLock);
    NUM_HEADS += count;
    pthread_mutex_unlock(&headLock);

    // Return the local count for main to print
    int *result = (int *)malloc(sizeof(int));
    *result = count;

    free(param);  // free the package, main will free the result
    return (void *)result;
}