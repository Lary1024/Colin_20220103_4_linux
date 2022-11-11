#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

/*通过修改线程属性,提高线程的创建数量,将默认的8M线程改为1M*/

//0x100000表示1M的意思，十六进制对于十进制就是1M
#define STACK_SIZE 0x100000

void * thread_job(void * arg)
{
	while(1)
		sleep(1);
}

int main(void){
	
	int flags = 0;
	pthread_attr_t Attr;
	pthread_attr_init(&Attr);
	//查一下默认属性中的栈地址栈大小
	void * stackaddr = NULL;
	size_t stacksize;
	int err;
	pthread_t tid;
	pthread_attr_getstack(&Attr,&stackaddr,&stacksize);
	printf("Attr DFL StackAddr = %p Stacksize=%d\n",stackaddr,stacksize);
	while(1){
		//申请指定的大小的栈空间
		if((stackaddr = (void *)malloc(STACK_SIZE))==NULL){
			perror("Malloc Stack Addr Error");
			pthread_attr_destroy(&Attr);
			exit(0);
		}
		//直接将栈地址和栈大小赋予属性中
		stacksize = STACK_SIZE;
		pthread_attr_setstack(&Attr,stackaddr,stacksize);
		if((err = pthread_create(&tid,&Attr,thread_job,NULL))>0){
			printf("Create Thread Error : %s\n",strerror(err));
			pthread_attr_destroy(&Attr);
			exit(0);
		}
		printf("Create Thread Number = %d\n",++flags);
	}
	pthread_attr_destroy(&Attr);
	return 0;
}
