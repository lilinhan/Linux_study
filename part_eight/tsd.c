/*
 * =====================================================================================
 *
 *       Filename:  tsd.c
 *
 *    Description:  p211
 *
 *        Version:  1.0
 *        Created:  07/28/2014 10:48:32 AM
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

pthread_key_t key;

void * thread2(void * arg)
{
	int tsd = 5;
	printf("thread %d is running!\n",pthread_self());
	pthread_setspecific(key,(void * )tsd);
	printf("thread %d returns %d\n",pthread_self(),pthread_getspecific(key));
}

void * thread1(void * arg)
{
	int tsd =0;
	int status;
	pthread_t thid2;

	printf("thread %d is running\n",pthread_self());
	pthread_setspecific(key,(void *)tsd);
	pthread_create(&thid2 ,NULL,thread2,NULL);
//	pthread_join(thid2,(void *) status);
	sleep(3);
	printf("thread %d returns %d\n",pthread_self(),pthread_getspecific(key));
}

int main(int argc, char *argv[])
{
	pthread_t thid1;
	int status;

	printf("main thread begins running\n");
	pthread_key_create(&key,NULL);
	pthread_create(&thid1,NULL,thread1,NULL);
	sleep(5);
//	pthread_join(thid1,(void *)status);
	pthread_key_delete(key);
	printf("main thread exit\n");

	return EXIT_SUCCESS;
}

