/*
 * =====================================================================================
 *
 *       Filename:  vfork.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/21/2014 02:59:35 PM
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
#include <sys/types.h>

int globvar = 5;

int main(int argc, char *argv[])
{
	pid_t pid;
	int var = 1,i;

	//pid = fork();
	pid = vfork();
	
	switch( pid )  {
		case 0:  {
			i = 3;
			while( i-- > 0 )  {
				printf("Child is running!\n");
				globvar++;
				var++;
				sleep(1);
			}
			printf("child's globvar = %d, var = %d\n",globvar,var);
			exit(0);//当使用vfork函数时，没有加exit，var变量会出错
		};break;

		case -1:
			 perror("process creation failed\n");
			 exit(-1);

		default: {
			 i = 5;
			 while(i-- > 0 )  {
			 	printf("father is running!\n");
				globvar++;
				var++;
				sleep(1);
			 }
			 printf("parent's globvar = %d , var = %d \n",globvar,var);
			 exit(0);
		 }
	}

	return 0;
}













