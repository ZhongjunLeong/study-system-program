#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 1024
int readline(int fd,char *buf)//line char num
{
  int cnum;
  for(;;)
  {
    read(fd,&buf[cnum],1);
    cnum++;
    if(*(buf-1) == '\n')
    {
      break;
    }
  }
  return cnum;
}
int get_line_num(int fd,int *size)//get total line num &file size 
{
  size_t fdr;
  int i,lnum;
  char ch;
  while((fdr = read(fd,&ch,1)) > 0)//read line num
  {
      (*size)++;
          if(ch == '\n')
          {
              lnum++;
          }
  }
     
  return lnum;
}
int main(int argc,char**argv)
{
  int fd1,fd11;
  int llnum,lcnum;
  off_t d11,d10;
  char buf[BUFFSIZE];
  int size = 0,s;
  if(argc < 3)
  {
    fprintf(stdout,"usage 2 file\n");
    exit(1);
  }
  fd1 = open(argv[1],O_RDWR);
  if(fd1 == 0)
  {
    perror("open()");
    exit(1);
  }
  lcnum = readline(fd1,buf);
  llnum = get_line_num(fd1,&size);
  d10 = lseek(fd1,lcnum*10,SEEK_SET);
  fd11 = open(argv[1],O_RDONLY);
  if(fd11 < 0)
  {
     close(fd1);
    perror("open()");
    exit(1);
  }

  d11 = lseek(fd11,lcnum*11,SEEK_SET);
  s = d11 - d10;
    size_t ch;
    ssize_t fd11r,fd1w;
  while(1)
  {

    fd11r = read(fd11,&ch,1);
    if(fd11r < 0)
    {
      perror("read()");
      exit(1);
    }
    if(fd11r == 0)
    {
      break;
    }
      
    fd1w = write(fd1,&ch,1);
  }
  ftruncate(fd1,size-s);

  close(fd1);
  close(fd11);


  exit(0);
}
