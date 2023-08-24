#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

void sig_alarm(int n){
	//空调用
}

unsigned int SLEEP(unsigned int seconds)
{
	unsigned int reval;
	//信号捕捉
	struct sigaction act,oact;
	act.sa_handler = sig_alarm;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act,&oact);
	//信号屏蔽
	sigset_t set,oset;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	sigprocmask(SIG_SETMASK,&set,&oset);
	

	reval = alarm(seconds);
	sleep(3);
	//pause();
	sigsuspend(&act.sa_mask);//临时解除对SIGALRM的屏蔽并挂起进程

	return reval;
}

int main(void){
	while(1)
	{
		printf("sleep two secons.\n");
		SLEEP(2);
	}

}
