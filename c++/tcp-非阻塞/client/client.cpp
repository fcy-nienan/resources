#include<WINSOCK2.H>
#include<iostream>
#include<string>
using namespace std;
#include<stdlib.h>
#define BUF_SIZE 64
#pragma comment(lib,"WS2_32.lib")
int main()
{
WSADATA wsd;
SOCKET sHost;
SOCKADDR_IN servAddr;//服务器地址
int retVal;//调用Socket函数的返回值
char buf[BUF_SIZE];
int iMode=1;
//初始化Socket环境
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
printf("WSAStartup failed!\n");
return -1;
}
sHost=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//设置服务器Socket地址
servAddr.sin_family=AF_INET;
servAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
//在实际应用中，建议将服务器的IP地址和端口号保存在配置文件中
servAddr.sin_port=htons(9990);
//计算地址的长度
int sServerAddlen=sizeof(servAddr);
//调用ioctlsocket（）将其设置为非阻塞模式
retVal=ioctlsocket(sHost,FIONBIO,(u_long FAR*)&iMode);
if(retVal==SOCKET_ERROR)
{
printf("ioctlsocket failed!");
WSACleanup();
return -1;
}


//循环等待
while(true)
{
//连接到服务器
retVal=connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));
if(SOCKET_ERROR==retVal)
{
int err=WSAGetLastError();
//无法立即完成非阻塞Socket上的操作
if(err==WSAEWOULDBLOCK||err==WSAEINVAL)
{
Sleep(5);
continue;
}
else if(err==WSAEISCONN)//已建立连接
{
break;
}
else
{
printf("connection failed!\n");
closesocket(sHost);
WSACleanup();
return -1;
}
}
}
while(true)
{
//向服务器发送字符串，并显示反馈信息
printf("input a string to send:\n");
std::string str;
//接收输入的数据
std::getline(std::cin,str);
//将用户输入的数据复制到buf中
ZeroMemory(buf,BUF_SIZE);
strcpy(buf,str.c_str());
while(true)
{
retVal=send(sHost,buf,strlen(buf),0);
if(SOCKET_ERROR==retVal)
{
int err=WSAGetLastError();
if(err==WSAEWOULDBLOCK)
{
//无法立即完成非阻塞Socket上的操作
Sleep(5);
continue;
}

else
{
printf("send failed!\n");
closesocket(sHost);
WSACleanup();
return -1;
}
}
break;
}
while(true)
{
ZeroMemory(buf,BUF_SIZE);//清空接收数据的缓冲区
retVal=recv(sHost,buf,sizeof(buf)+1,0);
if(SOCKET_ERROR==retVal)
{
int err=WSAGetLastError();
//无法立即完成非阻塞Socket上的操作
if(err==WSAEWOULDBLOCK)
{
Sleep(5000);
printf("waiting back msg!\n");
continue;
}
else if(err==WSAETIMEDOUT||err==WSAENETDOWN)//已建立连接
{
printf("recv failed!");
closesocket(sHost);
WSACleanup();
return -1;
}
break;
}
break;
}
ZeroMemory(buf,BUF_SIZE);
retVal=recv(sHost,buf,sizeof(buf)+1,0);
printf("Recv from Server:%s\n",buf);
//如果接收到quit，则退出
if(strcmp(buf,"quit")==0)
{
printf("quit!\n");
break;
}
}
return 0;
}



