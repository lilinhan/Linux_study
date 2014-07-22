/*
 * =====================================================================================
 *
 *       Filename:  env.c
 *
 *    Description:  p188
 *
 *        Version:  1.0
 *        Created:  07/22/2014 08:57:58 AM
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

	extern char **environ;

int main(int argc, char *argv[])
{
	int i;

	printf("Arguement:\n");
	for( i =  0 ; i < argc ; i++ )  {
		printf("argv[%d] is %s\n",i,argv[i]);
	}

	printf("Environment:\n");

	for( i = 0 ; environ[i] != NULL ; i++ )  {
		printf("%s\n",environ[i]);
	}


	return EXIT_SUCCESS;
}

