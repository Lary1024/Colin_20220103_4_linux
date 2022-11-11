#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MSG "can you hear me?"

int main(void)
{
	//write
	int fd;
	fd = open("CONSD",O_WRONLY);
	write(fd, MSG, strlen(MSG));
	printf("parent %d write success \n",getpid());
	close(fd);
	return 0;
}

