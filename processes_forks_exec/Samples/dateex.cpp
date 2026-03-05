#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
  int status;

  pid_t fork_return;

  char *myargv[] = {(char *)"ls", (char *)"-l", NULL};

  fork_return = fork();

  if (fork_return == 0)
  {
    // execl("/usr/bin/ls","ls", "-l",NULL);//works
    // execl("/bin/date","date",NULL);//works
    // execl("date","date",NULL);//doesn't work
    // execlp("date","date",NULL);//works
    execvp(myargv[0], myargv[0]);
    //execv(myargv[0], &myargv[1]);
    perror("Error Forking");
  }

  else if (fork_return > 0)
  {
    wait(&status);
    printf("In the PARENT process\n");
  }
  else
  {
    printf("Error\n");
  }
  return 0;
}
