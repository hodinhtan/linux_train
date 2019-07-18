#include <pthread.h>
#include <stdio.h>

// compute successive prime numbers. reutrn Nth prime number, 
// where N is value pointed to by *ARG

void* compute_prime (void* arg)
{
  int candidate = 2;
  int n = *((int*) arg);

  while (1) {
    int factor;
    int is_prime = 1;

    // test primality by successive division
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0) {
        is_prime = 0;
        break;
      }

    // Is this the prime number we're looking for?
    if (is_prime) {
      if (--n == 0)
        return (void*) candidate;
    }
    ++candidate;
  }
  return NULL;
}


  int main()
  {
    pthread_t thread;
    int which_prime = 5000;
    int prime;
    
    // Start computing thread, up to the 5000th prime number
    pthread_create (&thread, NULL, &compute_prime, &which_prime);
    // Do some other work here ...
    // Wait for the prime number thread to complete, and get the result
  pthread_join (thread, (void*) &prime);
  // Print the largest prime it computed
  printf("The %dth prime number is %d. \n", which_prime, prime);

  return 0;
}
