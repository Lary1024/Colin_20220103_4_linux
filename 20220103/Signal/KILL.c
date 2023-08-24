#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// 此为函数触发信号的例子,自己来实现kill命令

int main(int argc, char ** argv) // 字符串数组
{
	// ./KILL 9 1000
	if(argc < 3){ // 需要三个参数,函数名,进程pid,要发送的信号
		printf("Error , TryAgain..\n");
		exit(0);
	}		
	kill(atoi(argv[2]), atoi(argv[1])); // kill(pid_t pid, int sigNO) 此函数可以向任意进程发送任意信号
	return 0;
}

