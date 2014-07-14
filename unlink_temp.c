/*
 * =====================================================================================
 *
 *       Filename:  unlink_temp.c
 *
 *    Description:  remove the file by unlink funvtion
 *
 *        Version:  1.0
 *        Created:  07/14/2014 09:49:13 PM
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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void my_err( const char * err_string , int line )  
{
	fprintf(stderr , "line :%d" , __LINE__);
	perror(err_string);
	exit(0);
}


int main(int argc, char *argv[])
{
	int fd;
	char buf[32];
	if((fd = open(argv[1] , O_CREAT | O_RDWR | O_TRUNC , S_IRWXU))  < 0 )  {
		my_err("open",__LINE__);
	}

	if(unlink(argv[1]) < 0 )  {
		my_err("unlink" , __LINE__);
	}
	printf("file unlinked\n");
	
	if((lseek(fd,0,SEEK_SET)) == -1 )  {
		my_err("lseek",__LINE__);
	}

	if(read(fd,buf,5) < 0 )  {
		my_err("read",__LINE__);
	}
	printf("%s\n",buf);
	return EXIT_SUCCESS;
}

