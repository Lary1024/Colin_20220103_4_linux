#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

// 实现获取并打印未决信号集,查看信号屏蔽

void Print_Pset(sigset_t pset)
{
	int signum;
	for(signum = 1; signum < 32; signum++){ // 软件工程师一般只管制前1-31个信号
		if((sigismember(&pset,signum))==1) // 获取信号集中某个信号的位码,并直接返回
			putchar('1');
		else
			putchar('0');
	}
	putchar('\n');
}

int main(void)
{
	sigset_t new_set,old_set,pset;
	sigemptyset(&new_set); // 将信号集中所有为置为1
	sigaddset(&new_set,SIGINT); // 将信号集中指定位变为1
	sigaddset(&new_set,SIGQUIT); // 
	sigprocmask(SIG_SETMASK,&new_set,&old_set);//替换进程屏蔽字信号集

	while(1){
		sigpending(&pset); // 每间隔1s获取一次未决信号 (获取传出进程的未决信号集)
		Print_Pset(pset); // 遍历打印未决(遍历pset信号集,结合sigismember函数,输出位码)
		sleep(1);
	}
}
