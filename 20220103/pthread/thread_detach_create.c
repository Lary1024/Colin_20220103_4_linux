#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>

/*通过修改线程属性，直接创建出分离态线程*/

void * pthread_jobs(void * arg)
{
	printf("pthread 0x%x Running..\n",(unsigned int)pthread_self());
	int i = 5;
	while(i--)
		sleep(1);
	pthread_exit(0);
}


int main(void)
{
	pthread_t tid;
	int detachstate;
	pthread_attr_t Attr;
    pthread_attr_init(&Attr);
	pthread_attr_getdetachstate(&Attr, &detachstate); // 查看线程创建默认属性中的状态
	if(detachstate == PTHREAD_CREATE_DETACHED){
		printf("Pthread EFL Attr : DETACHED\n");
	}else{
		printf("Pthread EFL Attr : JOINABLE\n");
	}

	//设置属性中退出状态
	pthread_attr_setdetachstate(&Attr, PTHREAD_CREATE_DETACHED);
	printf("Set DETACHED success\n");
	int err;
	//创建分离线程
	if((err = pthread_create(&tid, &Attr, pthread_jobs, NULL)) > 0){
		printf("pthread_create error:%s\n",strerror(err));	
		exit(0);
	}
	//尝试回收，如果回收失败，表示创建分离线程成功
	if((err = pthread_join(tid, NULL)) > 0){
		printf("join pthread failed:%s\n",strerror(err));
	}else{
		printf("join pthread success\n");
	}
	pthread_attr_destroy(&Attr);

	return 0;
}
