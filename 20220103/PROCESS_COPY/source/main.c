#include <PROCESS_COPY.h>

int main(int argc, char ** argv)
{
	int prono;
	int blocksize;
	if(argv[3] == 0)
		prono = 5;
	else
		prono = atoi(argv[3]);
	CHECK_ARG(argc,prono,argv[1]);
	blocksize = COPY_BLOCK_CUR(argv[1], prono);
	PROCESS_CREATE(argv[1],argv[2],prono,blocksize);
	return 0;
}
