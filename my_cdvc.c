/*
 * =====================================================================================
 *
 *       Filename:  my_cdvc.c
 *
 *    Description:  change the directory by chdir function
 *
 *        Version:  1.0
 *        Created:  07/15/2014 02:44:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
void my_err(const char * err_string , int line )  
{
	fprintf(stderr,"line : %s\n", line );
	perror(err_string);
	exit(0);
}


int main(int argc, char *argv[])
{
	char buf[PATH_MAX + 1] ;

	if( argc < 2 )  {
		printf("my_cd <target path>\n");
		exit(1);
	}

	if(chdir( argv[1]) < 0 )  {
		my_err("chdir",__LINE__);
	}

	if(getcwd(buf,512) < 0 )  {
		my_err("getcwd",__LINE__);
	}

	printf("%s\n",buf);

	return EXIT_SUCCESS;
}

