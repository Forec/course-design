// @author: Forec(王耀)
// @last-edit: 2016-10-25 
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @gcc version: 5.4
// @filename: t4.c

#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	pid_t pid[2];
	int fd[2];
	char buf[60];
	pipe(fd);
	if ((pid[0] = fork()) < 0){
		fprintf(stderr, "Fork1 failed\n");
		exit(-1);
	}else if (pid[0] == 0){ /* child 1 */
		sprintf(buf, "Child 1 is sending a message!");
		write(fd[1], buf, 30);
		exit(0);
	}else { /* parent process */
		wait(NULL); /* wait child 1 */
		if ((pid[1] = fork()) < 0){
			fprintf(stderr, "Fork2 failed\n");
			exit(-1);
		}else if (pid[1] == 0){ /* child 2 */
			sprintf(buf, "Child 2 is sending a message!");
			write(fd[1], buf, 30);
			exit(0);
		}else{
			wait(NULL); /* wait child 2 */
			read(fd[0], buf, 30);
			printf("%s\n", buf);
			read(fd[0], buf, 30);
			printf("%s\n", buf);
		}
	}
	return 0;
}
