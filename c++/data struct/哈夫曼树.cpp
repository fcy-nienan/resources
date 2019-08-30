#include<iostream>
#include<stdio.h>
using namespace std;
#define n 5//Ҷ�ӽڵ���
#define m 2*n-1//�ܽ����
typedef struct node
{
	char ch;//�ַ�
	char bit[30];//��������
	node* left;//����
	node* right;//�Һ���
	node* parent;//���ڵ�
	int value;//��־�Ƿ��и��ڵ㣬��Ϊ0����Ϊ-1
	double weight;//Ȩֵ
}node,*lpnode;
typedef struct hfm
{

	node data[m];
	int front;//ָ���һ���ڵ�
	int rear;//ָ�����һ���ڵ�ĺ�һλ
}hfm;
void init(hfm& myhfm)//��ʼ��
{
	myhfm.front=myhfm.rear=0;
	for(int i=0;i<n;i++)
	{
		myhfm.data[i].left=NULL;
		myhfm.data[i].right =NULL;
		myhfm.data[i].parent=NULL;
		myhfm.data[i].value =-1;//value��Ϊ-1����ʾ�����Բ���Ƚ�
		cout<<"�����ַ�:";
		cin>>myhfm.data[i].ch;
		cout<<"����Ȩֵ:";
		cin>>myhfm.data[i].weight ;
		myhfm.rear++;
	}
}
void select(hfm& myhfm)//ѡ����Сֵ
{
	double min1,min2;//min1,min2�洢������Сֵ
	int temp1,temp2;//temp1,temp2�洢������Сֵ���±�
	min1=min2=1000;
	for(int i=myhfm.front;i<myhfm.rear ;i++)//ѡ���һ����Сֵ
	{
		if(myhfm.data[i].value==0)continue;
		if(min1>myhfm.data[i].weight )
		{
			min1=myhfm.data[i].weight ;
			temp1=i;
		}
		else
		{
			min1=min1;
			temp1=temp1;
		}
	}
	myhfm.data[temp1].value=0;//�´β�����Ƚ�

	for(i=myhfm.front;i<myhfm.rear ;i++)//ѡ��ڶ�����Сֵ
	{
		if(myhfm.data[i].value==0)continue;
		if(min2>myhfm.data[i].weight )
		{
			min2=myhfm.data[i].weight ;
			temp2=i;
		}
		else
		{
			min2=min2;
			temp2=temp2;
		}
	}
	myhfm.data[temp2].value=0;//�´β�����Ƚ�

	//���츸�ڵ㲢�ֱ�ָ����Ӧ�ڵ�
	myhfm.data[myhfm.rear].weight =min1+min2;//���ڵ��Ȩֵ��������Сֵ֮��
	//���ڵ�ָ���ӽڵ�
	myhfm.data[myhfm.rear].left=&myhfm.data[temp1];
	myhfm.data[myhfm.rear].right=&myhfm.data[temp2];
	//�ӽڵ�ָ�򸸽ڵ�
	myhfm.data[temp1].parent=&myhfm.data[myhfm.rear];
	myhfm.data[temp2].parent=&myhfm.data[myhfm.rear];

	myhfm.data[myhfm.rear].value =-1;//���ڵ��value��ֵ����ʾ�´οɲ���Ƚ�
	myhfm.rear++;
}
void code(hfm& myhfm)//����
{
	lpnode p,q;
	for(int i=0;i<n;i++)
	{
		p=&myhfm.data[i];//pָ���ӽڵ㣬qָ�򸸽ڵ㣬���q�����ӵ���p,�����Ϊ0������Ϊ1
		int j=0;
		do
		{
			q=p->parent ;
			if(q->left==p)
			{
				myhfm.data[i].bit[j++]='0';
			}
			else
			{
				myhfm.data[i].bit[j++]='1';
			}
			p=q;
		}while(q->value==0);
		myhfm.data[i].bit[j]='\0';
		
		//����ѱ���õĵ�һ���ڵ�
		cout<<"�ַ�"<<myhfm.data[i].ch<<"��ȨֵΪ:"<<myhfm.data[i].weight<<"����Ϊ:";

		for(j=j-1;j>=0;j--)
		{
			cout<<myhfm.data[i].bit[j];
		}
		cout<<endl;
	}
}

node* getroot(hfm& myhfm)//��ȡ�����������ڵ�
{
	int index=0;
	for(int i=0;i<m;i++)
	{
		if(myhfm.data[i].value==-1)
		{	
			index=i;
		    break;
		}
	}
	node* root;
	root=&myhfm.data[index];
	return root;
}
void preorder(node* root)//�������
{

	if(root!=NULL)
	{
		printf("%6.2f",root->weight);
		preorder(root->left);
		preorder(root->right);
	}
	
}
void midorder(node* root)//�������
{

	if(root!=NULL)
	{
		midorder(root->left);
		printf("%6.2f",root->weight);
		midorder(root->right);
	}
	
}
void backorder(node* root)//�������
{
	if(root!=NULL)
	{
		backorder(root->left);
		backorder(root->right);
		printf("%6.2f",root->weight);
	}
	
}
void threeorder(node* root)
{
	cout<<"�������:"<<endl;
	preorder(root);
	cout<<endl;
	cout<<"�������:"<<endl;
	midorder(root);
	cout<<endl;
	cout<<"�������:"<<endl;
	backorder(root);
	cout<<endl;
}
void show()
{
	cout<<"                                 ����������                  "<<endl;
	cout<<"             1.����Ȩֵ���ַ�                  2.������������"<<endl;
	cout<<"             3.�������������                  4.�˳�        "<<endl;
}
void mainprint()
{
	hfm myhfm;
	char t;	
	while(1)
	{	
		show();
		fflush(stdin);
		cout<<"��������ѡ��:";		
		cin>>t;
		system("cls");
		switch(t)
		{
		case '1':
			{
				cout<<"                      1.����Ȩֵ���ַ�                "<<endl;

				init(myhfm);//��ʼ��
				for(int i=0;i<n-1;i++)//�����������
				{
					select(myhfm);
				}	

				break;
			}
		case '2':
			{
				cout<<"                       2.������������                 "<<endl;

				lpnode root;
				root=getroot(myhfm);//��ȡ���������ĸ��ڵ�
				threeorder(root);//���ֱ���

				break;
			}
		case '3':
			{
				cout<<"                        3.�������                     "<<endl;

				code(myhfm);//�Թ�����������

				break;
			}
		case '4':
			{
				return;
			}
		}
	}
}
int main()
{
	mainprint();	
	system("pause");
	return 0;
}