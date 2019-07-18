#include <stdio.h>

int main ()
{
  int p = 5;
  int* a = &p;

  printf("%d - %p \n", p, &p);
  printf("%d - %p \n", *a, a);
}
