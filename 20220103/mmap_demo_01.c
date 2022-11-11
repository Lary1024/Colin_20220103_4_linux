#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>

//MMAP_DEMO_01

int main(void)
{
	int fd = open("MKFILE",O_RDWR);
	int fsize;
	int * ptr = NULL;
	fsize = lseek(fd, 0, SEEK_END);
	
	if((ptr = mmap(NULL,fsize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0))==MAP_FAILED)
	{
		perror("mmap failed");
	}
	close(fd);
	ptr[0]=0x34333231;
	printf("Change Success ,its Done\n");
	munmap(ptr, fsize);


	return 0;
}
