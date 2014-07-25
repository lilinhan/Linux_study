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

void find_command(char ** argv1)  
{
	DIR * dir;
	struct dirent * ptr;
	pid_t pid;

//	pid = vfork();

//	if( pid == 0 )  {

	if((dir = opendir("/usr/bin")) == NULL )  {
		perror("opendir!\n");
		exit(0);
	}
	

	while((ptr = readdir(dir)) != NULL )  {
		if(strcmp(ptr->d_name,argv1[0]) == 0 )  {
			execvp(argv1[0], argv1);
			exit(0);
//			if(execvp(argv1[0],argv1) < 0)
//			      perror("error!\n");
//			printf("\nwhye\n");
//			exit(0);
		}
	}
	printf("\nok\n");
}

int chose(int count,char ** argv1)
{
	int flag = 5,i;

	if( strcmp( argv1[0],"cd")  == 0 )  {
		flag = 1;
	}
	for( i = 0 ; i < count ; i++ )   {
		if( strcmp(argv1[i],">") == 0 ) 
		      flag = 2;
		if( strcmp(argv1[i],"|") == 0 ) 
		      flag = 3;
	}

	return flag;
}

void change_dir(char ** argv1)
{
	char buf[100];
	if(chdir(argv1[1]) < 0)  {
		perror("chdir!\n");
	}

	getcwd(buf,100);
	printf("%s\n",buf);

}

void outputdir(int count,char ** argv1)
{
	int i,j,num;
	int fd;
	char * argv[10];
	pid_t pid;

/*	for( i = 0 , j = 0 ; i < count ; i++ )  {
		if()
	}
*/	

	for( i = 0 , j = 0; i < count ; i++) {
		if(strcmp(argv1[i],">") == 0 )  {
		 	num = i+1;
			break;
		}
		argv[j] = argv1[i];
		j++;
	}
	argv[j] = NULL;
	if((fd = open(argv1[num],O_EXCL | O_TRUNC | O_CREAT | O_RDWR , 0666)) < 0 )  {
		perror("error!\n");
	}

//	pid = vfork();
//	if( pid == 0 )  {
	dup2(fd , 1);
		if(execvp(argv1[0],argv) == -1)  {
			exit(-1);
		}
		exit(0);
//	}
}

int main()
{
	char argv[15][100],shell_order[100],*argv1[15];
	int i,j,k,count = 0,flag,fd;
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
	
	printf("%d\n",count);
	
	flag = chose(count,argv1);
	printf("%d\t\n\n\n",flag);

	pid = vfork();
	if(pid ==0 )  {
	switch(flag)  {
		case 1:change_dir(argv1);break;
		case 2:outputdir(count,argv1);break;
		default:find_command(argv1);break;

	}
	exit(0);
	}
//	find_command(argv1);
wait(NULL);
	}
	return EXIT_SUCCESS;
}

