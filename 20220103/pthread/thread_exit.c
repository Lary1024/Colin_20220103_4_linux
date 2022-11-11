#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>

void * thread_job(void * arg)
{
	printf("thread Running..\n");
	pthread_exit((void *)16);
}

int main(void)
{
	pthread_t tid;
	void * reval = NULL;
	pthread_create(&tid,NULL,thread,);

}
