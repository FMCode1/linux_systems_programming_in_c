#include "HALmod.h"

// Reads a command line from the user and tokenizes it
int getCommand(string tokens[]) 
{ 
    string commandLine; 
    bool commandEntered; 
    int tokenCount; 

    do 
    { 
        cout << "HALshell> "; 

        // Wait until a valid command is entered
        while (1) 
        { 
            getline(cin, commandLine); // Read a full line
            commandEntered = checkForCommand(); // Checks for cullProcess
            if (commandEntered) 
                break;
        } 
    } while (commandLine.length() == 0); // Skip empty lines

    // Break the command line into tokens
    tokenCount = tokenizeCommandLine(tokens, commandLine); 
    return tokenCount; 
}

// Splits the command line into separate tokens (words) based on whitespace
int tokenizeCommandLine(string tokens[], string commandLine) 
{ 
    char *token[MAX_COMMAND_LINE_ARGUMENTS]; 
    char *workCommandLine = new char[commandLine.length() + 1]; 
    int tokenCount; 

    // Initialize tokens array
    for (int i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i++) 
        tokens[i] = ""; 

    strcpy(workCommandLine, commandLine.c_str()); // Copy string to C-style array

    int i = 0;
    if ((token[i] = strtok(workCommandLine, " ")) != NULL) // first token
    { 
        i++; 
        while ((token[i] = strtok(NULL, " ")) != NULL) // remaining tokens
            i++; 
    } 
    tokenCount = i; 

    // Copy tokens into C++ strings array
    for (i = 0; i < tokenCount; i++) 
        tokens[i] = token[i]; 

    delete[] workCommandLine; 
    return tokenCount; 
}

// Checks if the process input should be ignored (signal-based)
bool checkForCommand() 
{ 
    if (cullProcess) 
    { 
        cullProcess = 0;
        cin.clear(); 
        cout << "\b\b  \b\b"; // erase previous input prompt
        return false; 
    } 
    return true; 
}

// Handles simple shell commands (shutdown, restart, or "lo")
int processCommand(string tokens[], int tokenCount) 
{ 
    if (tokens[0] == "shutdown" || tokens[0] == "restart") 
    {  
        if (tokenCount > 1) 
        { 
            cout << "HALshell: " << tokens[0] 
                 << " does not require any arguments" << endl; 
            return 1; 
        } 
        cout << "\nHALshell: terminating ..." << endl; 
        return 0; 
    } 
    else if (tokens[0] == "lo") 
    { 
        cout << "\nHALshell: terminating due to 'lo' command ..." << endl; 
        return 0; 
    } 
    else 
    { 
        return 1; // Continue running shell
    } 
}

// Converts C++ strings into C-style string array (char**)
char ** convertToC(string tokens[], int tokenCount) 
{ 
    char ** cTokens = new char*[tokenCount]; // Allocate array of char pointers

    for (int i = 0; i < tokenCount; i++) 
    { 
        cTokens[i] = new char[tokens[i].length() + 1]; // allocate each string
        strcpy(cTokens[i], tokens[i].c_str());          // copy content
    } 
    return cTokens; 
}

// Frees memory allocated for C-style array
void cleanUpCArray(char ** cTokens, int tokenCount) 
{ 
    for (int i = 0; i < tokenCount; i++) 
        delete[] cTokens[i]; 
    delete[] cTokens; 
}

// Prints tokens in reverse order
void printReverse(char ** cTokens, int tokenCount) 
{ 
    for (int i = tokenCount - 1; i >= 0; i--) 
        cout << cTokens[i] << endl; 
} 