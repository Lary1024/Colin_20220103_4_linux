#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

void Sig_Do(int n) //信号捕捉函数
{
	int i = 3;
	while(i){
		printf("Wait...Eating : %d\n",i);
		i--;
		sleep(1);
	}
}

int main(void)
{
	struct sigaction new_act,old_act; // 信号行为结构体
	new_act.sa_handler = Sig_Do; // 信号行为设置
	new_act.sa_flags = 0; //默认选项,取决于行为接口
	sigemptyset(&new_act.sa_mask); 
	sigaction(SIGINT,&new_act,&old_act);

	while(1)
		sleep(1);
	return 0;
}
