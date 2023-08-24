#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

/*通过创建线程和映射内存来拷贝file文件的前5个字符串*/

//全局映射内存
char * ptr = 0;

void * thread_job(void * arg)
{
	char buff[10];
	int blocksize = 5;
	int pose = 0;
	snprintf(buff, blocksize+1, "%s",ptr+pose);
	printf("%s\n",buff);
	pthread_exit(0);
}

int main(void)
{
	int fd = open("file",O_RDONLY);
	int filesize = lseek(fd, 0, SEEK_END);
	
	if((ptr = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED){
		perror("mmap failed");
		exit(0);
	}
	
	pthread_t tid;
	int err;
	if((err = pthread_create(&tid,NULL,thread_job,NULL)) > 0){
		printf("thread create failed:%s\n",strerror(err));
		exit(0);
	}
	pthread_join(tid, NULL);
	munmap(ptr, filesize);
	close(fd);
	return 0;
}
