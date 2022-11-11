#include<PROCESS_COPY.h>

int CHECK_ARG(int argno,int prono,const char * Sfile){
		
		if(argno < 3){
			printf("errror:arg number less...\n");
			exit(0);
		}
		if(prono <= 0 || prono >= 100){
			printf("error:process number less 0 ,more 100\n");
			exit(0);
		}
		if((access(Sfile,F_OK)) != 0){
			printf("error: Sfile no exit\n");
			exit(0);
		}
		return 0;
}
