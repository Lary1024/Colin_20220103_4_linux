#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define msg "hi can you hear me?"

int main(void)
{
	int fds[2];
	pid_t pid;
	pipe(fds);
	pid = fork();
	if(pid > 0){
		close(fds[0]);
		write(fds[1], msg, strlen(msg));
		printf("Parent:%d send msg success!\n",getpid());
		close(fds[1]);
		wait(NULL);
	}else if(pid == 0){
		close(fds[1]);
		char buffer[1024];
		bzero(buffer,sizeof(buffer));
		read(fds[0], buffer, sizeof(buffer));
		printf("child:%d read msg:%s\n",getpid(),buffer);
		close(fds[0]);
		exit(0);
	}else{
		perror("fork call failed");
		exit(0);
	}
	return 0;	
}
