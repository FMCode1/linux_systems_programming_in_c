/* -----------------------------------------------------------
 * PC.c
 *
 * Demonstrates the **Producer-Consumer problem** with semaphores.
 *
 * - Multiple producers and consumers
 * - Bounded buffer
 * - Synchronization using semaphores (full, empty, mutex)
 *
 * Skills demonstrated:
 *   - POSIX threads
 *   - Semaphores for synchronization
 *   - Circular buffer management
 * -----------------------------------------------------------
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 5  // Total slots in buffer
#define NP 3         // Number of producers
#define NC 5         // Number of consumers
#define NITERS 7     // Number of items each producer produces

typedef struct
{
    int buf[BUFF_SIZE];  // Shared buffer
    int in;              // Next empty slot
    int out;             // Next full slot
    sem_t full;          // Number of full slots
    sem_t empty;         // Number of empty slots
    sem_t mutex;         // Protect buffer access
} sbuf_t;

sbuf_t SHARED;

// Producer thread
void *Producer(void *arg)
{
    int i, item, index = *(int *)arg;

    for (i = 0; i < NITERS; i++)
    {
        item = i;               // Produce item
        sem_wait(&SHARED.empty); // Wait for empty slot
        sem_wait(&SHARED.mutex); // Lock buffer
        SHARED.buf[SHARED.in] = item;
        SHARED.in = (SHARED.in + 1) % BUFF_SIZE;
        printf("[P%d] Producing %d\n", index, item);
        fflush(stdout);
        sem_post(&SHARED.mutex); // Unlock buffer
        sem_post(&SHARED.full);  // Increment full slots
    }

    free(arg);
    return NULL;
}

// Consumer thread
void *Consumer(void *arg)
{
    int i, item, index = *(int *)arg;

    for (i = 0; i < NITERS; i++)
    {
        sem_wait(&SHARED.full);  // Wait for full slot
        sem_wait(&SHARED.mutex); // Lock buffer
        item = SHARED.buf[SHARED.out];
        SHARED.out = (SHARED.out + 1) % BUFF_SIZE;
        printf("[C%d] Consuming %d\n", index, item);
        fflush(stdout);
        sem_post(&SHARED.mutex); // Unlock buffer
        sem_post(&SHARED.empty); // Increment empty slots
    }

    free(arg);
    return NULL;
}

int main()
{
    pthread_t *idP = malloc(NP * sizeof(pthread_t));
    pthread_t *idC = malloc(NC * sizeof(pthread_t));
    int index, *arg;

    SHARED.in = SHARED.out = 0;

    // Initialize semaphores
    sem_init(&SHARED.full, 0, 0);
    sem_init(&SHARED.empty, 0, BUFF_SIZE);
    sem_init(&SHARED.mutex, 0, 1);

    // Create producers
    for (index = 0; index < NP; index++)
    {
        arg = malloc(sizeof(int));
        *arg = index;
        pthread_create(&idP[index], NULL, Producer, arg);
    }

    // Create consumers
    for (index = 0; index < NC; index++)
    {
        arg = malloc(sizeof(int));
        *arg = index;
        pthread_create(&idC[index], NULL, Consumer, arg);
    }

    // Join producers
    for (index = 0; index < NP; index++)
        pthread_join(idP[index], NULL);

    // Join consumers
    for (index = 0; index < NC; index++)
        pthread_join(idC[index], NULL);

    // Destroy semaphores
    sem_destroy(&SHARED.full);
    sem_destroy(&SHARED.empty);
    sem_destroy(&SHARED.mutex);

    free(idP);
    free(idC);

    pthread_exit(NULL);
}