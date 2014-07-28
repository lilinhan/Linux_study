/*
 * =====================================================================================
 *
 *       Filename:  jointhread.c
 *
 *    Description:  p209
 *
 *        Version:  1.0
 *        Created:  07/28/2014 10:01:08 AM
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
#include <pthread.h>

void assisthread(void * arg)
{
	printf("I am helping to do some jobs!\n");
	sleep(3);
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t assisthid;
	int status;

	pthread_create(&assisthid , NULL , (void *)assisthread , NULL ) ;
	pthread_join(assisthid,(void *)&status);
	printf("assisthread's exit is caused %d\n",status);

	return EXIT_SUCCESS;
}

