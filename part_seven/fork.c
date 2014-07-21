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
			printf("i am son,pid = %d,my father's pid = %d\n",pid , getppid());
			break;
		case -1:
			printf("error!\n");
			exit(-1);
		default:
			printf("i am father! my pid = %d\n",getpid());
			break;
	}

	return EXIT_SUCCESS;
}

