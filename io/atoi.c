#include <stdio.h>
#include <stdlib.h>
int main ()
{
	
//	char str[] = "12345";
//	printf("%d\n",atoi(str));

	char buf[1024];
	int year = 2014,moth = 5,day = 13;
	sprintf(buf,"%d-%d-%d",year,moth,day);
	puts(buf);


	exit(0);
}

