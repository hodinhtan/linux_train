#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int fds[2];
  pid_t pid;

  // create a pipe. File descriptor for the two ends of the pipe are palced in fds
  pipe (fds);
  // fork a child
  pid = fork();

  if (pid == (pid_t) 0) {
    close (fds[1]); // close fds for write
    // connect the read end of pipe to standard input
    dup2 (fds[0], STDIN_FILENO);
    // replace the child process with the "sort" program
    execlp ("sort", "sort", 0);
  } else {
    // This is parent process
    FILE* stream;
    // cose our copy of the read end of file desciptor 
    close (fds[0]);

    stream = fdopen (fds[1], "w");
    fprintf( stream, "This is a Test \n");
    fprintf( stream, "Hello, world!\n");
    fprintf( stream, "The program is great\n");
    fprintf( stream, "This is a Test End \n");
    fflush (stream);
    close (fds[1]);
    // wait for the clid process to finish
    waitpid (pid, NULL, 0);
  }

  return 0;
}
