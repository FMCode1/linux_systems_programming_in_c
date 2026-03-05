/* -----------------------------------------------------------
 * badcnt.c
 *
 * Demonstrates a **race condition** using two threads incrementing
 * a shared global counter without synchronization.
 *
 * Skills demonstrated:
 *   - pthread creation and joining
 *   - Race conditions in multithreading
 *   - Understanding need for mutexes/semaphores
 * -----------------------------------------------------------
 */

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int CNT = 0; // Global counter (shared between threads)

// Thread function: increments CNT NITER times without synchronization
void *counterFunct(void *a)
{
    int i, tmp;
    for (i = 0; i < NITER; i++)
    {
        tmp = CNT;     // copy the global CNT locally
        tmp = tmp + 1; // increment the local copy
        CNT = tmp;     // write back (race condition!)
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tId1, tId2;

    // Create two threads
    if (pthread_create(&tId1, NULL, counterFunct, NULL))
    {
        perror("ERROR creating thread 1");
        exit(1);
    }
    if (pthread_create(&tId2, NULL, counterFunct, NULL))
    {
        perror("ERROR creating thread 2");
        exit(1);
    }

    // Wait for both threads to finish
    if (pthread_join(tId1, NULL) || pthread_join(tId2, NULL))
    {
        perror("ERROR joining thread");
        exit(1);
    }

    // Check result
    if (CNT < 2 * NITER)
        printf("BOOM! CNT is [%d], should be %d\n", CNT, 2 * NITER);
    else
        printf("OK! CNT is [%d]\n", CNT);

    pthread_exit(NULL);
}