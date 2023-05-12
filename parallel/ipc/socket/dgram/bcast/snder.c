#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "proto.h"
int main ( )
{
    int sd;
    struct msg_st sbuf;
    struct sockaddr_in raddr;
/*    if(argc < 2)
    {
        fprintf(stderr,"usage..\n");
        exit(1);
    }
  */
  sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }
    int val = 1;
   if(setsockopt(sd,SOL_SOCKET,SO_BROADCAST,&val,sizeof(val)) < 0)
   {
        perror("setsockopt()");
        exit(1);
   }

   strcpy(sbuf.name,"alen");
   sbuf.math = htonl(rand()%100);
   sbuf.chinese = htonl(rand()%100);
   raddr.sin_family = AF_INET;
   raddr.sin_port = htons(atoi(RCVPORT));
    inet_pton(AF_INET,"255.255.255.255",&raddr.sin_addr);
   if(sendto(sd,&sbuf,sizeof(sbuf),0,(void *)&raddr,sizeof(raddr)) < 0)
   {
        perror("sendo()");
        exit(1);
   }
   puts("ok");
    close(sd);



    exit(0);
}

