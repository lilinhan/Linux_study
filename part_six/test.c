/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  linux c test
 *
 *        Version:  1.0
 *        Created:  07/13/2014 09:06:53 AM
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
int main(int argc, char *argv[])
{
	int number , guess , i = 8;
	srand(time(NULL));
	number = rand()%100 + 1;
	printf("%d",number);
	printf("please guess the number:\n");
	while( i > 0 )  {
		scanf("%d",&guess);
		if ( guess == number )  {
			printf("you are right!\n");
			return 0;
		}

		else if ( guess > number )  {
			printf("sorry you are wrong !\n");
			printf(" too high\n");
		}

		else  {
			printf("sorry you are wrong\n");
			printf("too low!\n");
		}

		i--;
	}
	
	printf("Game over!\n");

	return EXIT_SUCCESS;
}

