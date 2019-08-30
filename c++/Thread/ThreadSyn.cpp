#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
int data=0;
pthread_mutex_t mutex;
void * thread1(void *){
     for(int i=0;i<100;i++){
         printf("%d\r\n",data);
         //pthread_mutex_lock(&mutex);
         data++;
         //pthread_mutex_unlock(&mutex);
     }
}
void * thread2(void *){
     for(int i=0;i<100;i++){
         printf("%d\r\n",data);
         data++;
     }
}
int main(){
    pthread_mutex_init(&mutex,NULL);
    pthread_t t1,t2;
    int ret=0;
    ret=pthread_create(&t1,NULL,thread1,NULL);
    if(ret!=0){
        printf("thread1 create failed!");
        exit(0);
    }
    ret=pthread_create(&t2,NULL,thread2,NULL);
    if(ret!=0){
        printf("thread2 create failed!");
        exit(0);
    }
    sleep(1000);
    return 0;
}
