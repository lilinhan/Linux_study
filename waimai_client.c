/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *
 *    Description:  client
 *
 *        Version:  1.0
 *        Created:  2014年08月01日 15时04分31秒
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
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define MYPORT 4058
#define SERVICE_IP "222.24.51.8"
//#define SERVICE_IP "127.0.0.1"

struct data 
{
	char name[20];
	int money;
};

int connect_service()
{
	int socket_fd;
	struct sockaddr_in service_addr;
	char sentence[1000];

	socket_fd = socket( AF_INET , SOCK_STREAM , 0 );

	memset(&service_addr , 0 , sizeof(struct sockaddr_in));
	service_addr.sin_family = AF_INET;
	service_addr.sin_port = htons(MYPORT);
	if(inet_aton( SERVICE_IP , &service_addr.sin_addr ) == 0 )  {
		printf("invalid service ip!\n");
		exit(1);
	} 
	if((connect(socket_fd,(struct sockaddr *)(&service_addr),sizeof(struct sockaddr))) == -1 )  {
		perror("connect!\n");
		exit(0);
	}
	printf("connected!\n");

	return socket_fd;
}

void communacation(int socket_fd)
{
	char send_buf[1000];
	char recive_buf[1000];
	int size_recv;
	struct data customer;
	char quit[5];

	printf("欢迎使用linux小组定外买系统  哈哈哈哈 \n\n");
	if(!fork())  {
		while(1)  {
			printf("叫啥！吃多钱的！！！(姓名，6，7，8，务必按格式，不要调戏我!!!)\n\n");
			scanf("%s%d",customer.name,&customer.money);
			send( socket_fd ,(void *)&customer , sizeof(struct data), 0);
		}
	}
	if(!fork())   {
		
			if((size_recv = recv(socket_fd , recive_buf , sizeof(recive_buf) , 0 ))< 0 )  {
				perror("recv!\n");
				exit(0);
			}
			recive_buf[size_recv + 1] = '\0';
			printf("%s\n",recive_buf);


		
	}
	wait(NULL);
	exit(0);
}

int main(int argc, char *argv[])
{
	int socket_fd;

	socket_fd = connect_service();
	communacation(socket_fd);

	return EXIT_SUCCESS;
}
