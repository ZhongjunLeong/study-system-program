#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TIMESTRSIZE 1024

int main()
{
  struct tm *tm;
  time_t stamp;
  char timestr[TIMESTRSIZE];
  stamp =  time(NULL);
  tm = localtime(&stamp);
  strftime(timestr,TIMESTRSIZE,"Now:%Y-%m-%d",tm);
  puts(timestr);
  tm->tm_mday += 100;
  (void)mktime(tm);
  strftime(timestr,TIMESTRSIZE,"100 days later:%Y-%m-%d",tm);
  puts(timestr);

  exit(0);
}
