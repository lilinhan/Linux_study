/*
 * =====================================================================================
 *
 *       Filename:  fianlls.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2014 11:04:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */

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
#include <unistd.h>

#define MAX_LINE  50

void my_err( const char * err_string , int line )
{
	fprintf( stderr , "line :%d" , line );
	perror("err_string");
	exit(0);
}

void ls_a( char *argv )
{
	DIR * dir;
	struct dirent *ptr,*ptr1;
	struct stat buf;
	int sure_len = 0 , i , j , m, n, MAX_FILE_NAME = 0,LAST_LETTER,NUMBER_OF_FILE = 0;
	//测试文件夹里面文件的个数，以及最长文件名字的长度
	if(( dir = opendir(argv)) == NULL )  {
		perror("opendir");
		exit(0);
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
	if(( dir = opendir(argv)) == NULL )  {
		perror("opendir");
		exit(0);
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
	printf("\n\n\n");
}


void ls( char *argv )
{
	DIR * dir;
	struct dirent *ptr,*ptr1;
	struct stat buf;
	int sure_len = 0 , i , j , m, n, MAX_FILE_NAME = 0,LAST_LETTER,NUMBER_OF_FILE = 0;
	//测试文件夹里面文件的个数，以及最长文件名字的长度
	if(( dir = opendir(argv)) == NULL )  {
		perror("opendir");
		exit(0);
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
	if(( dir = opendir(argv)) == NULL )  {
		perror("opendir");
		exit(0);
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

		if(FILE_NAME[j][0] == '.')  {
			j++;
			continue;
		}
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
}


void ls_l(char *argv)
{
	DIR * dir;
	struct dirent *ptr;
	struct passwd * psd;
	struct group * grp;
	struct stat buf;
	char buf_time[32];

	if(((dir = opendir(argv)) == NULL) )  {
		perror("opendir");
		exit(0);
	}

	chdir(argv);
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
	printf("%-d  ",buf.st_nlink);
	printf("%-6s   ",psd->pw_name);
	printf("%-6s   ",grp->gr_name);
	printf("%-6ld    ",buf.st_size);
	strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';
	printf("%s   ",buf_time);
	printf("%s   ",ptr->d_name);
	printf("\n");
	
	}
	closedir(dir);


}

int ls_r(char * argv)
{
	DIR * dir;
	struct dirent *ptr, *ptr1;
	struct stat buf;

	ls(argv);
	if((dir = opendir(argv)) == NULL )  {
		perror("opendir");
		exit(1);
	}
	chdir(argv);
	while((ptr1 = readdir(dir)) != NULL )  {
		lstat(ptr1->d_name,&buf);
		if(S_ISDIR(buf.st_mode))  {
			if( strcmp(ptr1->d_name,".") == 0 || strcmp(ptr1->d_name,"..") == 0) {
				continue;
			}
			if(ptr1->d_name[0] != '.')  {
			printf("\n%s:\n",ptr1->d_name);
			ls_r(ptr1->d_name);
			printf("\n\n");
			}
		}
	}
	closedir(dir);
	chdir("..");
	return 0;
}

int main(int argc, char * argv[])
{
	char add_directory[100];
	int flag;    //flag确定进入哪个函数  0：ls  1：ls -a    2：ls -l  3：ls -R
	getcwd(add_directory,100);
	
	if( argc == 1 )  {
		flag = 0;

	}
	else if( 2 == argc )  { 
		if( argv[1][0] == '-')   {
			if( argv[1][1] == 'a' )  {
		      		flag = 1;
		        }
			else if( argv[1][1] == 'l' )  {
				flag = 2;
			}
			else if( argv[1][1] == 'R' )  {
				flag = 3;
			}
			else  {
				printf("my_ls <options> -a -l -R");
			}
		}
	}
	else if( 3 == argc )  {
			if( argv[1][1] == 'a' )  {
		      		flag = 4;
		        }
			else if( argv[1][1] == 'l' )  {
				flag = 5;
			}
			else if( argv[1][1] == 'R' )  {
				flag = 6;
			}
			else  {
				printf("my_ls <options> -a -l -R <path>");
			}
	}
	else  {
		printf("my_ls <options>");
	}
	
	switch(flag)  {
		case 0:ls(add_directory);break;
		case 1:ls_a(add_directory);break;
		case 2:ls_l(add_directory);break;
		case 3:ls_r(add_directory);break;
		case 4:ls_a(argv[2]);break;
		case 5:ls_l(argv[2]);break;
		case 6:ls_r(argv[2]);break;
	};
	
	return 0 ;
}
