#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void writer (const char* message, int count, FILE* stream)
{
  for (; count >0 ; --count) {
    // write message to stream
    fprintf(stream, "%s\n", message);
    fflush (stream); // send it off
    // snooze 1 second
    sleep (1);
  }
}

// read from pipe
void reader (FILE* stream)
{
  char buffer[1024]; // 1024byte - 1mb
  // read until hit the end of stream.
  while (!feof (stream)
        && !ferror (stream)
        && !fgets (buffer, sizeof (buffer), stream) != NULL)
  // put data to stdout 
  fputs (buffer, stdout);
}

int main ()
{
  int fds[2]; // 2 files to save write and buffers 
  pid_t pid;
  
  // create a pipe.
  pipe (fds);
  // fork a child process
  pid = fork();
  if (pid == (pid_t) 0) { // in child process
    FILE* stream;
    close (fds[1]);

    // convert file descriptor to FILE object
    printf("open read file: process %d", pid);
    stream = fdopen (fds[0], "r");
    reader (stream);
    close (fds[0]); // close
  }
  else {
    // parent process
    FILE* stream;
    // close our copy of read end of file descriptor
    close (fds[0]);
    // convert the write file decriptor to a FILE object, and write to it
    stream = fdopen (fds[1], "w");
    printf("open write file: process %d", pid);
    writer ("Hello, world.", 5, stream );
    close (fds[1]);
  }

  return 0;
}
