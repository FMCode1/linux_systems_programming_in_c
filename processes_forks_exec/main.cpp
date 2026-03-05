/* -----------------------------------------------------------
 * main.cpp
 *
 * Entry point for the HAL shell project.
 *
 * This file contains the main driver loop for the shell:
 *   - Continuously reads commands from the user
 *   - Tokenizes the input
 *   - Processes built-in and external commands
 *   - Manages parent-child process execution via fork/exec
 *
 * Demonstrates:
 *   - Modular C++ systems programming
 *   - Integration of C++ code with Linux system calls
 * -----------------------------------------------------------
 */

#include "HALmod.h"

int main()
{
    string tokens[MAX_COMMAND_LINE_ARGUMENTS];
    int tokenCount;

    // Main shell loop: continue until processCommand signals termination
    do
    {
        tokenCount = getCommand(tokens);        // Read and tokenize user input
    } while (processCommand(tokens, tokenCount)); // Execute command and wait if necessary

    return 0;
}