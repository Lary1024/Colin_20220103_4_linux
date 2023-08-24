#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//进程重载

int main()
{
	pid_t pid;
	pid = fork();

	if(pid > 0){
		printf("Parent i:%d\n",getpid());
		while(1)
			sleep(1);
	}else if(pid == 0){
		printf("Child i:%d\n",getpid());
		sleep(5);
		execlp("firefox","firefox","www.baidu.com",NULL);
	}else{
		perror("fork call failed");
		exit(0);
	}
	
}
