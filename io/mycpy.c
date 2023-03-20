#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fps,*fpd;
	int ch;
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
	while(1)
	{
		ch = fgetc(fps);//read from scrfile
		if(ch == EOF)
			break;
		fputc(ch,fpd);//read from scrfile and put it to destfile
	}

	fclose(fpd);
	fclose(fps);
	exit(0);
}
