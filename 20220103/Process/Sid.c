#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//创建会话关系

int main(void)
{
	pid_t pid;
	int i = 0;
	for(i;i<3;i++){
		pid = fork();
		if(pid == 0)
			break;
	}
	if(pid > 0){
		printf("parent pid %d pgid %d sid %d\n",getpid(),getpgrp(),getsid(getpid()));
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("child pid %d pgid %d sid %d\n",getpid(),getpgrp(),getsid(getpid());
		if(i == 2)
		{
			//
			setsid();
			printf("Change child pid %d pgid %d sid %d\n",getpid(),getpgrp(),getsid(getpid()));
		}
		while(1)
			sleep(1);
	}else{
		perror("Failed");
	}
	return 0;
}

