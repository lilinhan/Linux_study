/*
* =====================================================================================
*
* Filename: client.c
*
* Description: client
*
* Version: 1.0
* Created: 2014年08月01日 15时04分31秒
* Revision: none
* Compiler: gcc
*
* Author: 李林翰, lilinhan1303@gmail.com 693465363@qq.com
* Company: Class 1303 of Xiyou Linux Group
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
#include <pthread.h>
#define MYPORT 4058
#define SERVICE_IP "222.24.51.8"
//#define SERVICE_IP "127.0.0.1"
struct send_buf
{
	int flag;
	char id[20];
	char from[20];
	char data[1000];
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

char id[20];
void creat_user( int client_fd )
{
	char tip[50];
	struct self_data data_self;
	char s[5];	
	while(1) {
		memset(&data_self , 0 , sizeof(struct self_data));
		data_self.flag = 1;
		printf("\n请输入您的用户名:");
		scanf("%s",data_self.id);
		send( client_fd , &data_self , sizeof(struct self_data) , 0 );
		memset(tip , 0 , sizeof(tip));
		recv( client_fd , tip , sizeof(tip) , 0 );
		printf("%s\n",tip);
		if(strcmp(tip,"恭喜您,该用户不存在") == 0) {
			printf("请输入密码:");
			system("stty -echo");
			scanf("%s",data_self.passwd);
			system("stty echo");
			printf("\n请输入姓名，年龄，生日:\n");
			getchar();
			scanf("%s%s%s",data_self.name,data_self.age,data_self.birthday);
			printf("%d %s %s %s %s %s\n",data_self.flag,data_self.name,data_self.id,data_self.passwd,data_self.age,data_self.birthday);
			strcmp(id,data_self.id);
			send( client_fd , &data_self , sizeof(struct self_data) , 0 );
		break;
		}
		printf("\n按任意健继续,返回上级输入quit\n");
		scanf("%s",s);
		if(strcmp(s,"quit")== 0 ) {
			login_interface(client_fd);
		}
	}
}

void confirm_user( int client_fd )
{
	char tip[50];
	char s[5];
	struct self_data data_self;
	memset(&data_self , 0 , sizeof(struct self_data));
	data_self.flag = 2;
	send( client_fd , &data_self , sizeof(struct self_data) , 0 );
	while(1) {
		memset(&data_self , 0 , sizeof(struct self_data));	
		printf("\n请输入您的用户名:");
		scanf("%s",data_self.id);
		printf("\n请输入密码:");
		system("stty -echo");
		scanf("%s",data_self.passwd);
		system("stty echo");
		send( client_fd , &data_self , sizeof(struct self_data) , 0 );
		memset(tip , 0 , sizeof(tip));
		recv( client_fd , tip , sizeof(tip) , 0 );
		printf("%s\n",tip);
		if(strcmp(tip,"登陆成功!") == 0) {
			strcpy(id,data_self.id);
			break;
		}
		printf("\n按任意健继续，返回上级输入quit\n");
		scanf("%s",s);
		if(strcmp(s,"quit")== 0 ) {
			login_interface(client_fd);
		}
	}
}

int login_interface(int client_fd)
{
	int i;
	printf("1 创建用户\n");
	printf("2 用户登陆\n");
	printf("3 退出\n");
	scanf("%d",&i);
	if( i == 1) {
		creat_user(client_fd);
	}
	else if( i == 2 ) {
		confirm_user(client_fd );
	}
	else {
		exit(0);
	}
}

int creatsocket()
{
	int client_fd;
	struct sockaddr_in service_addr;
	if((client_fd = socket( AF_INET , SOCK_STREAM , 0)) < 0 ) {
		perror("socket\n");
		exit(0);
	}

	memset(&service_addr , 0 , sizeof(service_addr));
	service_addr.sin_family = AF_INET;
	service_addr.sin_port = htons(MYPORT);
	if(inet_aton( SERVICE_IP ,&service_addr.sin_addr) == 0 ) {
		printf("invalid service ip adress\n");
		exit(0);
	}
	if((connect(client_fd,(struct sockaddr*)(&service_addr) , sizeof(struct sockaddr))) == -1 ) {
		perror("connect\n");
		exit(0);
	}
	else {
		printf("connected\n");
		return client_fd;
	}
}
void* recv_mesg(void* client_fd)
{
	struct send_buf buf;
	FILE * fp;

	while(1) {
		memset( &buf , 0 , sizeof(struct send_buf) );
		recv(*(int*)client_fd , &buf , sizeof(struct send_buf) , 0 );
		printf("\n%s:%s\n",buf.from,buf.data);
		fp = fopen("chat_record","a+");
		fprintf(fp,"%s:%s\n",buf.from,buf.data);
		fclose(fp);
		fflush(stdout);
	}
}

void chat(int client_fd)
{
	struct send_buf buf;
	char s[20];

	FILE * fp;
	memset(&buf , 0 ,sizeof(struct send_buf));
	buf.flag = 1;
	while(1) {
		printf("%s\n",buf.data);
		printf("你要跟谁聊天?\n");
		scanf("%s",buf.id);
		printf("聊天结束请输quit\n");
		while(1) {
			printf("me:");
			scanf("%s",buf.data);
			fp = fopen("chat_record","a+");
			fprintf(fp,"me:%s    to %s\n",buf.data,buf.id);
			fclose(fp);
			if(strcmp(buf.data,"quit") == 0 ) {
				break;
			}
			strcpy(buf.from,id);
			send(client_fd , &buf , sizeof(struct send_buf) , 0 );
		}
		printf("按任意健选择他人聊天，退出聊天请输入quit\n");
		scanf("%s",s);
		if(strcmp(s,"quit") == 0 ) {
		break;
		}
	}
}

void chat_group(int client_fd)
{
	struct send_buf buf;
	char s[20];

	FILE * fp;
	memset(&buf , 0 ,sizeof(struct send_buf));
	buf.flag = 2;
	strcpy(buf.id,"group");
	strcpy(buf.from,id);
	
	printf("聊天结束请输quit\n");
	while(1) {
		printf("me:");
		scanf("%s",buf.data);
		fp = fopen("chat_record","a+");
		fprintf(fp,"me:%s    to others!\n",buf.data);
		fclose(fp);
		if(strcmp(buf.data,"quit") == 0 ) {
			break;
		}
		send(client_fd , &buf , sizeof(struct send_buf) , 0 );
		}
}
void functions(int client_fd)
{
	int i;
	printf("1 私聊\n");
	printf("2 群聊\n");
	printf("0 退出\n");
	scanf("%d",&i);
	switch(i) {
		case 1:chat(client_fd);break;
		case 2:chat_group(client_fd);break;
		case 0:exit(0);break;
	}
}

int main(int argc, char *argv[])
{
	int client_fd;
	int flag;
	
	chdir("/home/llh/code/boss");
	pthread_t tid;
	client_fd = creatsocket();
	login_interface(client_fd);
	if(pthread_create(&tid , NULL ,(void *)recv_mesg , (void *)&client_fd ) != 0 ) {
		printf("Creat pthread error!\n");
		exit(0);
	}
	functions(client_fd);
	return EXIT_SUCCESS;
}
