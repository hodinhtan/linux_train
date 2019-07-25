#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

void print_time ()
{
  struct timeval tv;
  struct tm* ptm;
  char time_string[40];
  long milliseconds;

  // Obtain the time of day, and convert it to a tm struct
  gettimeofday (&tv, NULL);
  ptm = localtime (&tv.tv_sec);
  strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm );
  // Compute milliseconds from microseconds 
  milliseconds =  tv.tv_usec;
  // Print the formatted time , in seconds, followed by a decimal point and the milliseconds
  printf ("%s.%03ld\n", time_string, milliseconds);
}

int main()
{
  print_time();
  return 0;
}
