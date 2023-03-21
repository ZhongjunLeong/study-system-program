#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
int main(int argc, char **argv)
{
	FILE *fps,*fpd;
//	int ch;
	char buf[BUFSIZE];
	int n;
	if(argc < 3)
	{
		fprintf(stderr,"usage:%s <src_file> <dest_file>\n",argv[0]);
		exit(1);
	}
	fps = fopen(argv[1],"r");//open scrfile &must exit
	if(fps == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	fpd = fopen(argv[2],"w");//open destfile
	if(fpd == NULL)
	{
		fclose(fps);
		perror("fopen()");
		exit(1);
	}
/*	while(1)
	{
		ch = fgetc(fps);//read from scrfile
		if(ch == EOF)
			break;
		fputc(ch,fpd);//read from scrfile and put it to destfile
	}
*/
	while((n = fread(buf,1,BUFSIZE,fps)) > 0)//make sure read bufsize number
	{
		fwrite(buf,1,n,fpd);
	}
	fclose(fpd);
	fclose(fps);
	exit(0);
}
