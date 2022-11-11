#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

//创建进程以及进程工作分区

int main(void)
{
	pid_t pid;
	pid = fork();

	if(pid > 0){
		printf("Parent Running...\n");
	}else if(pid == 0){
		printf("Child Running...\n");
		exit(0);
	}else{
		perror("Fork Call Failed");
		exit(0);
	}
	printf("Running...\n");
	while(1)
		sleep(1);
	return 0;
}

