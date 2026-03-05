This lab demonstrates low-level file input/output and process handling using fork(). The program reads input from the user, writes it to a file via a child process, and then the parent process reads the file, prints its contents, and displays metadata such as file size, owner, group, and last modification time.

To compile and run:

g++ -o myIO myIO.cpp
./myIO example.txt

Type your input, then press Ctrl+D to signal end-of-input.

The parent process will then display file metadata and contents.

This lab illustrates parent-child coordination, low-level file operations, and retrieving file attributes programmatically.