#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200
int main()
{
  pid_t pid;
  int i,j,mark;
  for(i = LEFT; i <= RIGHT; i++)//parent
  {
    pid = fork();
    if(pid < 0)
    {
      perror("fork()");
      exit(1);
    }
    if(pid == 0 )//child
    {
      mark = 1;

       for(j = 2; j < i/2; j++)
      {
          if( i % j == 0)
        {
            mark = 0;
            break;

        }
      }
        if(mark)
        printf("%d is a promer\n",i);
        sleep(1000);
        exit(0);
      }
 }




  exit(1);
}
