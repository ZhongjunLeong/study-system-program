#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**date +%s
*
*/

int main()
{
  printf("begin\n");
  fflush(NULL);
  execl("/bin/date","date","+%s",NULL);

  perror("execl()");
  exit(1);
  puts("end");
  exit(0);
}
