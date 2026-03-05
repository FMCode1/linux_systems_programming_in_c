#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  char cstr1[] = "This is a sample string. Is it working?";
  char delim[] = " ,.-;!?";
  char *token;

  cout << "cstr1 before being tokenized: " << cstr1 << endl << endl;

  // In the first call to strtok, the first argument is the line to be tokenized
  token = strtok(cstr1, delim);
  cout << token << endl;

  // In subsequent calls to strtok, the first argument is NULL
  while ((token = strtok(NULL, delim)) != NULL)
  {
    cout << token << endl;
  }

	cout << endl << "cstr1 after being tokenized: " << cstr1 << endl;
}