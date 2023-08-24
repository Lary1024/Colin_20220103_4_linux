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
	char buffer[1024];
	bzero(buffer,sizeof(buffer));
	fd = open("CONSD",O_RDONLY);
	read(fd, buffer, sizeof(buffer));
	printf("child  %d read success readdate:%s\n",getpid(),buffer);
	close(fd);
	return 0;
}

