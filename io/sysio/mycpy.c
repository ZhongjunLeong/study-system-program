#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 1024
int main(int argc, char **argv)
{
	int sfd,dfd;
	char buf[BUFFSIZE];
	int len,ret,pos;
  int count = 0;
	if(argc < 3)
	{
		fprintf(stderr,"usage..\n");
		exit(1);
	}

	sfd = open(argv[1],O_RDONLY);
	if(sfd < 0)
	{
		perror("open()");
		exit(1);
	}
	dfd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0600);//直写，没有就创建否则就截断，创建文件就给一个权限
	if(dfd < 0)
	{
		close(sfd);
		perror("open()");
		exit(1);
	}
	while(1)
	{
		len = read(sfd,buf,BUFFSIZE);
		if(len < 0)
		{
			perror("read()");
			break;
		}
		if(len == 0)
			break;
      count++;
		pos = 0;
		while(len > 0)//确保写入成功，如len=10，但只写入3个，这是ret仍然大于0；
		{
			ret = write(dfd,buf+pos,len);
			if(ret < 0)
			{
				perror("write()");
				exit(1);
			}
			pos += ret;
		len -= ret;//?
    }
	}
  printf("%d\n",count);
	close(dfd);
	close(sfd);
	exit(0);


}
