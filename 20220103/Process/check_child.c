#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

//子进程退出的校验方式

int main(void)
{
	int i = 0;
	pid_t pid;
	for(i; i < 2; i++){
		pid = fork();
		if(pid == 0){
			break;
		}
	}
	if(pid > 0){
		printf("Parent id:%d running...\n",getpid());
		int status;
		pid_t zpid;
		while((zpid = waitpid(-1,&status,WNOHANG)) != -1){
			if(zpid > 0){
				if((WIFEXITED(status))){//进程正常退出返回1
					printf("子进程为正常退出,退出码/返回值 = %d\n",WEXITSTATUS(status));//从status中将子进程的返回值或退出码提取并返回
				}
				if((WIFSIGNALED(status))){//进程正异常退出返回1
					printf("子进程为异常退出,退出码/返回值 = %d\n",WTERMSIG(status));//提取返回子进程的信号编号
				}
			}else if(zpid == 0){
			
			}
		}
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i == 0){
			sleep(5);
			printf("child id:%d exit\n",i);
			exit(0);
		}else if(i == 1){
			while(1){
				sleep(2);
				printf("child id:%d running..\n",i);
			}
		}
	}else{
		perror("Parent fork failed!");
		exit(0);
	}
	
	return 0;
}
