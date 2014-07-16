/*
 * =====================================================================================
 *
 *       Filename:  show_files.c
 *
 *    Description:  print files from directory by opendir(),readdir(),closedir();
 *
 *        Version:  1.0
 *        Created:  07/15/2014 03:14:55 PM
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
#include <dirent.h>
#include <sys/types.h>

int my_readir(const char * path)
{
	DIR * dir;
	struct dirent * ptr;
	int i;

	if((dir = opendir( path )) == NULL )  {
		perror("opendir:");
		return -1;
	}
	printf("file :\n");
	while(( ptr = readdir ( dir ))  != NULL )  {
		printf("%-8s\t", ptr->d_name );
	}
	printf("\n");
	closedir(dir);

	return 0;
}


int main(int argc, char *argv[])
{
	if( argc < 2 )  {
		printf("listfile <target path>\n");
		exit(0);
	}

	if( my_readir( argv[1] ) < 0 )  {
		exit(1);
	}

	return EXIT_SUCCESS;
}

