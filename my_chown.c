/*
 * =====================================================================================
 *
 *       Filename:  my_chown.c
 *
 *    Description:  try and try
 *
 *        Version:  1.0
 *        Created:  07/14/2014 08:27:54 PM
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
#include <errno.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	if( argc != 2 )  {
		printf("usage : my_stat <filename>\n");
		exit(0);
	}
	if( stat(argv[1],&buf)  == -1)  {
		perror("stat:");
		exit(1);
	}

	chown(argv[1],1000,1000);

	return 0;
}

