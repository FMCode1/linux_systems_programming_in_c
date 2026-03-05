# linux_systems_programming_in_c
Some programming projects based on shell scripting, socket programming(networking), threading process management, synchronization and signal handling

Linux Systems Programming (C)

This repository contains implementations of core operating system concepts developed in C on Linux.
    - Dynamic memory management, process creation, and synchronization
    - Threading and semaphores for concurrent programming
    - Inter-process communication via pipes and sockets
    - Shell scripting and automation tools
    - Modular C development using headers, source, and object files

How to run - Type the following commands in a terminal:
    1. cd path_to_sub_directory (eg. cd sockets)
    2. make
    3. ./demo (or ./name of the output file is, it will likely always be 'demo').
    3. make clean

Note:
    1. Each project includes a 'sample_run.txt' script file that demonstrates a test run of the program. You can go into the subdirectory then run the command below to see the printout in the terminal: 
        cat sample_run.txt

    2. In the absence of a script file, kindly follow 'How to run' or the local README.md to see results.

    3. Files without a Makefile include a README.md file for illustration and steps to run where applicable.

These programs demonstrate practical use of Linux system calls and low-level debugging tools such as GCC and GDB.

Technologies:
    -C, GCC, GDB, POSIX Threads, Linux System Calls, Bash