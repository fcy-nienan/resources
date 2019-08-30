
//统计一句英文中有多少个相同的单词并逐个输出
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
    cout<<"请输入一句英文(单词之间以空格隔开):";
    gets(p);
    char c=p[0];
    int i=0,j=0,mm=0;

    char cc=p[0];
    int kk=0,l=0;
    //计算总共有多少个单词
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
    kk++;//此命令后kk为句子中单词的个数

    //将单词按个存到save数组中
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


    int counter[50]={0};//统计每个单词的次数
    for(int aaa=0;aaa<kk;aaa++)
    {
        for(int bbb=(kk-1);bbb>aaa;bbb--)
        {
            if((strcmp(save[aaa],save[bbb]))==0)
            {
                strcpy(save[bbb],"");//如果匹配到相同的则把后一个单词删除掉
                counter[aaa]++;
            }
        }
    }


    for(int iii=0;iii<kk;iii++)
    {
        if(save[iii][0]=='\0')continue;

        cout<<"单词"<<save[iii]<<"有";
        cout<<counter[iii]+1<<"个"<<endl;
    }
	getchar();
}
