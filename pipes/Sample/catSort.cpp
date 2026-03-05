#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  int f_des[2];
  char *catArgs[] = {(char *)"cat", (char *)"colorFile.txt", NULL};
  char *sortArgs[] = {(char *)"sort", NULL};

  if (pipe(f_des) == -1)
  {
    perror("Pipe");
    exit(1);
  }
  switch (fork())
  {
  case -1:
    perror("Fork");
    exit(2);
  case 0: /*In the child*/
    int stdbak = dup(1);
    printf("%i\n", stdbak);

    dup2(f_des[1], 1);
    close(f_des[0]);
    close(f_des[1]);
    write(stdbak, "Zin the child\n", strlen("In the child\n"));
    execvp(catArgs[0], catArgs);
    exit(3);
  default: /*In the parent*/
    dup2(f_des[0], 0);
    
		close(f_des[0]);
    close(f_des[1]);  //Try commenting this line out and see what happens
    write(1, "In parent\n", strlen("In parent\n"));
    execvp(sortArgs[0], sortArgs);
    exit(4);
  }
}
