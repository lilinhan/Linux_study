/*
 * =====================================================================================
 *
 *       Filename:  pthread_attr_t.c
 *
 *    Description:  lots of pthread_attr_t functions
 *
 *        Version:  1.0
 *        Created:  07/23/2014 08:45:44 PM
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
#include <pthread.h>
#include <sched.h>

void *child_thread(void *arg)
{
	int policy = 0;
	int max_priority = 0,min_priority = 0;
	struct sched_param param;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_getinheritsched(&attr,&policy);
	if(policy == PTHREAD_EXPLICIT_SCHED)  {
		printf("inheritsched:PTHREAD_EXPLICIT_SCHED\n");
	}
	if(policy == PTHREAD_INHERIT_SCHED)  {
		printf("inheritsched:PTHREAD_INHERIT_SCHED\n");
	}

	pthread_attr_setschedpolicy(&attr,SCHED_RR);
	pthread_attr_getschedpolicy(&attr,&policy);
	if( policy == SCHED_RR )  {
		printf("schedpolicy:SCHED_RR\n");
	}
	if( policy == SCHED_FIFO )  {
		printf("schedpolicy:SCHED_FIFO\n");
	}
	if( policy == SCHED_OTHER )   {
		printf("schedpolicy:SCHED_OTHER");
	}

	max_priority = 	sched_get_priority_max(policy);
	min_priority =  sched_get_priority_min(policy);
	printf("Maxpriority:%u\n",max_priority);
	printf("Minpriority:%u\n",min_priority);

	param.sched_priority = max_priority;
	pthread_attr_setschedparam(&attr,&param);
	printf("sched_priority:%u\n",param.sched_priority);
	pthread_attr_destroy(&attr);


}

int main(int argc, char *argv[])
{

	pthread_t child_pthread_id;
	pthread_create(&child_pthread_id,NULL,child_thread,NULL);
	pthread_join(child_pthread_id,NULL);

	return EXIT_SUCCESS;
}

