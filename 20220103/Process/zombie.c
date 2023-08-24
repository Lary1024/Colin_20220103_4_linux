#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

//僵尸进程+非阻塞回收例子

int main(void)
{
	pid_t pid;
	pid = fork();
	if(pid > 0){
		printf("Parent running %d ...\n",getpid());
		pid_t zpid;
		while((zpid = waitpid(-1,NULL,WNOHANG)) != -1){
			if(zpid > 1){
				printf("Parent wait success! zpid = %d\n",zpid);
			}else{
				printf("Parent running...\n");
				sleep(1);
			}
		}
		while(1)
			sleep(1);
	}else if(pid == 0){
		sleep(5);
		printf("child %d exit...\n",getpid());
		exit(0);
	}else{
		perror("fork call failed");
		exit(0);
	}
	return 0;
}
