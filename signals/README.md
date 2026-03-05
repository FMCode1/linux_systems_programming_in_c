This lab demonstrates basic signal handling in a parent-child process using C++ and Linux signals. The child handles SIGWINCH and exits when it receives it, while the parent handles SIGCHLD when the child terminates. This lab shows the use of fork(), sigaction(), and signal sending via kill().

To compile and run (Type the following commands in a terminal):

g++ -o signal_ex signal_ex.cpp

./signal_ex > signal_output.txt

cat signal_output.txt

You should see the parent and child printing their waiting messages. When the child receives a signal (SIGWINCH), it exits, and the parent detects this via SIGCHLD.