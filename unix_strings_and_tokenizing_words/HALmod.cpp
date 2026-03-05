#include "HALmod.h"

int getCommand(string tokens[])
{
  string commandLine;
  bool commandEntered;
  int tokenCount;

  do
  {
    cout << "HALshell> ";
    while (1)
    {
      getline(cin, commandLine);
      commandEntered = checkForCommand();
      if (commandEntered)
      {
        break;
      }
    }
  } while (commandLine.length() == 0);

  tokenCount = tokenizeCommandLine(tokens, commandLine);

  return tokenCount;
}

int tokenizeCommandLine(string tokens[], string commandLine)
{
  char *token[MAX_COMMAND_LINE_ARGUMENTS];
  char *workCommandLine = new char[commandLine.length() + 1];
  int i;
  int tokenCount;

  for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i++)
  {
    tokens[i] = "";
  }
  strcpy(workCommandLine, commandLine.c_str());
  i = 0;
  if ((token[i] = strtok(workCommandLine, " ")) != NULL)
  {
    i++;
    while ((token[i] = strtok(NULL, " ")) != NULL)
    {
      i++;
    }
  }
  tokenCount = i;

  for (i = 0; i < tokenCount; i++)
  {
    tokens[i] = token[i];
  }

  delete[] workCommandLine;

  return tokenCount;
}

// Do not touch the below function
bool checkForCommand()
{
  if (cullProcess)
  {
    cullProcess = 0;
    cin.clear();
    cout << "\b\b  \b\b";
    return false;
  }

  return true;
}

// This is a very paired down version of Dr. Hilderman's function
int processCommand(string tokens[], int tokenCount)
{
  if (tokens[0] == "shutdown" || tokens[0] == "restart")
  { 
    if (tokenCount > 1)
    {
      cout << "HALshell: " << tokens[0] << " does not require any arguments"
           << endl;
      return 1;
    }
    cout << endl;
    cout << "HALshell: terminating ..." << endl;

    return 0;
  }
    // Added a check for "lo", prints a message and exits
    else if (tokens[0] == "lo") {
    cout << endl;
    cout << "HALshell: terminating due to 'lo' command ..." << endl;
    return 0;
  }
  else {
    return 1;
  }
}


// conVertToC function

char ** convertToC(string tokens[], int tokenCount) {
    char ** cTokens = new char*[tokenCount]; // Allocate memory for the array of pointers

    for (int i = 0; i < tokenCount; i++) {
        cTokens[i] = new char[tokens[i].length() + 1]; // Allocate memory for each string
        strcpy(cTokens[i], tokens[i].c_str()); // Copy the string content into the allocated space
    }

    return cTokens;
}

// cleanUpCArray function
void cleanUpCArray(char ** cTokens, int tokenCount) {
    for (int i = 0; i < tokenCount; i++) {
        delete[] cTokens[i]; // Free each individual string
    }
    delete[] cTokens; // Free the array of pointers
}

//printReverse function
void printReverse(char ** cTokens, int tokenCount) {
    for (int i = tokenCount - 1; i >= 0; i--) {
        cout << cTokens[i] << endl; // Print each string in reverse order
    }
}

