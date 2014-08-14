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
#define MAXFDS 100
//#define SERVICE_IP "222.24.51.8"

struct keepsock_list
{
	int flag;
	char id[20];
	int socket_fd;
};

struct data
{
	int flag;
	char alldata[2048];
};

struct self_data
{
	int flag;
	char name[20];
	char id[20];
	char passwd[20];
	char age[5];
	char birthday[20];
};

struct chat
{
	int flag;
	char id[20];
	char from[20];
	char sentence[1000];
};


struct keepsock_list fds[MAXFDS];
int x = 0;

void creat_user( int new_fd ,struct self_data data_self)
{
	DIR * dir;
	struct dirent* ptr;
	FILE * filename;
	int flag = 0;
	int i = 0;

	chdir("/home/llh/code/connection_software/1");
	while(flag != 1)  {
		dir = opendir("user_informations");
		while((ptr = readdir(dir)) != NULL )  { 
			if(strcmp( data_self.id , ptr->d_name ) == 0)  {
				i = 1;
				break;
			}
		}	

		if( i == 1) {
			send( new_fd , "该用户存在", 15 , 0);
			memset(&data_self,0,sizeof(struct self_data));
			recv( new_fd , &data_self , sizeof(struct self_data ), 0 );
		}

		if ( i == 0 ) {
			send( new_fd , "恭喜您,该用户不存在", 30 , 0);
			chdir("/home/llh/code/connection_software/1/user_informations");
			memset(&data_self,0,sizeof(struct self_data));
			recv(new_fd , &data_self , sizeof(struct self_data) , 0);
			filename = fopen(data_self.id ,"w");
			fprintf(filename ,"%s   %s   %s   %s  %s\n" ,data_self.name , data_self.id , data_self.passwd, data_self.age , data_self.birthday);
			fclose(filename);
			flag++;
			if( x <= MAXFDS )  {
				fds[x].flag = 1;
				fds[x].socket_fd = new_fd ;
				strcpy(fds[x].id,data_self.id);
				x++;
			}
			else  {
				send(new_fd , "用户过多" , 20 , 0);
			}
		}
		
	}


}


int confirm_user( int new_fd , struct self_data data_self )
{
	DIR * dir;
	struct dirent* ptr;
	FILE * filename;
	struct self_data compare;
	int flag = 0 , i = 0 ,j = 0;
	
	x = 0;
	chdir("/home/llh/code/connection_software/1");
	while(1)  {
		dir = opendir("user_informations");
		memset(&data_self,0,sizeof(struct self_data ));
		recv(new_fd , &data_self , sizeof(struct self_data) , 0);

		while((ptr = readdir(dir)) != NULL )  {
			if(strcmp( data_self.id , ptr->d_name ) == 0)  {
				i = 1;
			}
			if(ptr->d_name[0] != '.') {
				x++;
			}
		}	

		if( i == 1 ) {
			chdir("/home/llh/code/connection_software/1/user_informations");
			filename = fopen(data_self.id ,"r");
			fscanf( filename ,"%s  %s  %s  %s  %s\n" , compare.name,compare.id,compare.passwd,compare.age,compare.birthday);
			fclose(filename);
			flag =1;

		}
		else if( i == 0 ) {		
			send(new_fd , "该用户不存在",20, 0);
		}

		if(flag == 1)
			if(strcmp(compare.passwd ,data_self.passwd) == 0)  {
				send( new_fd , "登陆成功!", 20 , 0);
				for( j = 0 ; j <= x ; j++ )  {
					if( (fds[j].socket_fd == 0)  || (strcmp(fds[j].id , data_self.id) == 0 ))  {
						strcpy(fds[j].id , data_self.id);
						fds[j].socket_fd = new_fd ;
						fds[j].flag = 1;
						break;
					}
				}
				return 1;
			}
			else  {
				send( new_fd , "密码错误!", 20 , 0);
			}
	}
}


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
	fd_set fdsr;
	int num_client = 0;
	int maxsock;
	int i , j , m;
	int ret;
	int conn_client = 0;
	int fd[MAXFDS];//用来保存全部的文件描述符
	int new_fd;
	int size_buf;
	struct sockaddr_in client_addr;
	struct self_data data_self;
	struct chat buf;
	socklen_t sin_size;
	struct timeval tv;
	
	maxsock = socket_fd;

	tv.tv_sec = 5;
	memset(fd,0,sizeof(fd));
	while(1)  {
		//初始化文件描述符集合
		FD_ZERO(&fdsr);
		//将监听端口的文件描述符也存入到文件描述符集合中，用来接收连接请求
		FD_SET(socket_fd , &fdsr);
		

		for( i = 0 ; i < num_client ; i++ )  {
			if(fd[i] != 0 )   {
				FD_SET(fd[i],&fdsr);
			}

		}

		ret = select(maxsock+1 , &fdsr , NULL , NULL , &tv );
		if( ret < 0 )   {
			perror("select error!n\n");
			break;
		}

		else if( ret == 0 )  {
			continue;
			printf("hello\n");
		}else {
			num_client++;
		} 
		
		for( i = 0 ; i < num_client ; i++ )  {
			if(FD_ISSET(fd[i] , &fdsr))  {
				memset(&buf, 0, sizeof(buf));
				ret = recv(fd[i] , &buf ,sizeof(buf),0);
				if( ret <= 0 )  {
					num_client--;
					printf("client[%d] close\n",i);
					close(fd[i]);
					FD_CLR(fd[i],&fdsr);
					fd[i] = 0;
					fds[i].flag = 0;
				}
				else  {
					if(buf.flag == 1)  {
						printf("%s send:%s  to %s\n",buf.from,buf.sentence,buf.id);
						for( j = 0 ; j < num_client ; j++ )  {
							if(strcmp(fds[j].id , buf.id) == 0)  {
								send( fds[j].socket_fd , &buf , sizeof(struct chat) , 0 );
							}
						}
					}
					else if(buf.flag == 2)  {
						
					}
					else if(buf.flag == 3)  {
					
					}
					else if(buf.flag == 4)  {
					
					}
					
					continue;
				}

/*				if( num_client < 100 )  {
					for( i = 0 ; i < 100 ; i++ )   {
						for( j = 0 ; j < num_client ; j++ )  {
							if(fd[j] == fd[i]) {
								continue;
							}
							else  {
								send(fd[j] , &buf , sizeof(buf) , 0);
							}
						}
					}
				}
*/				
			}

		}
		
//判断有没有新的连接请求，并加入到描述符保存数组fd中
		if(FD_ISSET(socket_fd,&fdsr))   {
			new_fd = accept(socket_fd , (struct sockaddr*)&client_addr , &sin_size);
			if(new_fd <= 0 )  {
				perror("accept error\n");
				continue;
			}
			//将新的描述符添加到数组中 判断连接数会不会超

			memset(&data_self ,0, sizeof(struct self_data));
			recv( new_fd , &data_self , sizeof(struct self_data) , 0);
				if (data_self.flag == 1) {
					creat_user(new_fd ,data_self);
				} 
				else if ( data_self.flag == 2 ) {
					ret = confirm_user(new_fd ,data_self);
					if (ret != 1) {
						continue;
					}
				}

			if( num_client < MAXFDS )  {
				for( i = 0 ; i < 100 ; i++ )   {
					if(fd[i] == 0 )  {
						fd[i] = new_fd;
						break;
					}
				}
				printf("a new client connetced! client[%d]%s:%d\n",num_client,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
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

