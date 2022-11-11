#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;
	int i = 0;
	for(i; i < 3; i++){
		pid = fork();
		if(pid == 0){
			break;
		}
	}

	if(pid > 0){
		printf("Parent Create Success.\n");
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("Child i (%d)...\n",i);
		while(1)
			sleep(1);
	}else{
		perror("fork call failed");
		exit(0);
	}
	return 0;
}
