
//ͳ��һ��Ӣ�����ж��ٸ���ͬ�ĵ��ʲ�������
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;
int main()
{
    char *p;
    char save[50][50]={0};
    p=(char*)malloc(100);
    cout<<"������һ��Ӣ��(����֮���Կո����):";
    gets(p);
    char c=p[0];
    int i=0,j=0,mm=0;

    char cc=p[0];
    int kk=0,l=0;
    //�����ܹ��ж��ٸ�����
    while(1)
    {

        if(cc==32)
        {
            kk++;
        }
        l++;
        cc=p[l];
        if(cc==0)break;
    }
    kk++;//�������kkΪ�����е��ʵĸ���

    //�����ʰ����浽save������
    while(1)
    {
        do
        {
            save[i][mm]=p[j];
            j++;
            mm++;
            c=p[j];
            if(i==(kk+1))break;
            if(c==0)break;
        }while(c!=32);
        i++;
        mm=0;
        j++;
        if(i==(kk+1))break;
    }


    int counter[50]={0};//ͳ��ÿ�����ʵĴ���
    for(int aaa=0;aaa<kk;aaa++)
    {
        for(int bbb=(kk-1);bbb>aaa;bbb--)
        {
            if((strcmp(save[aaa],save[bbb]))==0)
            {
                strcpy(save[bbb],"");//���ƥ�䵽��ͬ����Ѻ�һ������ɾ����
                counter[aaa]++;
            }
        }
    }


    for(int iii=0;iii<kk;iii++)
    {
        if(save[iii][0]=='\0')continue;

        cout<<"����"<<save[iii]<<"��";
        cout<<counter[iii]+1<<"��"<<endl;
    }
	getchar();
}
