// myIO.cpp
// This program demonstrates low-level file I/O and process handling.
// A child process writes input to a file, and the parent reads it and displays file info.

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) 
{
    // Check for correct number of arguments
    if (argc != 2) {
        cerr << "Must be two arguments!\n\teg: " << argv[0] << " somefile.txt" << endl;
        exit(1);
    }

    char buf[8];  // buffer for reading/writing data in chunks
    int pid = fork();  // create a child process

    if (pid == -1) {
        perror("Error with Forking");
        exit(1);
    } 
    else if (pid == 0) { // Child Process
        // Open file for writing, create if not exists, truncate to append
        int fdo = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0600); 
        if (fdo == -1) {
            perror("Error opening file for writing");
            exit(1);
        }

        int l;
        // Read from stdin (keyboard) in chunks of 8 bytes and write to file
        while ((l = read(0, buf, 8)) > 0) { 
            if (write(fdo, buf, l) == -1) {
                perror("Error writing to file");
                close(fdo);
                exit(1);
            }
        }

        // Write a demonstration integer to stdout (binary)
        int n = 3160368;
        write(1, &n, sizeof(int));

        close(fdo); // Close file after writing
    } 
    else { // Parent Process
        wait(NULL); // Wait for child process to finish

        // Open the same file for reading
        int fd = open(argv[1], O_RDONLY); 
        if (fd == -1) {
            perror("Error opening file for reading");
            exit(1);
        }

        struct stat mybuf;
        // Get file metadata
        if (fstat(fd, &mybuf) == -1) {
            perror("Error getting file status");
            close(fd);
            exit(1);
        }

        // Retrieve owner and group names
        struct passwd *owner = getpwuid(mybuf.st_uid);
        struct group *group = getgrgid(mybuf.st_gid);

        // Format the last modified time as a string
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%a %b %d %H:%M:%S %Y", localtime(&mybuf.st_mtime));

        // Print file metadata
        printf("This is the status of %s\n", argv[1]);
        printf("File Size\tOwner\t\tGroup ID\tLast Modified\n");
        printf("%-12ld\t%-12s\t%-12s\t%-20s\n", 
               mybuf.st_size, 
               owner ? owner->pw_name : "Unknown", 
               group ? group->gr_name : "Unknown", 
               timebuf);

        // Read the contents of the file in chunks of 8 bytes and write to stdout
        int bytesRead;
        while ((bytesRead = read(fd, buf, 8)) > 0) {
            if (write(1, buf, bytesRead) == -1) {
                perror("Error writing to stdout");
                close(fd);
                exit(1);
            }
        }

        close(fd); // Close the file after reading
    }

    return 0;
}