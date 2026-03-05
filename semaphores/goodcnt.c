/* -----------------------------------------------------------
 * goodcnt.c
 *
 * Demonstrates a **thread-safe counter** using two threads
 * and a semaphore for synchronization.
 *
 * Skills demonstrated:
 *   - pthread creation and joining
 *   - Using POSIX semaphores to prevent race conditions
 *   - Correct shared memory access in multithreading
 * -----------------------------------------------------------
 */

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int CNT = 0;      // Global counter
sem_t mutex;      // Semaphore for synchronizing access

// Thread function: increments CNT NITER times safely
void *counterFunct(void *a)
{
    int i, tmp;
    for (i = 0; i < NITER; i++)
    {
        sem_wait(&mutex); // Lock semaphore
        tmp = CNT;
        tmp = tmp + 1;
        CNT = tmp;
        sem_post(&mutex); // Unlock semaphore
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tId1, tId2;

    // Initialize semaphore as binary
    if (sem_init(&mutex, 0, 1) != 0)
    {
        perror("Semaphore init failed");
        exit(1);
    }

    // Create threads
    if (pthread_create(&tId1, NULL, counterFunct, NULL) ||
        pthread_create(&tId2, NULL, counterFunct, NULL))
    {
        perror("ERROR creating threads");
        exit(1);
    }

    // Wait for threads
    if (pthread_join(tId1, NULL) || pthread_join(tId2, NULL))
    {
        perror("ERROR joining threads");
        exit(1);
    }

    // Check result
    if (CNT < 2 * NITER)
        printf("BOOM! CNT is [%d], should be %d\n", CNT, 2 * NITER);
    else
        printf("OK! CNT is [%d]\n", CNT);

    // Clean up semaphore
    sem_destroy(&mutex);
    pthread_exit(NULL);
}