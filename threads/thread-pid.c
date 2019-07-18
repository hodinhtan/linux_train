#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_function (void* arg)
{
  fprintf (stderr, "child thread pid is %d\n", (int) getpid ());
  // spin forever
  while (1);
  return NULL;
}

int main()
{
  pthread_t thread;
  fprintf (stderr, "thread value 1 %ld \n", thread);
  fprintf (stderr, "main thread is %d\n", (int) getpid());
  pthread_create(&thread, NULL, &thread_function, NULL);
  fprintf (stderr, "thread value2 %ld \n", thread);
  fprintf (stderr, "function thread value %p \n", thread_function);
  // spin forever
  while (1);
  return 0;
}
