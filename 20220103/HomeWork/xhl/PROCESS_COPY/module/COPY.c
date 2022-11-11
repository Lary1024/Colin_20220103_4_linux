#include<PROCESS_COPY.h>

int main(int argc , char ** argv){
	
	int pos = atoi(argv[3]);
	int blocksize = atoi(argv[4]);
	int sfd,dfd;
	sfd = open(argv[1],O_RDONLY);
	dfd = open(argv[2],O_WRONLY | O_CREAT,0664);
	lseek(sfd,pos,SEEK_SET);
	lseek(dfd,pos,SEEK_SET);

	char buffer[blocksize];
	bzero(buffer,blocksize);
	int recvlen;
	recvlen = read(sfd,buffer,blocksize);
	write(dfd,buffer,recvlen);
	close(sfd);
	close(dfd);
	return 0;
}
