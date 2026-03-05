/* -----------------------------------------------------------
 * HALmod.h
 *
 * Header file for the HAL shell project (C++ systems programming).
 *
 * Provides:
 *   - Global constants for command parsing and delays
 *   - Function prototypes for reading and processing commands
 *   - Signal-safe global variables
 * -----------------------------------------------------------
 */

#ifndef HALMOD_H
#define HALMOD_H

#include <fstream>     // Optional file I/O
#include <iostream>    // Standard I/O streams
#include <signal.h>    // Signal handling
#include <sstream>     // String parsing utilities
#include <stdlib.h>    // malloc, exit
#include <string.h>    // strcpy, strtok, strdup
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait(), WIFEXITED, WEXITSTATUS

using namespace std;

// -----------------------------------------------------------
// Constants
// -----------------------------------------------------------
const int MAX_COMMAND_LINE_ARGUMENTS = 8; // Maximum tokens in a command
const int SLEEP_DELAY = 100000;           // Delay in microseconds for loops

// -----------------------------------------------------------
// Function declarations
// -----------------------------------------------------------
int getCommand(string tokens[]);
int tokenizeCommandLine(string tokens[], string commandLine);
bool checkForCommand();
int processCommand(string tokens[], int tokenCount);
char **convertToC(string tokens[], int tokenCount);

// -----------------------------------------------------------
// Global variables
// -----------------------------------------------------------
static volatile sig_atomic_t cullProcess = 0; // Signal-safe flag for interrupting input

#endif // HALMOD_H