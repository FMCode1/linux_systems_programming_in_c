#include "HALmod.h"

int main()
{
  string tokens[MAX_COMMAND_LINE_ARGUMENTS];
  int tokenCount;

  do
  {
    tokenCount = getCommand(tokens);
  } while (processCommand(tokens, tokenCount));

  return 0;
}
