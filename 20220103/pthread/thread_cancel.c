#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_job(void * arg)
{
	while(1){
		pthread_testcancel();//调用此函数产生一次(系统调用),目的时检测处理cancel事件,没有其他附加功能
		//printf("thread 0x%x Running..\n",(unsigned int)pthread_self());
		//sleep(1);
	}
	//使用return
	return (void *)8;//只有正常走到这里，正常退出才会返回8，这里线程被取消了，返回-1
	//对取消的线程进行回收操作.会得到-1的返回值,通过-1可以辨别线程是被取消结束的
	//(我们在编写线程工作时,绝对不能用-1作为线程退出码,避免跟cancel混淆,无法判断)
}

int main(void)
{
	pthread_t tid; //线程id类型
	int err;
	void * reval = NULL;
	if((pthread_create(&tid,NULL,thread_job,NULL))>0){  //创建线程成功返回0,失败返回错误信号
		printf("Master thread Create Failed:%s\n",strerror(err));
		exit(0);
	}
	//pthread_self();//可以返回调用线程的线程id:
	printf("Master 0x%x Create thread 0x%x Success..\n",(unsigned int)pthread_self(),(unsigned int)tid);
	sleep(5);
	printf("Master 0x%x Send CANCEL..\n",(unsigned int)pthread_self());
	pthread_cancel(tid);
	printf("Master 0x%x Join..\n",(unsigned int)pthread_self());
	if((err = pthread_join(tid,&reval))>0){ //线程回收函数,阻塞回收,可以回收线程资源获取线程返回值或退出吗
		printf("Master thread Join Failed:%s\n",strerror(err));
		exit(0);
	}

	printf("Master 0x%x Join success , return value:%ld\n",(unsigned int)pthread_self(),(long int)reval);
	return 0;
}
