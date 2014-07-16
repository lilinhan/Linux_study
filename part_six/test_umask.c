/*
 * =====================================================================================
 *
 *       Filename:  test_umask.c
 *
 *    Description:  change file permission by umask function
 *
 *        Version:  1.0
 *        Created:  07/14/2014 09:00:48 PM
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

int main(int argc, char *argv[])
{
	umask(0);
	if(creat("example2",S_IRWXU | S_IRWXG |S_IRWXO) < 0 )  {
		perror("creat");
		exit(0);
	}

	umask(S_IRWXO);
	if(creat("example1",S_IRWXU | S_IRWXG | S_IRWXO) < 0)  {
		perror("creat:");
		exit(1);
	}

	return 0;
}




