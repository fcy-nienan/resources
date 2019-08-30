#include<iostream>
#include<string>
using namespace std;

template <class T>
struct BiNode   //二叉树的结点结构
{
	T data;
	BiNode<T> *lchild, *rchild;
};

template <class T>
class BiTree
{
public:
	BiTree();             //构造函数，初始化一棵二叉树，其前序序列由键盘输入
	~BiTree(void);         //析构函数，释放二叉链表中各结点的存储空间
	BiNode<T>* Getroot();  //获得指向根结点的指针
	void PreOrder(BiNode<T> *root);     //前序遍历二叉树
	void InOrder(BiNode<T> *root);      //中序遍历二叉树
	void PostOrder(BiNode<T> *root);    //后序遍历二叉树
	void LeverOrder(BiNode<T> *root);   //层序遍历二叉树
	int Count(BiNode<T>  *r);  //统计节点个数   
	int CountLeaf(BiNode<T> *r );//统计二叉树中叶子结点的个数
	int Depth(BiNode<T> *r);//求二叉树的深度
private:
	BiNode<T> *root;         //指向根结点的头指针
	BiNode<T> *Creat();     //有参构造函数调用
	void Release(BiNode<T> *root);   //析构函数调用 
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
	if (root == NULL)  return;      //递归调用的结束条件	          
	else{
		InOrder(root->lchild);    //中序递归遍历root的左子树
		cout << root->data << " ";    //访问根结点的数据域
		InOrder(root->rchild);    //中序递归遍历root的右子树
	}
}
template <class T>
void BiTree<T>::PostOrder(BiNode<T> *root)
{
	if (root == NULL)   return;       //递归调用的结束条件
	else{
		PostOrder(root->lchild);    //后序递归遍历root的左子树
		PostOrder(root->rchild);    //后序递归遍历root的右子树
		cout << root->data << " ";      //访问根结点的数据域
	}
}

template <class T>
void BiTree<T>::LeverOrder(BiNode<T> *root)
{
	const int MaxSize = 100;

	int front = 0;
	int rear = 0;  //采用顺序队列，并假定不会发生上溢

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
	cout << "请输入创建一棵二叉树的结点数据" << endl;
	cin >> ch;
	if (ch == "#") root = NULL;
	else{
		root = new BiNode<T>;       //生成一个结点
		root->data = ch;
		root->lchild = Creat();    //递归建立左子树
		root->rchild = Creat();    //递归建立右子树
	}
	return root;
}

template<class T>
void BiTree<T>::Release(BiNode<T>* root)
{
	if (root != NULL){
		Release(root->lchild);   //释放左子树
		Release(root->rchild);   //释放右子树
		delete root;
	}
}
template <class T>
int BiTree<T>::Count(BiNode<T> *r)  //统计节点个数 
{
	//......
	if(r==NULL)return 0;
	else if(r->lchild==NULL&&r->rchild==NULL)return 1;
	else
		return BiTree<T>::Count(r->rchild)+BiTree<T>::Count(r->lchild)+1;


}

template <class T>
int BiTree<T>::CountLeaf(BiNode<T> *r )  //统计二叉树中叶子结点的个数
{
	
    if(r==NULL)return  0;
	else if(r->lchild==NULL&&r->rchild==NULL)return  1;
	else
		return  CountLeaf(r->rchild)+CountLeaf(r->lchild);

	//......
}

template <class T>
int BiTree<T>::Depth(BiNode<T> *r) //求二叉树的深度
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
	BiTree<string> bt; //创建一棵树
	BiNode<string>* root = bt.Getroot( );  //获取指向根结点的指针 

	cout<<"------前序遍历------ "<<endl;
	bt.PreOrder(root);
	cout<<endl;
	cout<<"------中序遍历------ "<<endl;
	bt.InOrder(root);
	cout<<endl;
	cout<<"------后序遍历------ "<<endl;
	bt.PostOrder(root);
	cout<<endl;
	cout<<"------层序遍历------ "<<endl;
	bt.LeverOrder(root);
	cout<<endl;
	cout<<"该树的深度为:"<<bt.Depth(root)<<endl;
	cout<<"该树的叶子节点数为:"<<bt.CountLeaf(root)<<endl;
	cout<<"该树的总结点数为:"<<bt.Count(root)<<endl;

	cout<<endl;
	 
}