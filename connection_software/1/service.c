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
#include <pthread.h>
#include <dirent.h>
#include <errno.h>


#define MYPORT 4058
//#define SERVICE_IP "222.24.51.8"

struct user_information
{
	char id[20];
	int fd;
};


void

//创建一个套接字绑定端口，并且设置监听状态
static int socket_bind()
{
	int socket_fd;
	int optval = 1;
	struct sockaddr_in service_addr,client_addr;


	socket_fd = socket( AF_INET , SOCK_STREAM , 0 );
	
	setsockopt( socket_fd , SOL_SOCKET ,SO_REUSEADDR , (void *)&optval , sizeof(int));

	memset( &service_addr , 0 , sizeof(struct sockaddr_in));
	service_addr.sin_family = AF_INET;
	service_addr.sin_port = htons(MYPORT);
	service_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind( socket_fd ,(struct sockaddr *)&service_addr , sizeof(struct sockaddr_in));
	listen(socket_fd , 10);

	return socket_fd;
}

//客户端连接，将套接字保存到一个数组中
static handle_ask( int socket_fd )
{
	fd_set fdsr , fdsw;
	int num_client;
	int maxsock;
	int i;
	int ret;
	int conn_client = 0;
	struct user_information info[100];//用来保存全部的文件描述符
	char buf[1000];
	int new_fd;
	int size_buf;
	struct sockaddr_in client_addr;
	socklen_t sin_size;
	
	maxsock = socket_fd;

	for( i = 0 ; i < 100 ; i++ )  {
		info[i].fd = 0;
	}

	while(1)  {
		//初始化文件描述符集合
		FD_ZERO(&fdsr);
		//将监听端口的文件描述符也存入到文件描述符集合中，用来接收连接请求
		FD_SET(socket_fd , &fdsr);
		
		for( i = 0 ; i < 100 ; i++ )  {
			if(info[i].fd != 0 )   {
				FD_SET(info[i].fd ,&fdsr);
			}

		}

		ret = select(maxsock+1 , &fdsr , NULL , NULL , NULL );
		if( ret < 0 )   {
			perror("select error!n\n");
			break;
		}
		else if( ret == 0 )  {
			continue;
		}

//判断有没有新的连接请求，并加入到描述符保存数组fd中
		if(FD_ISSET(socket_fd,&fdsr))   {
			new_fd = accept(socket_fd , (struct sockaddr*)&client_addr , &sin_size);
			if(new_fd <= 0 )  {
				perror("accept error\n");
				continue;
			}
		

//将新的描述符添加到数组中 判断连接数会不会超
			if( num_client < 100 )  {
				for( i = 0 ; i < 100 ; i++ )   {
					if(info[i].fd == 0 )  {
						info[i].fd = new_fd;
						break;
					}
				}
				num_client++;
				if( new_fd > maxsock )  {
					maxsock = new_fd;
				}
			}
			
		}

	}
}

	

int main(int argc, char *argv[])
{ 

	int socket_fd;

	socket_fd = socket_bind();
	handle_ask(socket_fd);

	return EXIT_SUCCESS;
}

//转发消息
/*void trans_send()
{
	
		for( i = 0 ; i < num_client ; i++ )  {
			if(FD_ISSET(fd[i] , &fdsr))  {
				ret = recv(fd[i] , buf ,sizeof(buf),0);
				if( ret <= 0 )  {
					printf("client[i] close\n",i);
					close(fd[i]);
					FD_CLR(fd[i],&fdsr);
					fd[i] = 0;
					num_client--;
				}
				else  {
					if( ret < 1000 )  
						memset(&buf[1000],'\0',1);
					printf("client[i] send:%s\n",buf);
				}
			}
		}
}
*/
