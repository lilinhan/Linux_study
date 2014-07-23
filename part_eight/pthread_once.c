/*
 * =====================================================================================
 *
 *       Filename:  pthread_once.c
 *
 *    Description:  p206
 *
 *        Version:  1.0
 *        Created:  07/23/2014 04:34:52 PM
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

pthread_once_t once = PTHREAD_ONCE_INIT;

void run()
{
	printf("i just run once~,my tid = %d\n",pthread_self());
}

void * thread1(void * arg)
{
	pthread_t tid = pthread_self();
	printf("current thread's ID is %d\n",tid);
//	sleep(2);
	pthread_once(&once,run);
//	sleep(2);
	printf("pthread1 end!\n");
}
void * thread2(void * arg)
{
	pthread_t tid = pthread_self();
	printf("current thread's ID is %d\n",tid);
	pthread_once(&once,run);
	printf("pthread2 end!\n");
}

int main(int argc, char *argv[])
{
	pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
//	sleep(1);
	sleep(3);
	printf("main thread exit!\n");
	
	return EXIT_SUCCESS;
}









