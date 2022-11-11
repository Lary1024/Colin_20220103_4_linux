#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

//union sigval , 发送的联合体数据包 , sival_int , sival_ptr
//siginfo_t info , 接收数据包的捕捉函数参数 si_int , si_ptr

void Parent_sig(int signum , siginfo_t * info , void * arg)
{
	//info 结构体可以接受,其他进程信号携带的数据
	printf("Parent Recv Number:%d\n",info->si_int);
	union sigval val;
	val.sival_int = ++(info->si_int)
	sigqueue(getpid()+1,SIGUSR1,val);
	usleep(100000);
}

void 
