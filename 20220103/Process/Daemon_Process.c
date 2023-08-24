#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

//DEMO:创建守护进程,此进程间隔执行任务(3 seconds),向time.log中写入系统事件,后台执行

int Daemon_Job(void)
{
	int fd;
	time_t tp; //时间种子类型
	char time_buf[1024];
	if((fd = open("time.log",O_RDWR|O_CREAT,0664)) == -1){
		perror("open call failed");
		exit(0);
	}
	while(1){
		bzero(time_buf,1024);
		tp = time(NULL); //获取时间种子
		ctime_r(&tp, time_buf); //转换并写入时间
		write(fd,time_buf,strlen(time_buf)); //事件写入文件
		sleep(3);
	}
}

void Daemon_Create(void)
{
	pid_t pid;
	int err_fd;
	if((err_fd = open("ERROR_FILE",O_RDWR|O_CREAT,0664))==-1)
		perror("Open Call Failed");
	pid = fork();
	if(pid > 0){
		exit(0); //父进程创建完子进程就退出,没事干了
	}else if(pid == 0){
		setsid();  //创建新会话,脱离控制终端
		close(STDIN_FILENO); //关闭标准输入标准输出文件描述符
		close(STDOUT_FILENO);
		dup2(err_fd,STDERR_FILENO); //出错重定向
		umask(0002); //修改掩码
		chdir("./"); //如果需要修改工作目录,改为/目录
		Daemon_Job(); //执行任务

		//守护进程的退出处理
	}else{
		perror("Fork Call Failed");
		exit(0);
	}
}

int main(void)
{
	Daemon_Create();

	return 0;
}

