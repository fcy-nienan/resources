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
SOCKADDR_IN servAddr;//��������ַ
int retVal;//����Socket�����ķ���ֵ
char buf[BUF_SIZE];
int iMode=1;
//��ʼ��Socket����
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
printf("WSAStartup failed!\n");
return -1;
}
sHost=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//���÷�����Socket��ַ
servAddr.sin_family=AF_INET;
servAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
//��ʵ��Ӧ���У����齫��������IP��ַ�Ͷ˿ںű����������ļ���
servAddr.sin_port=htons(9990);
//�����ַ�ĳ���
int sServerAddlen=sizeof(servAddr);
//����ioctlsocket������������Ϊ������ģʽ
retVal=ioctlsocket(sHost,FIONBIO,(u_long FAR*)&iMode);
if(retVal==SOCKET_ERROR)
{
printf("ioctlsocket failed!");
WSACleanup();
return -1;
}


//ѭ���ȴ�
while(true)
{
//���ӵ�������
retVal=connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));
if(SOCKET_ERROR==retVal)
{
int err=WSAGetLastError();
//�޷�������ɷ�����Socket�ϵĲ���
if(err==WSAEWOULDBLOCK||err==WSAEINVAL)
{
Sleep(5);
continue;
}
else if(err==WSAEISCONN)//�ѽ�������
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
//������������ַ���������ʾ������Ϣ
printf("input a string to send:\n");
std::string str;
//�������������
std::getline(std::cin,str);
//���û���������ݸ��Ƶ�buf��
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
//�޷�������ɷ�����Socket�ϵĲ���
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
ZeroMemory(buf,BUF_SIZE);//��ս������ݵĻ�����
retVal=recv(sHost,buf,sizeof(buf)+1,0);
if(SOCKET_ERROR==retVal)
{
int err=WSAGetLastError();
//�޷�������ɷ�����Socket�ϵĲ���
if(err==WSAEWOULDBLOCK)
{
Sleep(5000);
printf("waiting back msg!\n");
continue;
}
else if(err==WSAETIMEDOUT||err==WSAENETDOWN)//�ѽ�������
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
//������յ�quit�����˳�
if(strcmp(buf,"quit")==0)
{
printf("quit!\n");
break;
}
}
return 0;
}



