#include "HALmod.h"

// You were asked to add a print message after the exec* call, does it print it in all cases? Why? Why not?
  // a No, it does not print in all cases. It only prints if the execvp fails.
// Who is the parent of your executable (./demo) program?
  
  // b By running ps -u fco483 -o pid,ppid,cmd in halshell  
  // The parent of the executable program is the shell program since it is running the demo.
// How would you change the code so that the child and parent "appear" to run concurrently (ie. at the same time)?
  
  // c I would remove the wait call from the parent process, so that the parent process will continue executing while the child process is running.

// Part 2
// Why does child print CHILD0, CHILD1, CHILD2, etc whereas parent prints PARENT0, PARENT0, PARENT0, etc? Remember mynum is a global variable.
//  because the mynum variable is being updated in the child process's loop, but not the parent's

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

// original code
// // This is a very paired down version of Dr. Hilderman's function
// int processCommand(string tokens[], int tokenCount)
// {
//   if (tokens[0] == "shutdown" || tokens[0] == "restart" || tokens[0] == "lo")
//   {
//     if (tokenCount > 1)
//     {
//       cout << "HALshell: " << tokens[0] << " does not require any arguments"
//            << endl;
//       return 1;
//     }
//     cout << endl;
//     cout << "HALshell: terminating ..." << endl;

//     return 0;
//   }
//   else
//     return 1;
// }

// This is a very paired down version of Dr. Hilderman's function
int processCommand(string tokens[], int tokenCount)
{
  if (tokens[0] == "shutdown" || tokens[0] == "restart" || tokens[0] == "lo")
  {
    if (tokenCount > 1)
    {
      cout << "HALshell: " << tokens[0] << " does not require any arguments" << endl;
      return 1;
    }
    cout << endl;
    cout << "HALshell: terminating ..." << endl;
    return 0;
  }
  else
  {
    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0)  // If fork failed
    {
      perror("Fork failed");
      return 1;
    }
    else if (pid == 0)  // this is the child process
    {
      // Convert tokens to a char** for execvp
      char **args = convertToC(tokens, tokenCount);
      
      // running the command with execvp
      execvp(args[0], args);
      
      // If execvp fails, print error message and exit
      perror("execvp failed");
        return 1; // changed to return 1
      // exit(1);
    }
    else  // Parent process
    {
      int status;
      // Wait for the child process to finish
      wait(&status);

      // Check if the child process exited normally
      if (WIFEXITED(status)) 
      {
        cout << "Child exited with status: " << WEXITSTATUS(status) << endl;
      }
      else
      {
        cout << "Child process did not exit normally" << endl;
      }
      
      return 1;
    }
  }
}

// original code
// char **convertToC(string tokens[], int tokenCount)
// {
//   char **words;
//   words = (char **)malloc(sizeof(char *) * tokenCount);

//   for (int i = 0; i < tokenCount; i++)
//   {
//     words[i] = strdup(tokens[i].c_str());
//   }
//   return words;
// }


char **convertToC(string tokens[], int tokenCount)
{
  char **words;
  words = (char **)malloc(sizeof(char *) * (tokenCount + 1));

  for (int i = 0; i < tokenCount; i++)
  {
    // Copy each token string into the allocated memory
    words[i] = strdup(tokens[i].c_str());
  }

  // Add a NULL pointer at the end of the array to terminate it
  words[tokenCount] = NULL;
  
  return words;
}