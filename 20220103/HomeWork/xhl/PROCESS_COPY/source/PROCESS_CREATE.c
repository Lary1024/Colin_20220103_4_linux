#include<PROCESS_COPY.h>

int PROCESS_CREATE(const char * Sfile,const char * Dfile,int prono,int blocksize){
		pid_t pid;
		int flag;
		for(flag=0;flag<prono;flag++){
			pid = fork();
			if(pid == 0)
				break;
		}

		if(pid > 0){
			printf("parent procee %d waiting...\n",getpid());
			PROCESS_WAIT();
		}else if(pid == 0){
			char str_pos[100];
			char str_blocksize[100];
			bzero(str_pos,100);
			bzero(str_blocksize,100);
			int pos;
			pos = flag*blocksize;
			sprintf(str_pos,"%d",pos);
			printf("child process %d pos [%d] blocksize [%d]\n",getpid(),pos,blocksize);
			sprintf(str_blocksize,"%d",blocksize);
			execl("/home/lary/20220103/xhl/PROCESS_COPY/module/COPY","COPY",Sfile,Dfile,str_pos,str_blocksize);
		}else{
			perror("fork call fail...");
			exit(0);
		}
		return 0;
	
}
