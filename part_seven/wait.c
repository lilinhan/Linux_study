/*
 * =====================================================================================
 *
 *       Filename:  wait.c
 *
 *    Description:  p190 
 *
 *        Version:  1.0
 *        Created:  07/22/2014 10:52:40 AM
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
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	char *msg;
	int k;
	int exit_code;

	printf("study how to exit code\n");
	pid = fork();
	switch(pid)  {
		case 0:msg = "Child process is running!\n";
		       k = 5;
		       exit_code = 37;
		       break;
		case -1:
		       perror("process creation failed\n");
		       exit(1);
		default:
		       exit_code = 0 ;
		       break;
	}

	if(pid != 0)  {
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child process has exited, pid = %d\n",child_pid);
		if(WIFEXITED(stat_val))
		printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
		else
		      printf("child exited abnormally\n");
	}
	else  {
		while( k-- > 0 )  {
			puts(msg);
			sleep(1);
		}
	}

	exit(exit_code);
}

