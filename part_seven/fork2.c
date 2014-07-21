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
	char *msg;
	int k;

	pid = fork();
	switch( pid )  {
		case 0:
			msg = "child process is running\n";
			k = 3;
			break;
		case -1:
			perror("process creation failed\n");
			break;
		default:
			msg = "parent process is running";
			k = 5;
			break;
	}

	while( k > 0 )  {
		puts(msg);
		sleep(1);
		k--;
	}

	return EXIT_SUCCESS;
}











