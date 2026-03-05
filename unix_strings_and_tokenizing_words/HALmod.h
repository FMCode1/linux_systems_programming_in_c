#include <fstream>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// Constants
const int MAX_COMMAND_LINE_ARGUMENTS = 8; // Maximum tokens per command line
const int SLEEP_DELAY = 100000;           // Can be used for pauses (not used here)

// Function prototypes
int getCommand(string tokens[]);
int tokenizeCommandLine(string tokens[], string commandLine);
bool checkForCommand();
int processCommand(string tokens[], int tokenCount);
char ** convertToC(string tokens[], int tokenCount);
void cleanUpCArray(char ** cTokens, int tokenCount);
void printReverse(char ** cTokens, int tokenCount);

// Global flag to handle "culling" a process, usually by signal handling
static volatile sig_atomic_t cullProcess = 0;