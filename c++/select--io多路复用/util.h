#pragma once  
#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<poll.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<sys/socket.h>  
#include<string.h>  
  
#define IPADDR "127.0.0.1"  
#define PORT 8787  
#define MAXLINE 1024  
#define LISTENQ 5  
  
#define SIZE 10  
#define OPEN_SIZE 5 