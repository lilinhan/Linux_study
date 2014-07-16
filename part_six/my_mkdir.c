/*
 * =====================================================================================
 *
 *       Filename:  my_mkdir.c
 *
 *    Description:  make directory by mkdir function 
 *
 *        Version:  1.0
 *        Created:  07/15/2014 09:12:42 AM
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
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if( argc < 2 )  {
		printf("my_mkdir <directory name>\n");
		exit(0);
	}
	mkdir( argv[1] , S_IRWXU | S_IRWXG | S_IRWXO );

	return EXIT_SUCCESS;
}

