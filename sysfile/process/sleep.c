#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  puts("begin");
  fflush(NULL);
  pid = fork();
  if(pid < 0)
  {
    perror("forl()");
    exit(1);
  }
  if(pid ==0)
  {
     execl("/bin/sleep","sleep","100",NULL);

     perror("execl()");
     exit(1);
  }
  wait(NULL);//parent wait get child id
  puts("end");
  exit(0);
}
