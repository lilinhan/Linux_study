/*
 * =====================================================================================
 *
 *       Filename:  test_address.c
 *
 *    Description:  p296
 *
 *        Version:  1.0
 *        Created:  2014年08月03日 10时04分00秒
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char buffer[32];
	int ret = 0 ;
	int host = 0;
	int network = 0;
	unsigned int address = 0;
	struct in_addr in;

	in.s_addr = 0;

	//输入一个以“.”分隔的字符串形式的IP地址
	printf("please input your ip adress:");
	fgets(buffer , 31, stdin);
	buffer[31] = '\0';
	//使用inet_aton函数
	if(( ret = inet_aton(buffer,&in)) == 0)   {
		printf("inet_aton:  \t invalid adress\n");
	}
	else   {
		printf("inet_aton:  \t0x%x\n",in.s_addr);
	}

	//使用inet_addr函数
	if((address = inet_addr(buffer)) == INADDR_NONE )  {
		printf("inet_addr:  \t invalid address\n");
	}
	else   {
		printf("inet_addr:  \t0x%lx\n",in.s_addr);
	}


	//使用inet_network函数
	if((address = inet_network(buffer)) == -1)  {
		printf("inet_network: \t invalid address\n");
	}
	else   {
		printf("inet_network: \t0x%lx\n",in.s_addr);
	}


	//使用inet_ntoa函数
	if(inet_ntoa(in) == NULL)   {
		printf("inet_nota: \t invalid address\n");
	}
	else   {
		printf("inet_ntoa: \t%s\n",inet_ntoa(in));
	}


	//使用inet_lnaof函数 和 inet_netof函数
	host = inet_lnaof(in);
	network = inet_netof(in);
	printf("inet_inaof :\t0x%x\n",host);
	printf("inet_netof :\t0x%x\n",network);

	in = inet_makeaddr(network , host);
	printf("inet_makeaddr: 0x%x\n" ,in.s_addr);



	return EXIT_SUCCESS;
}

