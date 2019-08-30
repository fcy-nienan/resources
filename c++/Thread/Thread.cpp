#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


void * print_a(void *);
void * print_b(void *);
void * check(void *);
void * add(void *);
int i=10; 
int main(){

    pthread_t t0;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    int i=&&1;
    // 创建线程A
    if(pthread_create(&t3,NULL,add,NULL)==-1){
        puts("failed to create pthread t3");
        exit(1);
    }
    if(pthread_create(&t0,NULL,add,NULL)==-1){
        puts("failed to create pthread t0");
        exit(1);
    }

    // 等待线程结束
    void * result;                                     
    if(pthread_join(t0, &result) == -1){
        puts("fail to recollect t0");
        exit(1);
    }
    if(pthread_join(t3,&result)==-1){
        puts("fail to recollect t2");
        exit(1);
    } 
    printf("%d",i);
    getchar(); 


    return 0;
}

void * add(void *a){
     for(int j=0;j<1000000;j++){
         i++;
     }
}
// 线程A 方法
void * print_a(void *a){
    while(1){
        i=10;
    }
}

// 线程B 方法
void * print_b(void *b){
    while(1){
        i=20;
    }
}
void * check(void *b){
     while(1){
         if(i!=20&&i!=10){
             printf("Error:%d",i);
         
         }
     }
}
void * testadm(void *b){
     int n=0;
     for(int m=0;m<100;m++){
              
     }
