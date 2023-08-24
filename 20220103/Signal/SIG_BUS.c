#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

//总线错误的例子

int main(void)
{
	int fd = open("BUSFILE", O_RDWR);

	int * ptr = NULL;

	int mapsize = 4096;
	//映射失败,申请了映射内存,但是没有与映射文件建立关联,后续访问隐射内存的时候会失败,产生总线错误,进程终止
	
	if((ptr = mmap(NULL, mapsize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0))==MAP_FAILED)
	{
		perror("mmap failed");
		exit(0);
	}
	ptr[0] = 0x33323130;
	munmap(ptr,mapsize);
	close(fd);

	return 0;
}
