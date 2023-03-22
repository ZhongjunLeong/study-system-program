#include <stdio.h>
#include <stdlib.h>
/*缓冲区的作用：大多数情况下使好事，合并系统调用
 * 
 * 行缓冲IOLBF：换行时刷新；满了的时候刷新；强制刷新（标准输出是这样的，因为是终端设备）
 *
 * 全缓冲IOFBF：满了的时候刷新；强制刷新（默认，只要不是终端设备）
 *
 *无缓冲IONBF：如stderr，需要立即输出的内容
 *
 *可修改：setvbuf函数//光标停在要man的函数中间，命令行模式shift+k，可进入man 
 *setvbuf（）可用在任何缓冲模式下修改
 *
 * */
int main()
{
	int i;
	printf("before while()");
	fflush(stdout);
	while(1);
	printf("after while");
	fflush(NULL);
	exit(0);
}
