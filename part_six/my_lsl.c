/*
 * =====================================================================================
 *
 *       Filename:  my_lsl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2014 03:06:35 PM
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
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

int main(int argc, char *argv[])
{
	DIR * dir;
	struct dirent *ptr;
	struct passwd * psd;
	struct group * grp;
	struct stat buf;
	char buf_time[32];

	if(((dir = opendir(argv[1])) == NULL) )  {
		perror("opendir");
		exit(0);
	}

	chdir(argv[1]);
	while((ptr = readdir(dir)) != NULL )  {
	stat(ptr->d_name,&buf);
	//打印文件类型
	if(S_ISLNK(buf.st_mode))  {
		printf("l");
	}
	else if(S_ISREG(buf.st_mode))  {
		printf("-");
	}
	else if(S_ISDIR(buf.st_mode))  {
		printf("d");
	}
	else if(S_ISCHR(buf.st_mode))  {
		printf("c");
	}
	else if(S_ISBLK(buf.st_mode)) {
		printf("b");
	}
	else if(S_ISFIFO(buf.st_mode))  {
		printf("f");
	}
	else if(S_ISSOCK(buf.st_mode))  {
		printf("s");
	}
	//打印文夹所有者的权限
	if( buf.st_mode & S_IWUSR )  {
		printf("r");
	}
	else printf("-");

	if( buf.st_mode & S_IWUSR )  {
		printf("w");
	}
	else printf("-");

	if( buf.st_mode & S_IXUSR )  {
		printf("x");
	}
	else printf("-");
	//打印文件所有者所在的组的权限
	if( buf.st_mode & S_IRGRP )  {
		printf("r");
	}
	else printf("-");

	if( buf.st_mode & S_IWGRP )  {
		printf("w");
	}
	else printf("-");

	if( buf.st_mode & S_IXGRP ) {
		printf("x");
	}
	else printf("-");

	//打印其他用户的权限
	if( buf.st_mode & S_IROTH )  {
		printf("r");
	}
	else printf("-");

	if( buf.st_mode & S_IWOTH )  {
		printf("w");
	}
	else printf("-");

	if( buf.st_mode & S_IXOTH )  {
		printf("x");
	}
	else printf("-");
	
	printf("   ");
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%d  ",buf.st_nlink);
	printf("%s   ",psd->pw_name);
	printf("%s   ",grp->gr_name);
	printf("%-6ld    ",buf.st_size);
	strcpy(buf_time,ctime(&buf.st_mtime));
//	if(strlen(buf_time)>=1)
	buf_time[strlen(buf_time) - 1] = '\0';
//	printf("%s  ",buf.st_mtime );	
	printf("%s   ",buf_time);
	printf("%s   ",ptr->d_name);
	printf("\n");
	
	}
	closedir(dir);

	return EXIT_SUCCESS;
}












