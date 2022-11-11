#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_job(void * arg)
{
	int flags = 3;
	while(flags--){
		printf("thread 0x%x Running..%ds\n",(unsigned int)pthread_self(),flags);//pthread_t是无符号长整型
		//强转成无符号整型并且以十六进制的形式输出，方便观察
		sleep(1);
	}
	//使用return
	return (void *)8;
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
	printf("Call Join..\n");
	if((err = pthread_join(tid,&reval))>0){ //线程回收函数,阻塞回收,可以回收线程资源获取线程返回值或退出吗
		printf("Master thread Join Failed:%s\n",strerror(err));
		exit(0);
	}

	printf("Master 0x%x Join success , return value:%ld\n",(unsigned int)pthread_self(),(long int)reval);
	//64指针是8字节的，如果用int 和%d会报错，所以64位强转成长整型，long int
	return 0;
}
