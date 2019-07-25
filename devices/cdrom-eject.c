#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
  // Open a file desc to device specified on the command line 
  int fd = open (argv[1], O_RDONLY);
  // Eject the CD-ROM
  ioctl (fd, CDROMEJECT);
  // close 
  close (fd);

  return 0;
}
