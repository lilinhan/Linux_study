/*
 * =====================================================================================
 *
 *       Filename:  execve.c
 *
 *    Description:  程序2 p190
 *
 *        Version:  1.0
 *        Created:  07/22/2014 10:10:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[],char **environ)
{
	pid_t pid;
	int stat_val;
	printf("Exec example!\n");
	pid = fork();
	switch(pid)  {
		case -1:perror("process creation faild\n");
			exit(-1);
		case 0 :
			printf("Child prosess is running\n");
			printf("my pid = %d   ,parent pid = %d\n",getpid(),getppid());
			printf("uid = %d   ,gid = %d\n",getuid(),getgid());
			execve("processimage",argv,environ);
			printf("process never to here~\n");
			exit(0);
		default :
			printf("parent process is running\n");
			break;
	}

	wait(&stat_val);
	exit(0);

	return EXIT_SUCCESS;
}

