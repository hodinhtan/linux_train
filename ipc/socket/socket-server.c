#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// read text from the socket and print it out.
// Continue until the socket closes.
// REturn nonzero if the client sent a "quit" message, zero otherwise

int server (int client_socket )
{
  while (1) {
    int length;
    char* text;

    // First , read the length of text message from the socket. If read 
    // return zero, the client closed the connection
    if (read (client_socket, &length, sizeof (length)) ==0 )
      return 0;
    // Allocate a buffer to hold the text
    text = (char*) malloc (length);
    // read the text itself , and print it
    read (client_socket, text, length);
    printf ("%s\n", text);
    // free the buffer
    free (text);
    // if the client sent the message "quit" , we'r all done 
    if (!strcmp (text, "quit"))
      return 1;
  }
}

int main (int argc, char* const argv[])
{
  const char* const socket_name = argv[1];
  int socket_fd;
  struct sockaddr_un name;
  int client_sent_quit_message;

  //create the socket 
  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
  // indicate that this is a server
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_family, socket_name);
  bind (socket_fd, &name, SUN_LEN (&name));
  // listen for connection
  listen (socket_fd, 5);
  
  // repeatedly accept connections, spinning off one server() to deal with each client. 
  // continue until a client send a "quit" message
  do {
    struct sockaddr_un client_name;
    socklen_t client_name_len;
    int client_socket_fd;

    //accept a connection
    client_socket_fd = accept ( socket_fd, &client_name, &client_name_len);
    // handle the connection
    client_sent_quit_message = server (client_socket_fd);
    // close our end of the connection
    close (client_socket_fd);
  } 
  while(!client_sent_quit_message);
  // remove the socket file
  close (socket_fd);
  unlink (socket_name);

  return 0;
}

