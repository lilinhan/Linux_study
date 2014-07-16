/*
 * =====================================================================================
 *
 *       Filename:  fcntl_access.c
 *
 *    Description:  example for fcntl function
 *
 *        Version:  1.0
 *        Created:  07/13/2014 08:25:14 PM
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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void my_err( const char * err_string , int line )
{
	fprintf(stderr, "line : %d ",line );
	perror(err_string);
	exit(1);
}

int main(int argc, char *argv[])
{
	int ret;
	int access_mode;
	int fd;

	if((fd = open( "example" , O_CREAT|O_TRUNC|O_RDWR , S_IRWXU)) == -1 )  {
		my_err("open",__LINE__);
	}

	if((ret = fcntl(fd,F_SETFL , O_APPEND)) < 0 )  {
		my_err("fcntl",__LINE__);
	}

	if((ret = fcntl( fd , F_GETFL , 0))  < 0 )  {
		my_err("fcntl",__LINE__);
	}

	access_mode = ret & O_ACCMODE;
	printf("%d\t",F_GETFL);
	printf("%d\t",F_SETFL);
	printf("%d\t",ret);
	printf("%d\t",access_mode);
	if( access_mode == O_RDONLY ) {
		printf("example access mode : read only~\n");
	}

	if( access_mode == O_WRONLY )  {
		printf("example access mode : write only!\n");
	}

	if( access_mode == O_RDWR )   {
		printf("example access mode : read + write!\n");
	}	

	if( ret & O_APPEND )  {
		printf(" ,append");
	}

	if( ret & O_NONBLOCK )  {
		printf(" ,nonbclock");
	}
		printf("\n%d \t ",O_NONBLOCK);

	if( ret & O_SYNC )  {
		printf("\n%d ",O_SYNC);
	

	}
		printf("\n%d ",O_SYNC);

	printf("\n");


	return 0;
}















