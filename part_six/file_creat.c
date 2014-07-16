/*
 * =====================================================================================
 *
 *       Filename:  file_creat.c
 *
 *    Description:  try gedit file_open,file_creat,file_close.
 *
 *        Version:  1.0
 *        Created:  07/13/2014 02:59:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	if((fd = open( "example.c" , O_CREAT | O_EXCL , S_IRUSR | S_IWUSR )) == -1 )  {
		perror("open");
		printf("open:%s     with errno:%d\n",strerror(errno),errno);	
	}
	else  {
		printf("creat file success\n");
	}

	close(fd);
	return 0;
}

