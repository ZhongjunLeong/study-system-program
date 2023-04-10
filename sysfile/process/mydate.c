#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TIMESTRSIZE 1024
#include <string.h>
#include <unistd.h>
#define FMSIZE 1024
/*
*-y:year
*-m:moth
*-d:day
*-H:hour
*-M:minute
*-S:second
**/
int main(int argc,char**argv)
{
  struct tm *tm;
  FILE *fp;
  time_t stamp;
  char timestr[TIMESTRSIZE];
  int c;
  char fmstr[FMSIZE];
  fmstr[0] = '\0';
  stamp =  time(NULL);
  tm = localtime(&stamp);
  while(1)
  {
    c = getopt(argc,argv,"H:MSy:md");//if have option,then write : inbehind//when optstring before is '-',mean can get nonoption,and return 1
    if(c < 0)
      break;
    switch(c)
    {
 /*      case 1:
      if(fp == stdout)//all option save in the first file
      {
          fp = fopen(argv[optind-1],"w");//when get nonoption return 1 and then getopt goito next option
          if(fp == NULL)
          {
           perror("fopen()");
           fp = stdout;
          }
       } 
        break;
  */
    case 'H':
        if(strcmp(optarg,"12") == 0)
         strncat(fmstr,"%I(%P) ",FMSIZE);
         else if(strcmp(optarg,"24")== 0)
         strncat(fmstr,"%H ",FMSIZE);
         else
          fprintf(stderr,"invaild argument over h");
          break;
      case 'M':
          strncat(fmstr,"%M ",FMSIZE);
          break;
      case 'S':
          strncat(fmstr,"%S",FMSIZE);
          break;

      case 'y':
        if(strcmp(optarg,"4") == 0)
         strncat(fmstr,"%Y ",FMSIZE);
         else if(strcmp(optarg,"2")== 0)
         strncat(fmstr,"%y ",FMSIZE);
         else
          fprintf(stderr,"invaild argument over y\n");
          break;
      case 'm':
          strncat(fmstr,"%m ",FMSIZE);
          break;
      case 'd':
          strncat(fmstr,"%d ",FMSIZE);
          break;
      default:
        break;
   }

 }
  strncat(fmstr,"\n",FMSIZE);
  strftime(timestr,TIMESTRSIZE,fmstr,tm);
  fputs(timestr,fp);
 // tm->tm_mday += 100;
 // (void)mktime(tm);
 // strftime(timestr,TIMESTRSIZE,"100 days later:%Y-%m-%d",tm);
 // puts(timestr);
//  if(fp != stdout)
 // fclose(fp);
  exit(0);
}
