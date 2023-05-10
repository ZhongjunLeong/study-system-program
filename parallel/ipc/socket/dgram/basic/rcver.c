#include <stdio.h>
#include <stdlib.h>
#include "proto.h"

int main()
{
    int sd;
    struct sockaddr_in laddr;
   sd = socket(AF_INET,SOCK_DGRAM,0/*IPPROTO_UDP*/);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi("RCVPORT"));
    inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr);
    if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }
    while(1)
    {
        recvfrom();
        printf();
    }

    close(sd);

    exit(0);
}
