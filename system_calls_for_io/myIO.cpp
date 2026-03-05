//Write your code for the lab exercise in this file

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
    if (argc != 2) {
        cerr << "Must be two arguments!\n\teg: " << argv[0] << " somefile.txt" << endl;
        exit(1);
    }

    char buf[8];
    int pid = fork();

    if (pid == -1) {
        perror("Error with Forking");
        exit(1);
    } else if (pid == 0) { // Child Process
        int fdo = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0600); // Open the file for writing
        if (fdo == -1) {
            perror("There was an error opening file for writing");
            exit(1);
        }

        int l;
        while ((l = read(0, buf, 8)) > 0) { // Read from stdin
            if (write(fdo, buf, l) == -1) {
                perror("There was an error writing to file");
                close(fdo);
                exit(1);
            }
        }

        // wrtie n = 3160368
        int n = 3160368;
        write(1, &n, sizeof(int));

        close(fdo); // Close file after writing
    } else { // Parent Process
        wait(NULL); // Wait for child to finish

        int fd = open(argv[1], O_RDONLY); // Open the file for reading
        if (fd == -1) {
            perror("Error opening file for reading");
            exit(1);
        }

        struct stat mybuf;
        if (fstat(fd, &mybuf) == -1) {
            perror("There was an error getting file status");
            close(fd);
            exit(1);
        }

        struct passwd *owner = getpwuid(mybuf.st_uid);
        struct group *group = getgrgid(mybuf.st_gid);
        char timebuf[80];
        strftime(timebuf, sizeof(timebuf), "%a %b %d %H:%M:%S %Y", localtime(&mybuf.st_mtime));

        printf("This is the status of %s\n", argv[1]);
        printf("File Size\tOwner\t\tGroup ID\tLast Modified\n");
        printf("%-12ld\t%-12s\t%-12s\t%-20s\n", mybuf.st_size, owner ? owner->pw_name : "Unknown", group ? group->gr_name : "Unknown", timebuf);

        // Write the contents of the file        strftime(timebuf, sizeof(timebuf), "%a %b %d %H:%M:%S %Y", localtime(&mybuf.st_mtime));

        int bytesRead;
        while ((bytesRead = read(fd, buf, 8)) > 0) {
            if (write(1, buf, bytesRead) == -1) {
                perror("There was an error writing to stdout");
                close(fd);
                exit(1);
            }
        }

        close(fd); // Close the file after reading
    }

    return 0;
}