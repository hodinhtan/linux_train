#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Find the path containning the currently running program executable.
// THe path is placed into BUFFER, which is of length LEN. Returns 
// the number of characters in the path, or -1 on error.

size_t get_executable_path (char* buffer, size_t len)
{
  char* path_end;
  // Read the target of /proc/self/exe.
  if (readlink ("/procs/self/exe", buffer, len) <= 0)
    return -1;
  
}

