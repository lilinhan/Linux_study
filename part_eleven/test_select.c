/*
 * =====================================================================================
 *
 *       Filename:  test_select.c
 *
 *    Description:  p300
 *
 *        Version:  1.0
 *        Created:  2014年08月03日 10时35分19秒
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
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>


void display_time(const char * string)  {
	int seconds;

	seconds = time((time_t *)NULL);
	printf("%s , %d\n",string , seconds);
}

int main(int argc, char *argv[])
{
	
	fd_set  readfds;
	struct timeval timeout;
	int ret;

	FD_ZERO(&readfds);
	FD_SET(0 , &readfds);

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	while(1)   {
		display_time("before select");
		ret = select(1 , &readfds , NULL ,NULL , &timeout);
		display_time("after select");

		switch(ret)   {
			case 0 :
				printf("NO data in ten seconds.\n");
				exit(0);
				break;
			case -1 :
				perror("select\n");
				exit(-1);
				break;
			default :
				getchar();
				printf("Data is available now.\n");
		}
	}

	
	return EXIT_SUCCESS;
}

