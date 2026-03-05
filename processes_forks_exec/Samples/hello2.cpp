#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int a=3;
  printf("Before Fork a=%i\n", a);
  fork();
	a++;
	printf("After first Fork a=%i\n", a);
  fork();
	a++;
	printf("After second Fork a=%i\n", a);
  return 0;
}
