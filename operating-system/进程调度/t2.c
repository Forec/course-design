// @author: Forec(王耀)
// @last-edit: 2016-10-25 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @gcc version: 5.4
// @filename: t2.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define TIMES 30

int main(){
	pid_t pid[2];
	printf("parent says that aaaaaaaaaaaaaaaaaaaaaaaaa\n");

	pid[0] = fork();

	if (pid[0] < 0){
		fprintf(stderr, "Fork1 failed");
		exit(-1);
	}
	else if (pid[0] == 0){ /* child 1 process */
		int i;
		for (i = 0; i < TIMES; i++)
			printf("child1 says that bbbbbbbbbbbbbbbbbbbbbbbbb\n");
	}
	else if (pid[0] > 0){  /* parent process */
		pid[1] = fork();

		if (pid[1] < 0){
			fprintf(stderr, "Fork2 failed");
			exit(-1);
		}
		else if (pid[1] == 0){ /* child 2 process */
			int i;
			for (i = 0; i < TIMES; i++)
			printf("child2 says that ccccccccccccccccccccccccc\n");
		}
		else{
			wait(NULL);
		}
		wait(NULL);
	}
	return 0;
}
