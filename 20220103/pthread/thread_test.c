#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <signal.h>

//全局映射内存
char * ptr = NULL;

void * thread_job(void * arg)
{
	char buf[10];
	int pos = 5;
	int blocksize = 5;
	int Sfd,Dfd; 
	bzero(buf,sizeof(buf));
	snprintf(buf,blocksize+1,"%s",ptr+pos);
	printf("%s\n",buf);
	//将数据写入目标文件时需要注意偏移量
	//Sfd = open()
	//lseek(dfd,pos,SEEK_SET);
	//write(dfd,buf,strlen(buf));
	pthread_exit(NULL);
}

int thread_cur(const char * File)
{

}

int main(void)
{
	int fd = open("file",O_RDONLY);
	int Fsize = lseek(fd,0,SEEK_END);
	int err;
	if((ptr = mmap(NULL,Fsize,PROT_READ,MAP_PRIVATE,fd,0))==MAP_FAILED)
	{
		perror("MMAP Failed");
		exit(0);
	}
	pthread_t tid;
	for(int i = 0; i < 10; i++){
		if((err = pthread_create(&tid,NULL,thread_job,NULL)) > 0){
			printf("Create Thread Error:%s..\n",strerror(err));
			exit(0);
		}
	}
	pthread_join(tid,NULL);
	munmap(ptr,Fsize);
	close(fd);
	
	return 0;
}
