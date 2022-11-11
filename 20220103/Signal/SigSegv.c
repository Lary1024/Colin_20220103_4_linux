#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

//段错误示例,字符指针不能修改常量字符串
//非法操作内存,对只读内存进行写操作,系统就会通过信息把你的进程杀死

int main(void){

	char * str = "xxxxxxx";
	str[0] = 'X';

	return 0;
}
