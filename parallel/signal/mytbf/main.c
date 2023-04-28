#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include "mytbf.h"
#define CPS  10
#define BUFFSIZE 1024
#define BURST  100
int main(int argc, char **argv)
{
	int sfd,dfd  = 1;
	char buf[BUFFSIZE];
	int len,ret,pos;
  int count = 0;
  int size;
  mytbf_t *tbf;
	if(argc < 2)
	{
		fprintf(stderr,"usage..\n");
		exit(1);
	}
tbf = mytbf_init(CPS,BURST);
  if(tbuf == NULL)
  {
    fprintf(stderr,"mytbf_init() dailed\n");
    exit(1);
  }
  do
  {   
	  sfd = open(argv[1],O_RDONLY);
  	if(sfd < 0)
	  {
      if(errno != EINTR)
      {
		    perror("open()");
		    exit(1);
	    }
    }
   }while(sfd < 0);
	while(1)
	{
    size = mytbf_fetchtoken(tbf,BUFSIZE);
    if(size < 0)
    {
      fprintf(stderr,"mytbf_fetchtoken():%s\n",strerror(-size));
      exit(1);
    }
	while( (len = read(sfd,buf,size)) < 0)
  {
		 if(errno == EINTR)
        continue;
			  perror("read()");
			  break;
  }
		if(len == 0)
			break;
    //  count++;
    if(size - len >0)
      mytbf_returntoken(tbf,size-len);
		pos = 0;
		while(len > 0)
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
    sleep(1);//sleep 1s
	}
//  printf("%d\n",count);
  mytbf_destory(tbf);
	close(sfd);
	exit(0);
}
