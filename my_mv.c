/*
 * =====================================================================================
 *
 *       Filename:  my_mv.c
 *
 *    Description:  renmae the file by system renmae function
 *
 *        Version:  1.0
 *        Created:  07/14/2014 09:35:22 PM
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

int main(int argc, char *argv[])
{
	if( argc < 3 )  {
		printf("my_mv <old file> <new file>");
		exit(0);
	}

	if ( rename(argv[1],argv[2]) < 0 )   {
		perror("rename");
		exit(1);
	}

	return EXIT_SUCCESS;
}

