#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

// 信号忽略

int main(void)
{
	struct sigaction new_act, old_act; // 信号行为结构体
	new_act.sa_handler = SIG_IGN; 
	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask); //将信号集中的所有为初始化为0
	sigaction(SIGINT, &new_act, &old_act); //替换进程屏蔽字信号集

	while(1)
			sleep(1);	
	return 0;
}

