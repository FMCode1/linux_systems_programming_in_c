/* -----------------------------------------------------------
 * HALmod.cpp
 *
 * A simplified Unix-style shell implemented in C++.
 * 
 * This file contains functions to:
 *   - Read and tokenize user commands
 *   - Process built-in commands (shutdown, restart, lo)
 *   - Fork and execute external commands via execvp
 *   - Handle parent-child process management and display exit status
 *
 * Demonstrates key systems programming concepts in Linux:
 *   - Process creation and control (fork, exec, wait)
 *   - Interfacing C++ strings with C-style argv arrays
 *   - Dynamic memory management
 *   - Basic shell I/O handling
 *
 * Suitable for showcasing OS and Linux systems programming skills.
 * -----------------------------------------------------------
 */

// HAL shell simplified implementation
#include "HALmod.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

// -----------------------------------------------------------
// Reads a command line from the user and tokenizes it
// -----------------------------------------------------------
int getCommand(string tokens[])
{
    string commandLine;
    bool commandEntered;
    int tokenCount;

    do
    {
        cout << "HALshell> ";

        // Keep prompting until a valid command is entered
        while (1)
        {
            getline(cin, commandLine);
            commandEntered = checkForCommand();
            if (commandEntered)
                break;
        }
    } while (commandLine.length() == 0);

    tokenCount = tokenizeCommandLine(tokens, commandLine);
    return tokenCount;
}

// -----------------------------------------------------------
// Tokenizes a command line into individual words/tokens
// -----------------------------------------------------------
int tokenizeCommandLine(string tokens[], string commandLine)
{
    char *token[MAX_COMMAND_LINE_ARGUMENTS];
    char *workCommandLine = new char[commandLine.length() + 1];
    int i;
    int tokenCount;

    // Initialize all token strings to empty
    for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i++)
        tokens[i] = "";

    strcpy(workCommandLine, commandLine.c_str());

    // Split the command line by spaces
    i = 0;
    if ((token[i] = strtok(workCommandLine, " ")) != NULL)
    {
        i++;
        while ((token[i] = strtok(NULL, " ")) != NULL)
            i++;
    }

    tokenCount = i;

    // Copy C strings into C++ string array
    for (i = 0; i < tokenCount; i++)
        tokens[i] = token[i];

    delete[] workCommandLine;
    return tokenCount;
}

// -----------------------------------------------------------
// Checks whether the input should be processed
// Do not modify
// -----------------------------------------------------------
bool checkForCommand()
{
    if (cullProcess)
    {
        cullProcess = 0;
        cin.clear();
        cout << "\b\b  \b\b"; // Clear unwanted characters
        return false;
    }
    return true;
}

// -----------------------------------------------------------
// Processes a command entered by the user
// -----------------------------------------------------------
int processCommand(string tokens[], int tokenCount)
{
    // Handle built-in commands
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
        // Fork a new process to run external commands
        pid_t pid = fork();

        if (pid < 0) // Fork failed
        {
            perror("Fork failed");
            return 1;
        }
        else if (pid == 0) // Child process
        {
            // Convert C++ tokens to C-style argv array
            char **args = convertToC(tokens, tokenCount);

            // Execute the command
            execvp(args[0], args);

            // Only reached if execvp fails
            perror("execvp failed");
            return 1;
        }
        else // Parent process
        {
            int status;

            // Wait for the child to finish
            wait(&status);

            // Print child's exit status
            if (WIFEXITED(status))
                cout << "Child exited with status: " << WEXITSTATUS(status) << endl;
            else
                cout << "Child process did not exit normally" << endl;

            return 1;
        }
    }
}

// -----------------------------------------------------------
// Converts C++ string tokens into a null-terminated char** array
// required for execvp
// -----------------------------------------------------------
char **convertToC(string tokens[], int tokenCount)
{
    char **words = (char **)malloc(sizeof(char *) * (tokenCount + 1));

    for (int i = 0; i < tokenCount; i++)
    {
        words[i] = strdup(tokens[i].c_str()); // copy string
    }

    words[tokenCount] = NULL; // NULL terminate for execvp
    return words;
}