#ifndef MYPIPE_H__
#define MYPIPE_H__
#define MYPIPE_READ  0X00000001UL
#define MYPIPE_WRITE 0X00000002UL
#define PIPESIZE  1024
typedef void mypipe_t;

mypipe_t *mypipe_init(void);
int mypipe_register(mypipe_t *,int opmap);
int mypipe_unregister(mypipe_t *,int opmap);
int mypipe_read(mypipe_t *,void *buf,size_t count);
int mypipe_write(mypipe_t *,const void *buf,size_t size);


int mypipe_t mypipe_destory(mypipe_t *);












#endif
