#include<iostream>
#include<string>
using namespace std;

template <class T>
struct BiNode   //�������Ľ��ṹ
{
	T data;
	BiNode<T> *lchild, *rchild;
};

template <class T>
class BiTree
{
public:
	BiTree();             //���캯������ʼ��һ�ö���������ǰ�������ɼ�������
	~BiTree(void);         //�����������ͷŶ��������и����Ĵ洢�ռ�
	BiNode<T>* Getroot();  //���ָ�������ָ��
	void PreOrder(BiNode<T> *root);     //ǰ�����������
	void InOrder(BiNode<T> *root);      //�������������
	void PostOrder(BiNode<T> *root);    //�������������
	void LeverOrder(BiNode<T> *root);   //�������������
	int Count(BiNode<T>  *r);  //ͳ�ƽڵ����   
	int CountLeaf(BiNode<T> *r );//ͳ�ƶ�������Ҷ�ӽ��ĸ���
	int Depth(BiNode<T> *r);//������������
private:
	BiNode<T> *root;         //ָ�������ͷָ��
	BiNode<T> *Creat();     //�вι��캯������
	void Release(BiNode<T> *root);   //������������ 
};

template<class T>
BiTree<T>::BiTree()
{
	this->root = Creat();
}

template<class T>
BiTree<T>::~BiTree(void)
{
	Release(root);
}

template<class T>
BiNode<T>* BiTree<T>::Getroot()
{
	return root;
}

template<class T>
void BiTree<T>::PreOrder(BiNode<T> *root)
{
	if (root == NULL)  return;
	else{
		cout << root->data << " ";
		PreOrder(root->lchild);
		PreOrder(root->rchild);
	}
}

template <class T>
void BiTree<T>::InOrder(BiNode<T> *root)
{
	if (root == NULL)  return;      //�ݹ���õĽ�������	          
	else{
		InOrder(root->lchild);    //����ݹ����root��������
		cout << root->data << " ";    //���ʸ�����������
		InOrder(root->rchild);    //����ݹ����root��������
	}
}
template <class T>
void BiTree<T>::PostOrder(BiNode<T> *root)
{
	if (root == NULL)   return;       //�ݹ���õĽ�������
	else{
		PostOrder(root->lchild);    //����ݹ����root��������
		PostOrder(root->rchild);    //����ݹ����root��������
		cout << root->data << " ";      //���ʸ�����������
	}
}

template <class T>
void BiTree<T>::LeverOrder(BiNode<T> *root)
{
	const int MaxSize = 100;

	int front = 0;
	int rear = 0;  //����˳����У����ٶ����ᷢ������

	BiNode<T>* Q[MaxSize];
	BiNode<T>* q;

	if (root == NULL) return;
	else{
		Q[rear++] = root;
		while (front != rear)
		{
			q = Q[front++];
			cout << q->data << " ";
			if (q->lchild != NULL)    Q[rear++] = q->lchild;
			if (q->rchild != NULL)    Q[rear++] = q->rchild;
		}
	}
}

template <class T>
BiNode<T>* BiTree<T>::Creat()
{
	BiNode<T>* root;
	T ch;
	cout << "�����봴��һ�ö������Ľ������" << endl;
	cin >> ch;
	if (ch == "#") root = NULL;
	else{
		root = new BiNode<T>;       //����һ�����
		root->data = ch;
		root->lchild = Creat();    //�ݹ齨��������
		root->rchild = Creat();    //�ݹ齨��������
	}
	return root;
}

template<class T>
void BiTree<T>::Release(BiNode<T>* root)
{
	if (root != NULL){
		Release(root->lchild);   //�ͷ�������
		Release(root->rchild);   //�ͷ�������
		delete root;
	}
}
template <class T>
int BiTree<T>::Count(BiNode<T> *r)  //ͳ�ƽڵ���� 
{
	//......
	if(r==NULL)return 0;
	else if(r->lchild==NULL&&r->rchild==NULL)return 1;
	else
		return BiTree<T>::Count(r->rchild)+BiTree<T>::Count(r->lchild)+1;


}

template <class T>
int BiTree<T>::CountLeaf(BiNode<T> *r )  //ͳ�ƶ�������Ҷ�ӽ��ĸ���
{
	
    if(r==NULL)return  0;
	else if(r->lchild==NULL&&r->rchild==NULL)return  1;
	else
		return  CountLeaf(r->rchild)+CountLeaf(r->lchild);

	//......
}

template <class T>
int BiTree<T>::Depth(BiNode<T> *r) //������������
{
	if(r==NULL)return 0;
	else
	{
		int u=BiTree<T>::Depth(r->lchild);
		int v=BiTree<T>::Depth(r->rchild);
 
	return u>v?(u+1):(v+1);
	}
	//......
}

void main()
{	
	BiTree<string> bt; //����һ����
	BiNode<string>* root = bt.Getroot( );  //��ȡָ�������ָ�� 

	cout<<"------ǰ�����------ "<<endl;
	bt.PreOrder(root);
	cout<<endl;
	cout<<"------�������------ "<<endl;
	bt.InOrder(root);
	cout<<endl;
	cout<<"------�������------ "<<endl;
	bt.PostOrder(root);
	cout<<endl;
	cout<<"------�������------ "<<endl;
	bt.LeverOrder(root);
	cout<<endl;
	cout<<"���������Ϊ:"<<bt.Depth(root)<<endl;
	cout<<"������Ҷ�ӽڵ���Ϊ:"<<bt.CountLeaf(root)<<endl;
	cout<<"�������ܽ����Ϊ:"<<bt.Count(root)<<endl;

	cout<<endl;
	 
}