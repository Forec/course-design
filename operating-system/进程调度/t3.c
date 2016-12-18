// @author: Forec(王耀)
// @last-edit: 2016-10-25 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @gcc version: 5.4
// @filename: t3.c

#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50

char buffer[3][BUFFER_SIZE];

pid_t pid[2];

void handle_SIGINT(){
	kill(pid[0], SIGABRT);
	kill(pid[1], SIGABRT);
	wait(NULL);
	wait(NULL);
	write(STDOUT_FILENO, buffer[2], strlen(buffer[2]));
	exit(0);
}

void ch1_terminate(){
	write(STDOUT_FILENO, buffer[0], strlen(buffer[0]));
	exit(0);
}

void ch2_terminate(){
	write(STDOUT_FILENO, buffer[1], strlen(buffer[1]));
	exit(0);
}

int main(int argc, char *argv[]){
	struct sigaction handler[3];
	handler[0].sa_handler = handle_SIGINT;
	sigaction(SIGINT, &handler[0], NULL);
	strcpy(buffer[0], "Child Process 1 is killed by Parent!\n");
	strcpy(buffer[1], "Child Process 2 is killed by Parent!\n");
	strcpy(buffer[2], "Parent Process is killed!\n");
	if ((pid[0] = fork()) < 0){
		fprintf(stderr, "Fork1 failed\n");
		exit(-1);
	}else if (pid[0] == 0){ /* child1 process */
		handler[1].sa_handler = ch1_terminate;
		sigaction(SIGABRT, &handler[1], NULL);
		while(1);
	}else{ /* parent process */
		if ((pid[1] = fork()) < 0){
			fprintf(stderr, "Fork2 failed\n");
			exit(-1);
		}else if (pid[1] == 0){ /* child2 process */
			handler[2].sa_handler = ch2_terminate;
			sigaction(SIGABRT, &handler[2], NULL);
			while(1);
		}
		else{
			while(1);
		}
	}
	return 0;
}

