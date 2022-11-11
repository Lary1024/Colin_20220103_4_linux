#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

void * thread_job(void * arg)
{
	//普通线程的代码区
	int i = *(int *)arg;
	printf("thread Running tid = 0x%x i = %d...\n",(unsigned int)pthread_self(),i);
	while(1)
		sleep(1);
}

int main(void)
{
	//main函数中是主线的代码区
	pthread_t tid[2];
	int i;
	for(i=0; i<2; i++){
		pthread_create(&tid[i],NULL,thread_job,(void *)&i); //因为是取地址传递，所以要先睡一会，避免取到相同的值
		usleep(10000);
	}

	printf("Master thread tid = 0x%x Create Success..\n",(unsigned int)pthread_self());
	while(1)
		sleep(1);

}
