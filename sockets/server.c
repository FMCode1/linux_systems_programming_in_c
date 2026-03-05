/*****************************************************************
 Sockets Daemon Program

 This code was modified from Nigel Horspools, "The Berkeley
 Unix Environment".

 A daemon process is started on some host.  A socket is acquired
 for use, and it's number is displayed on the screen.  For clients
 to connect to the server, they must use this socket number.
*****************************************************************/

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define PORTNUM 0

/* Set up the location for the file to display when the daemon (okay,
 * server for you religious types) is contacted by the client. */
#define BBSD_FILE "./test.bbs.file"

/* Display error message on stderr and then exit. */
#define OOPS(msg)                                                              \
  {                                                                            \
    perror(msg);                                                               \
    exit(1);                                                                   \
  }

#define MAXLINE 512

int main()
{
  struct sockaddr_in saddr; /* socket information */
  struct hostent *hp;       /* host information */
  char hostname[256];       /* host computer */
  socklen_t slen;           /* length socket address */
  int s;                    /* socket return value */
  int sfd;                  /* socket descriptor returned from accept() */
  char ch[MAXLINE];         /* character for i/o */
  int bbf;
  int num_char = MAXLINE;

  /* Clear the data structure (saddr) to 0's. */
  memset(&saddr, 0, sizeof(saddr));

  /* Tell our socket to be of the internet family (AF_INET). */
  saddr.sin_family = AF_INET;

  /* Aquire the name of the current host system (the local machine). */
  gethostname(hostname, sizeof(hostname));
  printf("The hostname is: %s\n", hostname);

  /* Return misc. host information.  Store the results in the
   * hp (hostent) data structure.  */
  hp = gethostbyname(hostname);
  printf("The first hostaddress is: %s\n", inet_ntoa(*((struct in_addr *)(hp->h_addr_list[0]))));

  /* Copy the host address to the socket data structure. */
  memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);

  /* Convert the integer Port Number to the network-short standard
   * required for networking stuff. This accounts for byte order differences. */
  saddr.sin_port = htons(PORTNUM);

  /* Open socket */
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
    OOPS("socket");

  /* Register our address with the system. */
  if (bind(s, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
    OOPS("bind");

  /* Display the port that has been assigned to us. */
  slen = sizeof(saddr);
  getsockname(s, (struct sockaddr *)&saddr, &slen);
  printf("Socket assigned: %d\n", ntohs(saddr.sin_port));

  /* Tell socket to wait for input.  Queue length is 1. */
  if (listen(s, 1) != 0)
    OOPS("listen");

  /* Loop indefinitely and wait for events. */
  for (;;)
  {
    /* Wait in the 'accept()' call for a client to make a connection. */
    sfd = accept(s, NULL, NULL);
    if (sfd == -1)
      OOPS("accept");
    printf("Connection established\n");
    fflush(stdout);

    // Read a character from the socket (the command that the client wants to execute)
    read(sfd, ch, 1);
    printf("Client sent command: %c\n", ch[0]);

    // Fork a process and check
    int pid = fork();
    if (pid == -1)
    {
      OOPS("fork");
    }
    else if (pid == 0)
    { // Child process
      // Redirect standard output to the socket
      if (dup2(sfd, 1) == -1)
        OOPS("dup2");

      // Execute the command based on the client's choice
      switch (ch[0])
      {
      case '1': // date command
        printf("Executing Command: date\n");
        execlp("date", "date", (char *)NULL);
        break;
      case '2': // env command
        printf("Executing Command: env\n");
        execlp("env", "env", (char *)NULL);
        break;
      case '3': // ip addr show command
        printf("Executing Command: ip addr show\n");
        execlp("ip", "ip", "addr", "show", (char *)NULL);
        break;
      default:
        printf("Invalid command received\n");
        exit(1);
      }

      // If exec fails, exit the child process
      OOPS("exec failed");
    }
    else
    { // Parent process
      // Wait for the child process to finish
      wait(NULL);
    }

    close(sfd); // Close the socket after processing the client
  }

  return 0;
}
