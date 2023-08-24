#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int CHECK_ARG(int argno, int prono, const char * sfile);
int COPY_BLOCK_CUR(const char * Sfile, int prono);
int PROCESS_CREATE(const char * Sfile, const char * Dfile, int prono, int blocksize);
int PROCESS_WAIT(void);
