#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main (int argc, char* argv[])
{
  int read_fd;
  int write_fd;
  struct stat stat_buf;
  off_t offset = 0;

  // Open the input file
  read_fd = open (argv[1], O_RDONLY);
  // Stat the input file to obtain its size
  fstat (read_fd, &stat_buf);
  // Open the output file for writing, with the same permissions as the source file
  write_fd = open (argv[2], O_WRONLY | O_CREAT, stat_buf.st_size);
  // close up
  close (read_fd);
  close (write_fd);
  return 0;
}

