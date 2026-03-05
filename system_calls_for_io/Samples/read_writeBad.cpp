// Modified from page 7 of Interprocess Communication in Unix by John
// Shapely Gray

// checking errno and using perror

#include <cstdio>
#include <cstdlib>
#include <errno.h>     //needed for perror
#include <fcntl.h>     //needed for open
#include <sys/stat.h>  //needed for open
#include <sys/types.h> //needed for open
#include <unistd.h>
#include <string>

using namespace std;

extern int errno;
// extern char *sys_errlist[];

int main(int argc, char *argv[])
{
  int outFile;
  int n_char = 0;
  string buffer;
  string msg = "Enter text and CTRL-D to end";

  // Initially n_char is set to 0 -- errno is 0 by default
  printf("n_char = %d \t errno = %d\n", n_char, errno);

  outFile = open(argv[1], O_WRONLY);
  printf("\noutFile = %d \t errno = %d\n", outFile, errno);
  if (outFile == -1)
  {
    perror(NULL);
    exit(1);
  }

  write(0, msg, msg.length()); //Two mistakes. How would you fix it?
	write(1, "Enter text and CTRL-D to end ", 29);
  // Use the read system call to obtain 10 characters from inFile
  while ((n_char = read(0, buffer, 10)) != 0)
  {
    // Display the characters read
    n_char = write(outFile, buffer, n_char);
  }

  close(outFile);

  return 0;
}
