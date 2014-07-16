/*
 * =====================================================================================
 *
 *       Filename:  my_chomd.c
 *
 *    Description:  printf the file attribute
 *
 *        Version:  1.0
 *        Created:  07/14/2014 07:22:49 PM
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
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	struct stat buf;
	if( argc != 2 )   {
		printf("usage: my_stat <filename>\n");
		exit(0);
	}

	if (stat(argv[1] , &buf ) == -1)  {
		perror("stat:");
		exit(1);
	}

	printf("device is : %d\n" ,buf.st_dev);
	printf("inode is : %d\n" , buf.st_ino);
	printf("mode is : %d\n" , buf.st_mode);
	printf("number of hard link is : %d\n" , buf.st_nlink);
	printf("user ID of owner is : %d\n" , buf.st_uid);
	printf("group ID of owner is : %d\n" , buf.st_gid);
	printf("device type (if inode device) is : %d\n" ,buf.st_rdev);
	
	printf("total size , int bytes is : %d\n" , buf.st_size);
	printf("blocksize for filesystem I/O is : %d\n" , buf.st_blksize);
	printf("number of blocks allocated is : %d\n" , buf.st_blocks);
	
	printf("time of last access is :%s\n" , ctime(&buf.st_atim));
	printf("time of last modification is : %s\n" , ctime(&buf.st_mtim));
	printf("time of last change is : %s\n" , ctime(&buf.st_ctim));

	return 0;
}









