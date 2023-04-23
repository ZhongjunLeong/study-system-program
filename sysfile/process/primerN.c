#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define LEFT 30000000
#define RIGHT 30000200
#define N 3
int main()
{
  pid_t pid;
  int i,j,mark,n;
 for(n = 0;n < N;n++)//parent
 {
    pid = fork();
    if(pid < 0)
    {
      perror("fork()");
      exit(1);
    }
    if(pid == 0 )//child
    {
      for(i = LEFT+n; i <= RIGHT; i+=N)
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
          printf("[%d]%d is a promer\n",n,i);
//        sleep(1000);
         // exit(0);
       }
       exit(0);
    }
  }
  for(n = 0; n < N;n++)
  {
     // wait(&st);
     wait(NULL);//dont care child status
   }


  exit(0);
}