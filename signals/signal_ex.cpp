//Please write your code for the lab exercise in this file
/*
1.  Using the command: man 7 signal

    Terminate (Exit): SIGTERM (Signal 15) = Terminate process

    Core Dump: SIGSEGV (Signal 11) = Core

    Stop: SIGTSTP (Signal 18) = Ctrl + Z

    Ignore: SIGCHLD (Signal 20) = Child is ignored by parent

2.  The 2 commands we cannot change the default action for are:

    SIGKILL (Signal 9) and SIGSTOP (Signal 19), both cannot be caught, blocked, or ignored

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pid_t pid;  // child process ID

// Handler for SIGWINCH (received by the child)
void handle_SIGWINCH(int sigNo) {
    printf("Signal %d received.\n", sigNo);
    printf("Child received signal\n");
    exit(0);  // Child exits after handling SIGWINCH
}

// Handler for SIGCHLD (received by the parent)
void handle_SIGCHLD(int sigNo) {
    printf("Signal %d received.\n", sigNo);
    printf("Parent received signal\n");
    exit(0);  // Parent exits after receiving SIGCHLD
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
        // Error in forking
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child Process
        int count = 0;
        while (1) {  // Print "Child waiting!!" 7 times
            printf("Child waiting!!\n");
            nanosleep((const struct timespec[]){{0, 500000L}}, NULL);  // delay
            count++;
        }
    } else {
        // Parent Process
        while (1) {
            printf("Parent waiting!!\n");
            nanosleep((const struct timespec[]){{0, 500000L}}, NULL);  // delay
            
            // Send SIGWINCH to the child
            printf("Parent is sending a signal\n");
            // kill(pid, SIGWINCH);

            // ps -fu
            // kill -9 pid, withouy modifying code

            // After sending the signal, the parent will handle SIGCHLD when the child exits
        }
    }

    return 0;
}