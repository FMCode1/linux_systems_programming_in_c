/* signals_ex.cpp
 * Demonstrates basic signal handling in a parent-child process setup.
 * 
 * - The child handles SIGWINCH and exits when it receives it.
 * - The parent handles SIGCHLD when the child terminates.
 * - Shows use of fork(), sigaction(), and kill() to manage signals.
   Signals Covered:
   - SIGWINCH (Child handles)
   - SIGCHLD  (Parent handles)
   - SIGTERM, SIGSEGV, SIGTSTP, SIGKILL, SIGSTOP (theoretical references)
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pid_t pid;  // child process ID

// Handler for SIGWINCH (child)
void handle_SIGWINCH(int sigNo) {
    printf("Child received signal %d\n", sigNo);
    exit(0);  // Child exits after handling SIGWINCH
}

// Handler for SIGCHLD (parent)
void handle_SIGCHLD(int sigNo) {
    printf("Parent received SIGCHLD %d\n", sigNo);
    exit(0);  // Parent exits after child terminates
}

int main() {
    struct sigaction sa_child, sa_parent;

    // SIGWINCH handler for the child
    sa_child.sa_handler = handle_SIGWINCH;
    sigemptyset(&sa_child.sa_mask);
    sa_child.sa_flags = 0;
    sigaction(SIGWINCH, &sa_child, NULL);

    // SIGCHLD handler for the parent
    sa_parent.sa_handler = handle_SIGCHLD;
    sigemptyset(&sa_parent.sa_mask);
    sa_parent.sa_flags = 0;
    sigaction(SIGCHLD, &sa_parent, NULL);

    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child Process
        for (int count = 0; count < 7; count++) {
            printf("Child waiting!!\n");
            struct timespec t = {0, 500000000L}; // 0.5 seconds
            nanosleep(&t, NULL);
        }
        // Child now waits for signal (SIGWINCH)
        while (1) pause();  // wait indefinitely for signals
    } else {
        // Parent Process
        while (1) {
            printf("Parent waiting!!\n");
            struct timespec t = {0, 500000000L}; // 0.5 seconds
            nanosleep(&t, NULL);

            printf("Parent is sending SIGWINCH to child\n");
            kill(pid, SIGWINCH);  // send signal

            // Parent will handle SIGCHLD when child exits
            pause();
        }
    }

    return 0;
}