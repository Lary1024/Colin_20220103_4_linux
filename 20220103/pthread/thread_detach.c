#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

void * tjob(void * arg)
{
	pthread_detach(pthread_self());
	printf("THREAD 0x%x Set Detached Success..\n",(unsigned int)pthread_self());
	while(1)
		sleep(1);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,tjob,NULL);
	sleep(0); //切换线程
	int err;
	if((err = pthread_join(tid,NULL))>0){
		printf("Join Error:%s\n",strerror(err));  //报错无效的参数
		//因为线程分离设置成功，join指定的线程是分离的线程，分离的线程内核是不允许其他人回收的，是由系统回收的
		exit(0);
	}
	return 0;
}
