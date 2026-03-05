#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 50

int main(int argc, char *argv[])
{
  int f_des[2];
  static char message[BUFSIZE];

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s message\n", *argv);
    exit(1);
  }
  if (pipe(f_des) == -1)
  {
    perror("Pipe");
    exit(2);
  }
  write(f_des[1], argv[1], strlen(argv[1]));
  {
    printf("Message sent: [%s]\n", argv[1]);
    fflush(stdout);
  }
  if (read(f_des[0], message, BUFSIZE) != -1)
  {
    printf("Message received: [%s]\n", message);
    fflush(stdout);
  }
  else
  {
    perror("Read");
    exit(4);
  }

  exit(0);
}
