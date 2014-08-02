/*
 * =====================================================================================
 *
 *       Filename:  service.c
 *
 *    Description:  connection software
 *
 *        Version:  1.0
 *        Created:  2014年08月01日 10时35分06秒
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
#include <sys/stat.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MYPORT 4058
//#define SERVICE_IP "222.24.51.8"


int main(int argc, char *argv[])
{

	int sock_fd , client_fd , new_fd;
	int client_len,k,sizeof_data;
	char send_sentence[1000],receive_sentence[1000];
	struct sockaddr_in service_addr , client_addr;
	pid_t pid;

//	创建一个套接字
	if(( sock_fd = socket(AF_INET , SOCK_STREAM , 0 )) < 0 )   {
		perror("socket\n");
		exit(-1);
	}

//	将套接字的地址初始化以及绑定端口bind();
	memset(&service_addr , 0 , sizeof(struct sockaddr_in));
	service_addr.sin_family = AF_INET;
	service_addr.sin_port = htons(MYPORT);
	service_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind( sock_fd , (struct sockaddr *)&service_addr , sizeof(struct sockaddr_in)) < 0 )  {
		perror("bind\n");
		exit(1);
	}

//	在套接字上监听
	if(listen(sock_fd , 10 ) < 0 )	{
		perror("listen\n");
		exit(0);
	}

//	服务器接收客户端的请求
	while(1)  {
		client_len = sizeof(struct sockaddr_in);
		if((client_fd = accept( sock_fd , (struct sockaddr *)&client_addr,&client_len)) < 0 )  {
			perror("accept\n");
			exit(0);
		}
		printf("accept a new client connection , ip:%s\n",inet_ntoa(client_addr.sin_addr));

	if((pid = fork())== 0 )  {
		while(1)  {
//	给程序端发送数据
	      		printf("my sentence:\t");
			gets(send_sentence);
		      if( k = (send(client_fd,send_sentence,sizeof(send_sentence), 0 )) < 0 )  {
	      			perror("send\n");
				exit(0);
		      }

		      //从程序端收数据
		      printf("client :\t");
		      if((sizeof_data = recv(client_fd,receive_sentence,sizeof(receive_sentence),0)) < 0 )   {
		      		perror("recv\n");
				exit(0);
		      }
		      receive_sentence[sizeof_data+1] = '\0';
		      printf("%s\n",receive_sentence);

		}
		close(client_fd);
	}
	wait(NULL);
	exit(0);
	}
	return EXIT_SUCCESS;
}

