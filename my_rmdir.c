/*
 * =====================================================================================
 *
 *       Filename:  my_rmdir.c
 *
 *    Description:  remove directory by rmdir function
 *
 *        Version:  1.0
 *        Created:  07/15/2014 09:28:08 AM
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

int main(int argc, char *argv[])
{
	if( argc < 2 )  {
		printf("my_rmdir <directory name>\n");
		exit(0);
	}

	rmdir(argv[1]);

	return EXIT_SUCCESS;
}

