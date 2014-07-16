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

#define MAX_LINE  60

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
	int sure_len = 0,i, MAX_FILE_NAME = 0,LAST_LETTER;

	if(( dir = opendir(argv[1])) == NULL )  {
		perror("opendir");
		return 0;
	}

	while((ptr1 = readdir(dir)) != NULL )  {
		if( MAX_FILE_NAME < strlen(ptr1->d_name))   {
			MAX_FILE_NAME = strlen(ptr1->d_name);
		}
	}
	closedir(dir);


	if(( dir = opendir(argv[1])) == NULL )  {
		perror("opendir");
		return 0;
	}
	while (( ptr = readdir(dir)) != NULL )  {
		i = 0;
		LAST_LETTER = strlen(ptr->d_name);
		if( ptr->d_name[0] == '.' )  {
			continue;
		}
		sure_len += strlen(ptr->d_name);
		if( sure_len >= MAX_LINE )  {
			printf("\n");
			sure_len = 0;
		}
		printf("%s",ptr->d_name );
		while( i < (MAX_FILE_NAME - strlen(ptr->d_name)) )  {
			printf(" ");
			i++;
		}
		printf(" ");
	}
	

	closedir(dir);
	printf("\n");
	return EXIT_SUCCESS;
}


