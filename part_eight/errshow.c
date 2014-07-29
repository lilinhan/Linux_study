/*
 * =====================================================================================
 *
 *       Filename:  errshow.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/29/2014 09:10:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

FILE * open_file(char * filename)
{
	FILE * stream;
	errno = 0;

	stream = fopen(filename,"r");
	if( stream == NULL )  {
		printf("can not open the file %s , reason : %s\n",filename,strerror(errno));
		exit(-1);
	}
	else
	      return stream;
}

int main(int argc, char *argv[])
{
	char *filename = "test";

	open_file(filename);


	return EXIT_SUCCESS;
}

