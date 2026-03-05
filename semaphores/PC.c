#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 5 /* total number of slots */
#define NP 3        /* total number of producers */
// #define NC 3        /* total number of consumers */
#define NC 5        /* total number of consumers */

// #define NITERS 4    /* number of items produced/consumed */
#define NITERS 7    /* number of items produced/consumed */

typedef struct
{
  int buf[BUFF_SIZE]; /* shared var */
  int in;             /* buf[in%BUFF_SIZE] is the first empty slot */
  int out;            /* buf[out%BUFF_SIZE] is the first full slot */
  sem_t full;         /* keep track of the number of full spots */
  sem_t empty;        /* keep track of the number of empty spots */
  sem_t mutex;        /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t SHARED;

void *Producer(void *arg)
{
  int i, item, index;

  index = *(int *)arg;

  for (i = 0; i < NITERS; i++)
  {

    /* Produce item */
    item = i;

    /* Prepare to write item to buf */

    /* If there are no empty slots, wait */
    sem_wait(&SHARED.empty);
    /* If another thread uses the buffer, wait */
    sem_wait(&SHARED.mutex);
    SHARED.buf[SHARED.in] = item;
    SHARED.in = (SHARED.in + 1) % BUFF_SIZE;
    printf("[P%d] Producing %d ...\n", index, item);
    fflush(stdout);
    /* Release the buffer */
    sem_post(&SHARED.mutex);
    /* Increment the number of full slots */
    sem_post(&SHARED.full);
  }
  free(arg);
  return NULL;
}

void *Consumer(void *arg)
{
  /* ----Fill in the code here */ 
  
  int i, item, index;

  index = *(int *)arg;

  for (i = 0; i < NITERS; i++)
  {
    /* Wait if there are no full slots */
    sem_wait(&SHARED.full);
    /* Wait for exclusive access to the buffer */
    sem_wait(&SHARED.mutex);

    /* Consume item */
    item = SHARED.buf[SHARED.out];
    SHARED.out = (SHARED.out + 1) % BUFF_SIZE;
    printf("[C%d] Consuming %d ...\n", index, item);
    fflush(stdout);

    /* Release the buffer */
    sem_post(&SHARED.mutex);
    /* Increment the number of empty slots */
    sem_post(&SHARED.empty);
  }
  free(arg);
  return NULL;
}


int main()
{
  pthread_t *idP, *idC;
  int index;
  int *arg;

  /* ----Insert code here to set your in and out indices to zero */
  SHARED.in = 0;
  SHARED.out = 0;

  /* Initialize the full and empty semaphore */
  sem_init(&SHARED.full, 0, 0);
  sem_init(&SHARED.empty, 0, BUFF_SIZE);

  /* ----Insert code here to initialize mutex */
  sem_init(&SHARED.mutex, 0, 1);

  /* Allocate memory for idP */
  idP = (pthread_t *)malloc(NP * sizeof(pthread_t));

  /* ----Insert code here to allocate memory for idC */
  idC = (pthread_t *)malloc(NC * sizeof(pthread_t));

  /* Create NP Producers */
  for (index = 0; index < NP; index++)
  {
    arg = (int *)malloc(sizeof(int));
    *arg = index;
    /* Create a new producer */
    pthread_create(&idP[index], NULL, Producer, arg);
  }

  /* ----Insert code here to create NC consumers */
  for (index = 0; index < NC; index++)
  {
    arg = (int *)malloc(sizeof(int));
    *arg = index;
    /* Create a new consumer */
    pthread_create(&idC[index], NULL, Consumer, arg);
  }

  /* "Join" NP Producers */
  for (index = 0; index < NP; index++)
  {
    if (pthread_join(idP[index], NULL))
    {
      printf("Problem joining producer thread at index %i", index);
    }
  }

  /* ----Insert code here to "Join" NC consumers*/
  /* "Join" NC Consumers */
  for (index = 0; index < NC; index++)
  {
    if (pthread_join(idC[index], NULL))
    {
      printf("Problem joining consumer thread at index %i", index);
    }
  }

  /* ----Insert code here to destroy the three semaphores */
  sem_destroy(&SHARED.full);
  sem_destroy(&SHARED.empty);
  sem_destroy(&SHARED.mutex);

  pthread_exit(NULL);
}
