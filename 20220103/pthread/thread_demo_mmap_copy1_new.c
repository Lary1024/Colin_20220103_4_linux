#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <pthread.h>

//全局映射内存
char * ptr = NULL;
//全局块大小
int blocksize;
//文件描述结构体
struct file_fd_size 
{
	int fd;
	int filesize;
}File;

//
#define THREAD_NUMBER 10

//获取文件描述结构体
struct file_fd_size mmap_size(const char * filename)
{
	struct file_fd_size File;
	File.fd = open(filename,O_RDONLY);
	File.filesize = lseek(File.fd, 0, SEEK_END);
	return File;
}

//映射内存
void * pthread_mmap(struct file_fd_size File)
{
//	int fd = open("1.png",O_RDONLY);
//	int filesize = lseek(fd, 0,SEEK_END);
	ptr = mmap(NULL, File.filesize, PROT_READ, MAP_PRIVATE, File.fd, 0);
	return ptr;
}

//拷贝文件大小计算
int pthread_cur(struct file_fd_size File)
{
	int cur;
	if(File.filesize % THREAD_NUMBER == 0)
		cur = File.filesize / THREAD_NUMBER;
	else
		cur = File.filesize / THREAD_NUMBER + 1;
	return cur;
}

//线程函数:拷贝
void * pthread_job(void * arg)
{
	int i = *(int *)arg;
	int pos = i * blocksize;
	int ofd = open("2.png", O_RDWR|O_CREAT, 0664);//打开目标文件，文件不存在则创建
	char buff[blocksize];
	
	printf("bufflen:%d\n",(int)strlen(buff));
	printf("Copy Thread 0x%x , i = %d POS = %d, blocksize = %d\n",(unsigned int)pthread_self(),i,pos,blocksize);
	bzero(buff, blocksize);
//	snprintf(buff, blocksize + 1, "%s", ptr + pos);
	memcpy(buff, ptr + pos, blocksize);
	lseek(ofd, pos, SEEK_SET);
	printf("bufflen:%d\n",(int)strlen(buff));
	int size = write(ofd, buff, strlen(buff));
	printf("%d\n",size);
	close(ofd);
	pthread_exit(NULL);
	
}

//线程创建
int thread_create()
{
	pthread_t tids[THREAD_NUMBER];
	int err;
	int i = 0;
	for(i = 0; i < THREAD_NUMBER; i++){
		if((err = pthread_create(&tids[i], NULL, pthread_job, (void *)&i)) > 0){
			printf("create thread failed:%s",strerror(err));
		}
		usleep(10000);
	}

	while(i--){
		pthread_join(tids[i],NULL);
	}
	return 0;
}

int main(void)
{
	//获取文件描述符
	File = mmap_size("1.png");
	//映射内存
	ptr = pthread_mmap(File);
	//拷贝大小计算
	blocksize = pthread_cur(File);
	//线程创建
	thread_create();
	munmap(ptr, File.filesize);
	printf("Thread Copy success!!\n");
	
	return 0;
}
