/*
 * =====================================================================================
 *
 *       Filename:  my_ls.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/16/2014 03:30:38 PM
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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>

#define MAX_LINE  50

void my_err( const char * err_string , int line )
{
	fprintf( stderr , "line :%d" , line );
	perror("err_string");
	exit(0);
}

int main(int argc, char *argv[])
{
	DIR * dir;
	struct dirent *ptr,*ptr1;
	struct stat buf;
	int sure_len = 0 , i , j , m, n, MAX_FILE_NAME = 0,LAST_LETTER,NUMBER_OF_FILE = 0;
	//测试文件夹里面文件的个数，以及最长文件名字的长度
	if(( dir = opendir(argv[1])) == NULL )  {
		perror("opendir");
		return 0;
	}
	while((ptr1 = readdir(dir)) != NULL )  {
		if( MAX_FILE_NAME < strlen(ptr1->d_name))   {
			MAX_FILE_NAME = strlen(ptr1->d_name);
		}
	NUMBER_OF_FILE++;
	}
	closedir(dir);

	

	char FILE_NAME[NUMBER_OF_FILE][MAX_FILE_NAME+1],FILE[MAX_FILE_NAME+1];//定义二维字符数组，写入所有文件的名字

	//将文件名字写入数组中
	if(( dir = opendir(argv[1])) == NULL )  {
		perror("opendir");
		return 0;
	}


	i = 0;
	while(( ptr = readdir(dir)) != NULL )  {
		strcpy(FILE_NAME[i],ptr->d_name);
		i++;
	}
	closedir(dir);
	
	for( m = 0 ; m < NUMBER_OF_FILE ; m++ )
	      for( n = 0 ; n < NUMBER_OF_FILE-1 ; n++ )  
	      	if( strcmp(FILE_NAME[n] , FILE_NAME[n+1]) > 0 )  {
			strcpy(FILE , FILE_NAME[n]);
			strcpy(FILE_NAME[n],FILE_NAME[n+1]);
			strcpy(FILE_NAME[n+1],FILE);
		}
	j = 0;
	while( j < i )  {
		m = 0;
		sure_len += strlen(FILE_NAME[j]);
		if( sure_len >= MAX_LINE )  {
			printf("\n");
			sure_len = 0;
		}
		printf("%s",FILE_NAME[j] );
		while( m < (MAX_FILE_NAME - strlen(FILE_NAME[j])) )  {
			printf(" ");
			m++;
		}
		printf(" ");
		j++;
	}	
	
	printf("\n");
	return EXIT_SUCCESS;
}


