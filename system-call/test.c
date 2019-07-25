#include <stdio.h>
#include <unistd.h>

int main()
{
  printf ("%u", getpagesize());
  return 0;
}
