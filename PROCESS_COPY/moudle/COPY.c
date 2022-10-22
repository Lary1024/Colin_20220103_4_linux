#include <PROCESS_COPY.h>

int main(int argc, char ** argv)
{
	int pos;
	int blocksize;
	pos = atoi(argv[3]);
	blocksize = atoi(argv[4]);
	int Sfd,Dfd;
	Sfd = open(argv[1],O_RDONLY);
	Dfd = open(argv[2],O_WRONLY | O_CREAT, 0664);

	lseek(Sfd, pos, SEEK_SET);
	lseek(Dfd, pos, SEEK_SET);

	char  buffer[blocksize];
	bzero(buffer,sizeof(buffer));
	int recvlen;
	recvlen = read(Sfd,buffer,sizeof(buffer));
	write(Dfd,buffer,recvlen);
	close(Sfd);
	close(Dfd);
	return 0;
}

