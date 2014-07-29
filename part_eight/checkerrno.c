/*
 * =====================================================================================
 *
 *       Filename:  checkerrno.c
 *
 *    Description:  p217
 *
 *        Version:  1.0
 *        Created:  07/29/2014 09:06:51 AM
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


int main(int argc, char *argv[])
{
	FILE * stream;
	char * filename = "test";

	errno = 0;
	stream = fopen(filename,"r");
	if(stream == NULL)  {
		printf("open file %s failed,errno is %d\n",filename,errno);
	}
	else
	      printf("open file %s successfull\n",filename);

	return EXIT_SUCCESS;
}

