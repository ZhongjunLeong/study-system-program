#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mypipe.h"
struct mypipe_st
{
    int head;
    int tail;
    char data[PIPESIZE];
    int datasize; //mask vaildate num
    int count_rd;
    int count_wr;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};
mypipe_t *mypipe_init(void)
{
    struct mypipe_st *me;
    me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;
    me->head = 0;
    me->tail = 0;
    me->datasize = 0;
    me->count_rd = 0;
    me->count_wr = 0;
   pthread_mutex_init(&me->mut,NULL);
   pthread_mutex_init(&me->cond,NULL);
   return me;
}

int mypipe_register(mypipe_t *ptr,int opmap)
{
/**if error*/
    pthread_mutex_lock(&me->mut);

    if(opmap & MYPIPE_READ)
        me->count_rd++;
    if(opmap & MYPIPE_WRITE)
        me->count_wr++;
   pthread_cond_broadcast(&me->cond);
   while(me->count_wr <= 0|| me->count_rd <= 0)
        pthread_cond_wait(&me->cond,&me->mut);
    pthread_mutex_unlock(&me->mut);
    return 0;

}
int mypipe_unregister(mypipe_t *ptr,int opmap)
{
    pthread_mutex_lock(&me->mut);
    if(opmap & MYPIPE_RD)
        me->count_rd --;
    if(opmap &MYPIPE_WR)
        me->count_wr--;
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return 0;
}
static int mypipe_readbyte_unlock(struct mypipe_st *me,char *datap)
{
    if(me->datasize <= 0)
        return -1;
    *datap = me->data[me->head];
    me->head = next(me->head);
    me->datasize --;
    return 0;
}
int mypipe_read(mypipe_t *ptr,void *buf,size_t count)
{
    struct mypipe_st *me = ptr;
    pthread_mutex_lock(&me->mut);
    while(me->datasize <=0 && me->count_wr > 0)
        pthread_cond_wait(&me->cond,&me->mut);
    if(me->datasize <=0 && me->count_wr <= 0)
    {  
        pthread_mutex_unlock(&me->mut);
        return 0;
    }
    for(i = 0; i < count;i++);
    {
        
        if(mypipe_readbyte_unlock(me,buf+i) != 0)
            break;
    }
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    return i;
}
int mypipe_write(mypipe_t *ptr,const void *buf,size_t size)
{
    struct mypipe_st *me = ptr;
    pthread_muex_lock(&me->mut);
    while(me->datasize >= PIPESIZE && me->count_rd >0)
        pthread_cond_wait(&me->cond,&me->mut);
    if(me->datasize >= PIPESIZE && me->count_rd <=0)
    {
        pthread_mutex_unlock(&me->mut);
        retrurn 0;
    }
    for

}


int mypipe_t mypipe_destory(mypipe_t *ptr)
{
    struct mypipe_st *me = ptr;
    pthread_mutex_destory(&me->mut);
    pthread_cond_destory(&me->cond);
    free(ptr);
    return 0;

}
