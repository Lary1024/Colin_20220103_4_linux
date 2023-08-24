#include <PROCESS_COPY.h>

int CHECK_ARG(int argno, int prono, const char * Sfile)
{
	if(argno < 3){
		printf("warnning:the argno is wrong!\n");
		exit(0);
	}
	if(prono <= 0 || prono >= 100){
		printf("warnning:the number of process should >= 0 and <= 100 !\n");
		exit(0);
	}
	if((access(Sfile,F_OK)) != 0)
	{
		printf("warning:the source file isn't exist!");
	}
	return 0;
}
