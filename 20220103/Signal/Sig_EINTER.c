#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

void Sig_do(int n)
{
	printf("捕捉 %d SIGINT ...\n",n);
}

int main(void)
{
	struct sigaction act,oact;
	act.sa_handler = Sig_do;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT,&act,&oact);
	char buf[1024];
	bzero(buf,sizeof(buf));
	printf("read 阻塞读取标准输入...\n");
	if((read(STDIN_FILENO,buf,sizeof(buf)))==-1){
		if(errno == EINTR){
			printf("主函数read,被强制中断(EINTR)..\n");
			exit(0);
		}
	}
	return 0;
}
