/*
 * =====================================================================================
 *
 *       Filename:  my_pwd.c
 *
 *    Description:   Print the full filename of the current working directory by getcwd(),get_current_dir_name();
 *
 *        Version:  1.0
 *        Created:  07/15/2014 11:25:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李林翰, lilinhan1303@gmail.com    693465363@qq.com
 *        Company:  Class 1303 of  Xiyou Linux Group
 *
 * =====================================================================================
 */
#define _GNU_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf[50];
	char *c;
	getcwd(buf,50);
	printf("%s\n\n",buf);
	
	c = get_current_dir_name();
	printf("%s\n",c);
	return EXIT_SUCCESS;
}

