#include"util.h"  
  
void handle_connection(int sockfd)  
{  
    fd_set readfds;  
    int maxfd = sockfd;  
    struct timeval tv;  
  
    while(1)  
    {  
        //将描述符集合清空  
        FD_ZERO(&readfds);  
        FD_SET(sockfd,&readfds);  
        maxfd = sockfd;  
        tv.tv_sec = 5;  
        tv.tv_usec = 0;  
  
        int res = select(maxfd + 1,&readfds,NULL,NULL,&tv);  
        if(res == -1)  
        {  
            perror("select");  
            return;  
        }  
        if(res == 0)  
        {  
            printf("client time out.\n");  
            continue;  
        }  
        int n;  
        char recvbuf[256];  
        if(FD_ISSET(sockfd,&readfds))  
        {  
            n = recv(sockfd,recvbuf,256,0);  
            //n小于0说明服务器关闭  
            if(n <= 0)  
            {  
                printf("server is closed.\n");  
                close(sockfd);  
                FD_CLR(sockfd,&readfds);  
                return ;  
            }  
            printf("client recv self msg:>%s\n",recvbuf);  
            //sleep(3);  
            char sendbuf[256];  
            scanf("%s",sendbuf);  
            send(sockfd,sendbuf,strlen(sendbuf)+1,0);  
        }  
    }  
}  
  
int main(int argc,char*argv[])  
{  
    int sockCli;  
    //创建套接字  
    sockCli = socket(AF_INET,SOCK_STREAM,0);  
    struct sockaddr_in addrSer;  
    addrSer.sin_family = AF_INET;  
    addrSer.sin_port = htons(PORT);  
    addrSer.sin_addr.s_addr = inet_addr(IPADDR);  
  
    socklen_t addrlen = sizeof(struct sockaddr);  
    //连接服务器  
    int res = connect(sockCli,(struct sockaddr *)&addrSer,addrlen);  
    if(res < 0)  
        perror("connect");  
    printf("client connect server ok.\n");  
    //发送数据  
    char sendbuf[256];  
    scanf("%s",sendbuf);  
    send(sockCli,sendbuf,strlen(sendbuf)+1,0);  
    handle_connection(sockCli);  
  
    return 0;  
}  