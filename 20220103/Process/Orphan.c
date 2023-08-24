#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

//孤儿进程例子

int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid > 0){ //让父进程崩掉
		printf("Parent PID %d , Runing...\n",getpid());
		char * str = "xxxx";
		str[0] = 'x';
		while(1)
				sleep(1);
	}else if(pid == 0){
		while(1){
			printf("Child PID %d,Runing...\n",getpid());
			sleep(1);
		}
	}else{
		perror("Failed");
		exit(0);
	}
	return 0;
}
