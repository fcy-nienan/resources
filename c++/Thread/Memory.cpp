#include<stdio.h>
#include<stdlib.h>

int main(){
    int *p;
    int a[5]={1,2,3,4,5};
    int *ptr=(int*)(&a+1);
    printf("%d \r\n",*(ptr-1));
    p=(int*)malloc(10);
    *(p+1)=10;
    *(p+2)=11;
    *(p+3)=12;
    for(int i=0;i<10;i++){
            printf("%d\t",*(p+1));
    }
    getchar();
    return 0;
}
