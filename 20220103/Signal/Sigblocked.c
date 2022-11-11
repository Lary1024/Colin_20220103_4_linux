#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>

//屏蔽信号(SIGINT)的例子

int main(void)
{
	//屏蔽SIGINT
	sigset_t new_set , old_set; // 信号集类型
	sigemptyset(&new_set); // 将信号集所有位初始化为0
	sigaddset(&new_set, SIGINT); // 将信号集指定信号的位码设置1
	sigaddset(&new_set, SIGQUIT);
	sigaddset(&new_set, SIGKILL);
	sigprocmask(SIG_SETMASK, &new_set, &old_set); //覆盖新的传出旧的
	
	while(1)
		sleep(1);
		
	return 0;
}
