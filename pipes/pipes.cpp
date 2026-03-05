/* Please write your code for the lab exercise in this file */

// grep -inw 'sed' colorFile.txt > sed.txt

// Using the system calls from this lab, your goal is to create a program that executes the following command which will count the number of occurrences of "pipe" in the file and write the results to newFile.txt.

// compile and run with :
// g++ pipes.cpp -o pipes
// ./pipes

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int f_des[2];  // File descriptors for the pipe
    pid_t pid;

    // Create the pipe
    if (pipe(f_des) == -1) {
        perror("Error in creating Pipe");
        exit(1);
    }

    // Fork the process
    pid = fork();
    if (pid == -1) { 
        perror("Error in Forking");
        exit(2);
    }

    if (pid == 0) {  // Child process
        // Close the read end of the pipe, as the child will write to the pipe
        close(f_des[0]);

        // Redirect standard output to the write end of the pipe
        if (dup2(f_des[1], 1) == -1) {
            perror("dup2 (child)");
            exit(3);
        }

        // Close the write end of the pipe because we no longer need it after redirection
        close(f_des[1]);

        // Execute the "grep -o -i pipe colorFile.txt" command
        char *myargv[] = {(char *)"grep", (char *)"-o", (char *)"-i", (char *)"pipe", (char *)"colorFile.txt", NULL};
        if (execvp(myargv[0], myargv) == -1) {
            perror("Error with execvp (grep)");
            exit(4);
        }
    } else {  // Parent process
        // Close the write end of the pipe, because parent will read from the pipe
        close(f_des[1]);

        // Redirect standard input to the read end of the pipe
        if (dup2(f_des[0], 0) == -1) {
            perror("Error with dup2 (parent)");
            exit(5);
        }

        // Redirect standard output to the file "newFile.txt" (prepare to write)
        int output_fd = open("newFile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        
        if (output_fd == -1) {
            perror("open (newFile.txt)");
            exit(6);
        }

        // Redirect the standard output to the file (actually write)
        if (dup2(output_fd, 1) == -1) {
            perror("Error with dup2 (parent)");
            exit(7);
        }        char *myargv[] = {(char *)"wc", (char *)"-w", NULL};


        // Close the file descriptor as it's no longer needed after redirection
        close(output_fd);

        // Execute the "wc -w" command
        char *myargv[] = {(char *)"wc", (char *)"-w", NULL};
        if (execvp(myargv[0], myargv) == -1) {
            perror("Error with execvp (wc)");
            exit(8);
        }
    }

    return 0;
}