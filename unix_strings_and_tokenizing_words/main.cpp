#include "HALmod.h"

int main() {
    string tokens[MAX_COMMAND_LINE_ARGUMENTS];
    int tokenCount;

    do {
        tokenCount = getCommand(tokens);             // Get user input and tokenize
        char ** cTokens = convertToC(tokens, tokenCount); // Convert to C-style strings
        printReverse(cTokens, tokenCount);          // Print tokens in reverse order
        cleanUpCArray(cTokens, tokenCount);         // Free memory
    } while (processCommand(tokens, tokenCount));   // Exit loop if shutdown/restart/lo

    return 0;
}