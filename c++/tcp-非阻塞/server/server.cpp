#include<WINSOCK2.H>
#include<iostream>
using namespace std;
#include<stdlib.h>
#define BUF_SIZE 64
#pragma comment(lib,"WS2_32.lib")
int main()
{
WSADATA wsd;
SOCKET sServer;
SOCKET sClient;
int retVal;//调用Socket函数的返回值
char buf[BUF_SIZE];


//初始化Socket环境
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
printf("WSAStartup failed!\n");
return 1;
}
//创建监听的Socket
sServer=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(INVALID_SOCKET==sServer)
{
printf("socket failed!\n");
WSACleanup();
return -1;
}
//设置服务器Socket地址
SOCKADDR_IN addrServ;
addrServ.sin_family=AF_INET;
addrServ.sin_port=htons(9990);
addrServ.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
//绑定Sockets Server
retVal=bind(sServer,(const struct sockaddr*)&addrServ,sizeof(SOCKADDR_IN));
if(SOCKET_ERROR==retVal)
{
printf("bind failed!\n");
closesocket(sServer);
WSACleanup();
return -1;
}
//在Sockets Server上进行监听
retVal=listen(sServer,1);
if(SOCKET_ERROR==retVal)
{
printf("listen failed!\n");
closesocket(sServer);
WSACleanup();
return -1;
}
//设置Socket为非阻塞模式
int iMode = 1;
retVal = ioctlsocket(sServer,FIONBIO,(u_long FAR*) &iMode);
if(retVal == SOCKET_ERROR)
{
printf("ioctlsocket failed!\n");
WSACleanup();
return -1;
}
//接受来自客户端的请求
printf("TCPServer start...\n");
sockaddr_in addrClient;
int addrClientlen=sizeof(addrClient);
while(true)
{
sClient=accept(sServer,(sockaddr FAR*)&addrClient,&addrClientlen);
if(INVALID_SOCKET == sClient)
{
printf("暂时没有客户端连接");
int err = WSAGetLastError();
if(err == WSAEWOULDBLOCK)
{
Sleep(5);
continue;
}
else
{
printf("accept failed!\n");
closesocket(sServer);
WSACleanup();
return -1;
}
}
break;
}
while(true)
{
ZeroMemory(buf,BUF_SIZE);
retVal = recv(sClient,buf,BUF_SIZE,0);
if(SOCKET_ERROR == retVal)
{
	printf("暂时没有数据来");
int err = WSAGetLastError();
if(err == WSAEWOULDBLOCK)
{
Sleep(5);
continue;
}
else if(err == WSAETIMEDOUT || err == WSAENETDOWN)
{
printf("recv failed!\n");
closesocket(sServer);
closesocket(sClient);
WSACleanup();
return -1;
}
}
SYSTEMTIME st;
GetLocalTime(&st);
char sDateTime[30];
sprintf(sDateTime,"%4d-%2d-%2d-%2d:%2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
//打印输出的信息
printf("%s,Recv From Client [%s:%d]:%s\n",sDateTime,inet_ntoa(addrClient.sin_addr),addrClient.sin_port,buf);
//如果客户端发送quit字符串，则服务器退出
if(strcmp(buf,"quit")==1)//////////////////////////////////////////
{
retVal=send(sClient,"quit",strlen("quit"),0);
break;
}
//否则向客户端发送回显字符串
else
{
char msg[BUF_SIZE];
sprintf(msg,"Message received - %s\n",buf);
while(true)
{
retVal = send(sClient,msg,strlen(msg),0);
if(SOCKET_ERROR == retVal)
{
int err = WSAGetLastError();
if(err == WSAEWOULDBLOCK)
{
Sleep(5);
continue;
}
else
{
printf("send failed!\n");
closesocket(sServer);
closesocket(sClient);
WSACleanup();
return -1;
}
}
}
break;
}
}
}