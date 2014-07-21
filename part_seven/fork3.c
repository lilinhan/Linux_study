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
	switch(pid)  {
		case 0:
		while(1) {
			printf("i am son!\n   pid = %d  my father is %d \n", getpid() , getppid());
			sleep(3);
	}
		break;
		case -1:  {
		printf("error !\n");
		exit(-1);
	}
			  break;
		default :  {
		printf("i am father!\n pid = %d\n", getpid());
		exit(0);
		}
	}
	return EXIT_SUCCESS;
}


