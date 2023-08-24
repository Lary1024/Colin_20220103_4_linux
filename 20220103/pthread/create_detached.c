#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

/*通过修改线程属性,直接创建出分离态线程*/

void * thread_jobs(void * arg)
{
	printf("thread 0x%x Running..\n",(unsigned int)pthread_self());
	while(1)
		sleep(1);
	return NULL;
}

int main(void){

	int detachstate;
	pthread_t tid;
	pthread_attr_t Attr;
	pthread_attr_init(&Attr); //初始化线程属性
	pthread_attr_getdetachstate(&Attr,&detachstate); //查看默认属性中的退出状态
	if(detachstate == PTHREAD_CREATE_JOINABLE)
		printf("thread DFL Attr, ExitState = JOINABLE\n");
	else
		printf("thread DFL Attr, ExitStare = DETACHED\n");
	
	pthread_attr_setdetachstate(&Attr,PTHREAD_CREATE_DETACHED); //设置属性中的退出状态
	printf("Set DETACHED Success..\n");
	//创建分离线程
	pthread_create(&tid,&Attr,thread_jobs,NULL);
	//尝试回收,如果回收失败,表示分离线程正确
	int err;
	if((err = pthread_join(tid,NULL))>0)
	{
		printf("Join Failed:%s\n",strerror(err));
	}
	//属性释放
	pthread_attr_destroy(&Attr);
	return 0;



}
