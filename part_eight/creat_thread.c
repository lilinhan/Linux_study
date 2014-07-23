/*
 * =====================================================================================
 *
 *       Filename:  creat_thread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/23/2014 03:57:25 PM
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

int * thread(void * arg)
{
	pthread_t tid1;
	tid1 = pthread_self();
	printf("tid1 = %d\n",tid1);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid2;

	printf("i am master pthread:%d\n",pthread_self());

	tid2 = pthread_create(&tid2, NULL ,(void *)thread , NULL );
	if( tid2 != 0 )  {
		perror("pthread creation is failed!\n");
		exit(0);
	}
	sleep(1);
	return EXIT_SUCCESS;
}













