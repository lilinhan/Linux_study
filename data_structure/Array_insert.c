/*
 * =====================================================================================
 *
 *       Filename:  Array_insert.c
 *
 *    Description: 数组中随意的i处插入一个数
 *
 *        Version:  1.0
 *        Created:  07/21/2014 09:04:50 PM
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

int main(int argc, char *argv[])
{

	int a[20] = {1,2,3,4,5,6,7,8};
	int i = 0,k = 7,j;
	
	for(  ; k > 2 ; k-- )  {
		a[k+1] = a[k];
	}
	a[k+1] = 11;

	for ( i = 0 ; i < 20; i++ ) {
	printf("%d   ",a[i]);
	}
	printf("\n");
	k = 3;
	for( ; k < 5 ; k++ )   {
		a[k] = a[k+1];
	}  
	for ( i = 0 ; i < 20; i++ ) {
	printf("%d   ",a[i]);
	}
	return EXIT_SUCCESS;
}

