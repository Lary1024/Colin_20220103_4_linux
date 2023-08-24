#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//查看进程间关系

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
		printf("parent pid %d pgid %d\n",getpid(),getpgrp());
		while(1)
			sleep(1);
	}else if(pid == 0){
		if(i == 2)
		{
			printf("First child pid %d pgid %d\n",getpid(),getpgrp());
			sleep(10);
			setpgid(getpid(),getpid());
			printf("Change child pid %d pgid %d\n",getpid(),getpgrp());
			while(1)
				sleep(1);
		}
		printf("child pid %d pgid %d\n",getpid(),getpgrp());
		while(1)
			sleep(1);
	}else{
		perror("Failed");
	}
	return 0;
}

