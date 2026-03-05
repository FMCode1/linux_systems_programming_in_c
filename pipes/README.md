Shell Scripting, Signals, and Pipes Lab

Unix commands alone are powerful, but when you combine them together, you can accomplish complex tasks easily. One way you can combine Unix commands is through using pipes and filters on the command line. This lab covers shell scripting, process control, and pipes.

Child executes:

grep -o -i pipe colorFile.txt

Parent executes:

wc -w

Output is redirected to newFile.txt.

To compile and run:

g++ pipes.cpp -o pipes
./pipes

The file newFile.txt will contain the number of occurrences of "pipe" in colorFile.txt (currently = 7).