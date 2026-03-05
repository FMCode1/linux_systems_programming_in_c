#include <stdio.h>
#include <signal.h> // allows us use 'kill'
#include <stdlib.h>
#include <unistd.h>


void dontInterrupt(int sigNo)
{
  printf("Hahahaha your %d signal cannot stop me\n", sigNo);
}

int main(void)
{
  int i;

  sigset_t interruptMask;
  sigemptyset(&interruptMask);
  sigaddset(&interruptMask, SIGINT);
  sigaddset(&interruptMask, SIGQUIT);
  sigaddset(&interruptMask, SIGKILL);


  struct sigaction act;
  act.sa_mask = interruptMask;
  act.sa_flags = 0;
  act.sa_handler = &dontInterrupt;
  
  sigaction(SIGINT, &act, NULL);
  perror("INT");
  sigaction(SIGQUIT, &act, NULL);
  perror("QUIT");
  sigaction(SIGKILL, &act, NULL);
  perror("KILL"); // Kill is an invalid argument

  for (i = 0;; ++i)
  {
    printf("%i\n", i);
    sleep(1);

    if(i == 5)
    {
      kill(getpid(), SIGINT); // arguments are what process, what signal do you want to send, counts to 5
    // kill(getpid(), SIGQUIT); // arguments are what process, what signal do you want to send
    // kill(getpid(), SIGINT); // arguments are what process, what signal do you want to send
  }
  }
}
