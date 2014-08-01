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
#define SERVICE_IP "222.24.51.100"
//#define SERVICE_IP "127.0.0.1"

int main(int argc, char *argv[])
{
	int client_fd , socket_fd  ;
	struct sockaddr_in service_addr , client_addr;
	char recv_buf[1000];
	int size_of_data;


//	创建一个套接字
	if((socket_fd = socket( AF_INET , SOCK_STREAM , 0 )) < 0 )  {
		perror("socket\n");
		exit(0);
	}
	

//	将套接字初始化
	memset(&service_addr , 0 , sizeof(struct sockaddr_in));
	service_addr.sin_family = AF_INET;
	service_addr.sin_port = htons(MYPORT);
	if(inet_aton( SERVICE_IP , &service_addr.sin_addr ) == 0 )  {
		printf("invalid server ip adress\n");
		exit(1);
	}	

//	while(1)  {
	if((connect(socket_fd , (struct sockaddr*)(&service_addr) , sizeof(struct sockaddr))) == -1 )  {
		//fprintf(stderr,"connect erro\n",strerror(errno));
		perror ("connect error ") ;
		exit(0);
	}
	printf ("Connected \n") ;
	if((size_of_data = recv(socket_fd , recv_buf , sizeof(recv_buf) , 0 )) < 0  )  {
		perror("recv\n");
		exit(1);
	}
	recv_buf[size_of_data] = '\0';

	printf("%s\n",recv_buf);
//	}
	return EXIT_SUCCESS;
}
