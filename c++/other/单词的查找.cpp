
#include<iostream>
#include<string.h>
using namespace std;
int main()
{

    char pattern[]="abace";
    char target[]="abacdeabace";
    int next[10]={0};
    void makenext(char str[],int mynext[]);
    makenext(pattern,next);
    cout<<"ģʽ�ַ���next����:";
    for(int i=0;i<strlen(pattern);i++)
        cout<<next[i]<<"  ";
    cout<<endl;
    cout<<"Ŀ���ַ�:"<<target<<endl;
    cout<<"ģʽ�ַ�:"<<pattern<<endl;
	int j;
    for( i=0,j=0;i<strlen(target);i++)
    {
        while(j>0&&target[i]!=pattern[j])
        {
            j=next[j-1];
        }
        if(target[i]==pattern[j])
        {
            j++;
        }
        if(j==strlen(pattern))
        {
            cout<<"�ַ�����ʼ��Ŀ���ַ��ĵ�"<<i-j+2<<"���ַ�!"<<endl;
        }

    }
}
void makenext(char str[],int mynext[])
{
    int len=strlen(str);
    mynext[0]=0;
    for(int m=1,k=0;m<len;m++)
    {

        while(k>0&&str[m]!=str[k])
            k=mynext[k-1];
        if(str[m]==str[k])
        {
            k++;
        }
        mynext[m]=k;
    }
}
