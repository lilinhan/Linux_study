/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  fork.c
 *
 *        Version:  1.0
 *        Created:  07/21/2014 08:03:43 PM
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
#include <sys/types.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	switch( pid )  {
		case 0:
			while(1)  {
			printf("A background process,pid:%d\n,parentid: %d\n",getpid(),getppid());
			sleep(3);
			}
		case -1:
			perror("error!\n");
			exit(-1);
		default:
			printf("I am parent process, my pid = %d\n",getpid());
			exit(0);
	}

	return EXIT_SUCCESS;
}

