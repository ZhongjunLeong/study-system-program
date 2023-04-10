#include <stdio.h>
#include <stdlib.h>
#define FNAME "/tmp/out"
#define BUFFSIZE 1024
#include <time.h>
int main()
{
	struct tm *tm;
	FILE *fp;
	char buf[BUFFSIZE];
	int count = 0;
	time_t stamp;
	fp = fopen(FNAME,"a+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	while(fgets(buf,BUFFSIZE,fp) != NULL)//makesure read 1 line 
	{
		count++;
	}
	while(1)
	{
		time(&stamp);
		tm = localtime(&stamp);
		fprintf(fp,"%-4d\n%d-%d-%d %d:%d:%d\n",++count,tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday+1,tm->tm_hour,tm->tm_min,tm->tm_sec);

		sleep(1);
    fflush(fp);	
	}



	fclose(fp);





	exit(0);
}
