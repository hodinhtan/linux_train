#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// write TEXT to the socket given by file desciptor SOCKET_FD

void write_text (int socket_fd, const char* text)
{
  // wirte the number of bytes in the string, including NUL-termination
  int length = strlen (text) + 1;
  write (socket_fd, &length , sizeof (length));
  //write the string
  write (socket_fd, text, length);
}

int main (int argc, char* const argv [] )
{
  const char* const socket_name = argv[1];
  const char* const message = argv[2];
  int socket_fd;
  struct sockaddr_un name;

  // create the socket 
  socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
  // store the serve's name in the socket address 
  name.sun_family = AF_LOCAL;
  strcpy (name.sun_path, socket_name);
  // connect the socket 
  connect ( socket_fd, &name, SUN_LEN (&name));
  // write the text on the command line to the socket
  write_text (socket_fd, message);
  close (socket_fd);

  return 0;
}
