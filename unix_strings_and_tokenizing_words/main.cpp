    // Store the answer to the following questions as comments at the beginning of main.cpp:
    //     What is Dr. Hilderman's code tokenizing based on (ie. what delimeter(s) separate(s) his words)?
          // Answer: A whitespace character, egg space, tabs  

    //     What are two reasons why his tokens are strings instead of c strings
          // Answer: 1. C++ strings are easier to work with than C strings and many in-built functions to handle string manipulation
          //         2. C++ strings don't require you to manually handle null-termination, the string class handles that for you
    // Add functionality to the processCommand function so that "lo" will also cause the shell to exit

#include "HALmod.h"

int main() {
    string tokens[MAX_COMMAND_LINE_ARGUMENTS];
    int tokenCount;

    do {
        tokenCount = getCommand(tokens);

        // Convert to C-style array
        char ** cTokens = convertToC(tokens, tokenCount);

        // Print the tokens in reverse order
        printReverse(cTokens, tokenCount);

        // Clean up the memory allocated for C-style array
        cleanUpCArray(cTokens, tokenCount);

    } while (processCommand(tokens, tokenCount));

    return 0;
}