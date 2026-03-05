Sockets Lab: Client-Server Communication

This lab demonstrates basic client-server communication using TCP sockets in C. The server (server_ex.c) waits for client connections and executes a command on behalf of the client. The client (client_ex.c) connects to the server, selects a command, and receives the output.

1️ Compile the programs:
gcc -o server server.c
gcc -o client client.c

2️ Run the server
./server

The server will print the hostname and the port number it is listening on.

It will wait for a client to connect.

This server supports three commands:

date – shows the current date and time

env – prints environment variables

ip addr show – shows network interfaces

3️ Run the client (in another instance of the terminal)
./client

You will be prompted to enter the hostname of the server and the port number printed by the server.

Then you will select a command by typing 1, 2, or 3.

The client sends the selection to the server.

The server executes the command and sends the output back to the client.

The client prints the output on your terminal.

4️ Example workflow
Server terminal:
The hostname is: myhost
The first hostaddress is: 192.168.1.10
Socket assigned: 55000
Waiting for client...

Client terminal:
hostname: myhost
port number: 55000
What command would you like the server to execute?
Type a number in the round bracket
(1)date
(2)env
(3)ip addr show
2

Output:
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
HOME=/home/user