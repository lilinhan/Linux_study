/*
 * =====================================================================================
 *
 *       Filename:  my_shell.c
 *
 *    Description:  my shell
 *
 *        Version:  1.0
 *        Created:  07/24/2014 07:37:30 PM
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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

int main()
{
	char argv[15][100],shell_order[100],*argv1[15];
	int i,j,k,count = 0;
	DIR * dir;
	struct dirent * ptr;
	pid_t pid;

	while(1)  {
	count = 0;
	printf("llh my_shell@:");
	gets(shell_order);
	for( i = 0 , j = 0 , k = 0 ; shell_order[k] != '\0' ; k++ , j++  )  {
		if( shell_order[k] == ' ' )   {
			argv[i][j] = '\0';
			i++;
			j = -1;
			count++;
			continue;
		}
		argv[i][j] = shell_order[k];

	}
	argv[i][j] = '\0';
	count++;

//	printf("%d\n\n",count);
	for( i = 0 ; i < count ; i++ )  {
//		puts(argv[i]);
		argv1[i] = argv[i];
	}
	argv1[i] = NULL;


	pid = vfork();
	if( pid == 0 )  {
		if((dir = opendir("/usr/bin")) == NULL )  {
			perror("opendir!\n");
			exit(0);
		}
		while((ptr = readdir(dir)) != NULL )  {
			if(strcmp(ptr->d_name,argv[0]) == 0 )  {
				if(execvp(argv[0],argv1) < -1)
				      perror("error!\n");
			}
		}
		
		}
	}
	return EXIT_SUCCESS;
}

