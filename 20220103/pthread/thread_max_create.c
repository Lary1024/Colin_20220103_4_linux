#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

//线程创建的最大值，以及线程错误处理的方式

void * thread_jobs(void * arg)
{
	while(1)
		sleep(1);
}

int main(void)
{
	pthread_t tid;
	int err;
	int flags = 0;
	while(1){
		if((err = pthread_create(&tid,NULL,thread_jobs,NULL))>0){
			printf("thread create Failed:%s\n",strerror(err));  //所有线程函数都这样错误处理
			exit(0); //整个进程退出
		}
		printf("thread number [%d]..\n",++flags);
	}
	return 0;
}
