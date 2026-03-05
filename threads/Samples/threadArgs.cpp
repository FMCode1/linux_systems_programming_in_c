//
// Controlling output with mutexes.
//
// Based on p11.1.cxx from Interprocess Communications in Linux
// By: John Shapley Gray
// Adapted for CS330 by Alex Clarke
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
struct ArgPackage
{
  int arg1;
  int arg2;
};

pthread_mutex_t output_lock;

void *printArgs(void *);

int main(int argc, char *argv[])
{
  int num_threads;
  pthread_t *thread_ids;
  void *p_status;
  struct ArgPackage *theArgs;

  // Use unbuffered output on stdout
  setvbuf(stdout, (char *)NULL, _IONBF, 0);

  // Set up an output lock so that threads wait their turn to speak.
  if (pthread_mutex_init(&output_lock, NULL) != 0)
  {
    perror("Could not create mutex for output: ");
    return 1;
  }
  printf("How many threads? ");
  scanf("%d", &num_threads);
  thread_ids = (pthread_t *)malloc(sizeof(pthread_t *) * num_threads);

  // generate threads
  for (int i = 0; i < num_threads; i++)
  {
    theArgs = (struct ArgPackage *)malloc(sizeof(struct ArgPackage));
    theArgs->arg1 = i;
    theArgs->arg2 = num_threads;
    if (pthread_create(&thread_ids[i], NULL, printArgs, theArgs) > 0)
    {
      perror("creating thread:");
      return 2;
    }
  }

  // join threads and print their return values
  for (int i = 0; i < num_threads; i++)
  {
    if (pthread_join(thread_ids[i], &p_status) != 0)
    {
      perror("trouble joining thread: ");
      return 3;
    }
  }
  free(thread_ids);
  return 0;
}

//
void *printArgs(void *mainArgs)
{
  struct ArgPackage *args = (struct ArgPackage *)mainArgs;

  if (pthread_mutex_lock(&output_lock) != 0)
  {
    perror("Could not lock output: ");
    exit(4); // something horrible happened - exit whole program with error
  }
  printf("Argument 1: %d, Argument 2: %d\n", args->arg1, args->arg2);
  if (pthread_mutex_unlock(&output_lock) != 0)
  {
    perror("Could not unlock output: ");
    exit(5); // something horrible happened - exit whole program with error
  }
  free(args);
  return NULL;
}
