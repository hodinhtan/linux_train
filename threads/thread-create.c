#include <pthread.h>
#include <stdio.h>

// Prints x's to stderr. The parameter is unsused. Does not return


void* print_xs (void* unused)
{
  while (1)
    fputc ('x', stderr);
  return NULL;
}

// Main program

int main()
{
  pthread_t thread_id;
  // create new thread. The new thread will run the print_xs

  pthread_create (&thread_id, NULL, &print_xs, NULL);
  while (1)
    fputc ('o', stderr);
  return 0;
}

