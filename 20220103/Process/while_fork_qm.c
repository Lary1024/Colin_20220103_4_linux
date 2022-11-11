#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int i = 0;
	for(i; i < 3; i++){
		pid = fork();
			if(pid == 0)
				break;
	}

	if(pid > 0){
		printf("Parent pid=%d\n",getpid());
	}else if(pid == 0){
		if(i == 0){
			printf("Child i=%d aa\n",i);
			while(1)
				sleep(1);
		}else if(i == 1){	
			printf("Child i=%d bb\n",i);
			while(1)
				sleep(1);
		}else{
			printf("Child i=%d cc\n",i);
			while(1)
				sleep(1);
		}
	}else{
		perror("create pid failed");
		exit(0);
	}

	while(1)
		sleep(1);
	
	return 0;
}
