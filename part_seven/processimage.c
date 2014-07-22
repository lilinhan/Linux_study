/*
 * =====================================================================================
 *
 *       Filename:  processimage.c
 *
 *    Description:  p190  程序（1）
 *
 *        Version:  1.0
 *        Created:  07/22/2014 10:05:16 AM
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
	int i;
	printf("i am a process image!\n");
	printf("my pid = %d , parent'pid = %d\n",getpid(),getppid());
	printf("uid = %d , gid = %d\n",getuid(),getgid());

	for( i = 0 ; i < argc ; i++ ) {
		printf("argv[%d]:%s\n",i,argv[i]);
	}

	return EXIT_SUCCESS;
}

