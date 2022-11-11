#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

//read

typedef struct
{
	int id;
	char Name[20];
}shared_t;


int main(void)
{
	int fd;
	int size = sizeof(shared_t);
	shared_t * ptr = NULL;
	fd = open("MapFile",O_RDWR|O_CREAT,0664);	
	ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	while(1)  //
	{
		printf("Date: id %d Name %s\n",ptr->id,ptr->Name);
		sleep(1);	
	}
	munmap(ptr,size);
	close(fd);
	return 0;
}




