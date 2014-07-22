/*
 * =====================================================================================
 *
 *       Filename:  studyuid.c
 *
 *    Description:  p195
 *
 *        Version:  1.0
 *        Created:  07/22/2014 02:53:54 PM
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
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main(int argc, char *argv[])
{
	int fd;
	printf("uid study:   \n");
	printf("Process's uid = %d , euid = %d\n",getuid(),geteuid());

	if( (fd = open("test.c",O_RDWR)) == -1 )  {
		printf("Open failure,errno is %d : %s  \n",errno,strerror(errno));
		exit(1);
	}
	else   {
		printf("Open successfully!\n");
	}
	close(fd);
	exit(0);

	return EXIT_SUCCESS;
}

