#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, charz *argv[]) 
{

    if(argc != 2) {
        cerr << "Must be two arguments!\n\teg: " << argv[0] << " somefile.txt" << endl;
        exit(1);
    }

    int fdo = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0600);
    cout << fdo << endl;
    if (fdo == -1)
    {
        perror(NULL);
        exit(1);
    }

    char buf[8];
    int l;

    while((l=read(0, buf, 8)) > 0)
    {
        if (write(fdo, buf, l) == -1)
        {
            perror("There was an error writing");
            exit(1);
        }
        l=read(0, buf, 8);
    }

    // Reading File

    // int fd = open("myfile.txt", O_RDONLY);
    // cout << fd << endl;
    // cout << buf << endl;
    // if (fd == -1)
    // {
    //     perror(NULL);
    //     exit(1);
    // }

    // while((l=read(0, buf, 8)) > 0)
    // {
    //     if (write(fd, buf, l) == -1)
    //     {
    //         perror("There was an errow writing");
    //         exit(1);
    //     }
    //     l=read(0, buf, 8);
    // }

    return 0;
}