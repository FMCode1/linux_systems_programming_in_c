#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int CNT = 0;

sem_t mutex; // global declaration

void *counterFunct(void *a)
{
  int i, tmp;
  for (i = 0; i < NITER; i++)
  {
    sem_wait(&mutex);  // Wait (lock) the semaphore before accessing CNT
    tmp = CNT;     /* copy the global CNT locally */
    tmp = tmp + 1; /* increment the local copy */
    CNT = tmp;     /* store the local value into the global CNT */
    sem_post(&mutex);  // Post (unlock) the semaphore after accessing CNT
  }
}

int main(int argc, char *argv[])
{
  pthread_t tId1, tId2;

  // Initialize the semaphore with value 1 (binary semaphore)
  if (sem_init(&mutex, 0, 1) != 0)
  {
    perror("Semaphore init failed");
    exit(1);
  }

  if (pthread_create(&tId1, NULL, counterFunct, NULL))
  {
    perror("\n ERROR creating thread 1");
    exit(1);
  }

  if (pthread_create(&tId2, NULL, counterFunct, NULL))
  {
    perror("\n ERROR creating thread 2");
    exit(1);
  }

  if (pthread_join(tId1, NULL)) /* wait for the thread 1 to finish */
  {
    perror("\n ERROR joining thread");
    exit(1);
  }

  if (pthread_join(tId2, NULL)) /* wait for the thread 2 to finish */
  {
    perror("\n ERROR joining thread");
    exit(1);
  }

  if (CNT < 2 * NITER)
    printf("\n BOOM! CNT is [%d], should be %d\n", CNT, 2 * NITER);
  else
    printf("\n OK! CNT is [%d]\n", CNT);

  sem_destroy(&mutex);

  pthread_exit(NULL);
}
