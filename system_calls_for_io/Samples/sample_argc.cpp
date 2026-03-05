#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  int i;
	if (argc < 2)
  {
    printf("Please include arguments\n");
    exit(1);
  }
  for (i = 0; i < argc; i++)
  {
    cout << argv[i] << endl;
  }
  return 0;
}
