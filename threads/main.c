#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int NUM_HEADS = 0; /* global variable used to accumulate results from threads */
pthread_mutex_t headLock; /* mutex for safe NUM_HEADS updates */

int main(int argc, char *argv[])
{
    int *array;
    struct ArrayPackage onePackage;
    int size = 0;
    int numThreads;
    int increments;
    pthread_t *threadIds;
    void *pStatus;

    // Initialize mutex
    if (pthread_mutex_init(&headLock, NULL) != 0)
    {
        perror("Could not create mutex for NUM_HEADS");
        return 1;
    }

    // Ask user how many threads to create
    printf("How many threads? ");
    scanf("%d", &numThreads);
    threadIds = (pthread_t *)malloc(sizeof(pthread_t) * numThreads);

    // Ask user for array size (must be 100 or more)
    do
    {
        printf("How big is the array (100 elements or more)? ");
        scanf("%i", &size);
    } while (size < 100);

    array = (int *)malloc(sizeof(int) * size);

    // Determine how many elements each thread will handle
    increments = size / numThreads;

    // Initialize array with random 0s and 1s
    if (initialize(array, size) != 0)
    {
        printf("Initialization error\n");
        exit(1);
    }

    // Print array contents for verification
    printArray(array, size);

    // Create threads
    for (int i = 0; i < numThreads; i++)
    {
        struct ArrayPackage *onePack = (struct ArrayPackage *)malloc(sizeof(struct ArrayPackage));

        // Assign array segment for each thread
        onePack->array = array;
        onePack->start = i * increments;
        onePack->end = (i == numThreads - 1) ? size : (i + 1) * increments;

        // Create thread and run threadFunction
        if (pthread_create(&threadIds[i], NULL, threadFunction, (void *)onePack) != 0)
        {
            perror("Could not create thread");
            return 1;
        }
    }

    // Wait for threads to complete
    for (int i = 0; i < numThreads; i++)
    {
        if (pthread_join(threadIds[i], &pStatus) != 0)
        {
            perror("Could not join thread");
            return 1;
        }

        int *result = (int *)pStatus;
        printf("Thread %d returned value at start index: %d\n", i, *result);
        free(result);    
    }

    // Display final number of heads (safe with mutex)
    pthread_mutex_lock(&headLock);
    printf("The number of heads coin tosses is: %i\n", NUM_HEADS);
    pthread_mutex_unlock(&headLock);

    free(array);
    free(threadIds);

    // Destroy mutex
    pthread_mutex_destroy(&headLock);

    return 0;
}