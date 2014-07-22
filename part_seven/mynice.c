/*
 * =====================================================================================
 *
 *       Filename:  mynice.c
 *
 *    Description:  p197
 *
 *        Version:  1.0
 *        Created:  07/22/2014 03:16:32 PM
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
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int stat_val = 0;
	int oldpri,newpri;

	printf("nice study\n");

	pid = fork();
	switch(pid)   {
		case 0:printf("i am son,curpid = %d  ,father'pid = %d  \n",pid,getppid());
		       oldpri = getpriority(PRIO_PROCESS,0);
		       printf("old priority = %d\n",oldpri);

		       newpri = nice(2);
		       printf("New priority = %d\n",newpri);
		       exit(0);

		case -1:perror("process creation failed\n");
			exit(-1);
		default:
			printf("i am father,child'pid = %d  ,parent'pid = %d\n",pid ,getpid());
			break;
	}

	wait(&stat_val);
	exit(0);

}

