/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  fork.c
 *
 *        Version:  1.0
 *        Created:  07/21/2014 10:36:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	printf("Process Creation Study\n");
	pid = fork();
	if( 0 == pid ) {
		printf("i am son!\n   pid = %d  my father is %d \n", pid , getppid());
	}
	else if( -1 == pid )  {
		printf("error !\n");
	}
	else  {
		printf("i am father!\n pid = %d\n", getpid());
	}
	return EXIT_SUCCESS;
}

