/*
 * =====================================================================================
 *
 *       Filename:  filecreat.c
 *
 *    Description:  creat file by creat function
 *
 *        Version:  1.0
 *        Created:  07/13/2014 03:40:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	int fd;
	if ((fd = creat( "example.c" , O_CREAT | O_EXCL | O_TRUNC)) == -1)  {
		perror("open");
		printf("open:%s     with:%d",strerror(errno),errno);
		exit(1);

	}
	else  {
		printf("creat file success\n");
	}
	close(fd);
	return 0;
}

