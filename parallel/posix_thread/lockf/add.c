#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PROCNUM 20
#define FNAME "/tmp/out"
#define LINESIZE 1024
//static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static void *func_add(void )
{
    FILE *fp;
    int fd;
    char linebuf[LINESIZE];
    fp = fopen(FNAME,"r+");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    fd = fileno(fp);
    if(fd < 0)
    {
        perror("fileno()");
        exit(1);
    }
    lockf(fd,F_LOCK,0);
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
    sleep(1);
    fprintf(fp,"%d\n",atoi(linebuf)+1);

    fflush(fp);
    lockf(fd,F_ULOCK,0);
    fclose(fp);
    return ;
}

int main()
{

    int i,err;
    pid_t pid;
    for(i = 0; i < PROCNUM; i++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)//parent
        {
            func_add();
            exit(0);
        }

    }
    for(i = 0;i < PROCNUM;i++)
        wait(NULL);



    exit(0);
}
