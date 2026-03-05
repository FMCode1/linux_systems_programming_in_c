/* -----------------------------------------------------------
 * fork_demo.cpp
 *
 * Demonstrates parent and child process behavior in Linux.
 *
 * This program shows:
 *   - How fork() creates a child process
 *   - That global variables are duplicated after fork
 *   - How the parent and child processes run independently
 *   - Basic process synchronization using sleep()
 *
 * Output example:
 *   CHILD0
 *   PARENT0
 *   CHILD1
 *   PARENT0
 *   ...
 *
 * Skills demonstrated:
 *   - Process creation and control (fork)
 *   - Understanding memory isolation between processes
 *   - Simple I/O in C
 * -----------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char mynum = '0'; // global variable to show independent copies in parent/child

int main(void)
{
    int i;
    pid_t fork_return;
    char buffer[10];

    // Create a new process
    fork_return = fork();

    if (fork_return == 0) // Child process
    {
        strcpy(buffer, "CHILD");
        for (i = 0; i < 5; ++i)
        {
            mynum = i + '0';      // Update child’s copy of the global variable
            sleep(1);             // Simulate work
            printf("%s%c\n", buffer, mynum);
            fflush(stdout);
        }
        return 0;
    }
    else if (fork_return > 0) // Parent process
    {
        strcpy(buffer, "PARENT");
        for (i = 0; i < 5; ++i)
        {
            sleep(1);             // Simulate work
            printf("%s%c\n", buffer, mynum); // Parent’s copy of global variable is unchanged
            fflush(stdout);
        }
        return 0;
    }
    else // Fork failed
    {
        perror("fork failed");
        return 1;
    }
}