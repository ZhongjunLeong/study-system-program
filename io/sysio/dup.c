#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FNAME  "/tmp/out"

int main()
{
  int fd;
  close(1);//stdout
  fd = open(FNAME,O_WRONLY|O_CREAT|O_TRUNC,0600);//file will open in 1
  if(fd < 0)
  {
    perror("open()");
    exit(1);
  }

 // close(1);//avoid other file occpy 1
 // dup(fd);///make fd duplication in 1
  dup2(fd,1);
  if(fd != 1)
  close(fd);//1 still have fd function


/***********/
  puts("hello");


  exit(0);
}
