#include <stdio.h>
#include <stdlib.h>
typedef int elemtype;
typedef struct lnode    //定义结点类型
{
	elemtype data;
	struct lnode *next;
	struct lnode *prior;
}lnode,*linklist;

int initlist(linklist &L)   //初始化单链表
{
	L=(linklist)malloc(sizeof(lnode));   //表头附加结点
	if(!L) exit(-2);
	L->next=L;
	L->prior=L;
	return 1;                 
}
//初始化了一个空表
//尾插法是在上一次生成的节点后面插入一个新节点
//头插法是在上一次生成的节点后面和头结点之间插入一个新节点


void createlist(linklist &L)  //头插法生成双向循环链表
{
	//在创建节点过程中L始终指向头节点（头结点没有值),q始终指向新创建的那个节点
	int x;
	linklist q=L;
	printf("请输入要插入元素的值(输入0结束):\n");
	scanf("%d",&x);
	while(x){
		linklist p=(linklist)malloc(sizeof(lnode));
		/*p->data=x;
		q->next=p;
		L->prior=p;
		p->prior=q;
		p->next=L;
		q=p;*/
		
		
		p->data=x;
		p->next=q;
		p->prior=L;
		L->next=p;
		q->prior=p;
		q=p;//q始终指向新创建的那个节点
		if(L->prior==L)L->prior=p;//如果是第一次插入则把头结点的前驱指向第一次插入的值
		scanf("%d",&x);
	}          
}

void shuchulist(linklist &L)  //遍历有头结点的双向循环链表
{
	linklist p=L->next;
	while(p->next!=L){
		printf("%4d",p->data);
		p=p->next;
	}
	printf("%4d",p->data);
	printf("\n");
}
int lengthlist(linklist L){//通过链表的遍历来统计长度
	linklist p=L->next;
	int count=0;
	while(p!=L){
		p=p->next;
		count++;
	}
	return count;
}
int query_i(linklist &L,int index){//按索引查询(我没把头结点算第一个节点)
	linklist head=L;
	if (index <=0 || index > lengthlist(L))
    {
        printf("out of range\n");
        return 0;
    }
    int i;
    for (i = 1; i <=index; i++)
    {
        head = head->next;
    }
    printf("%d is %d\n", index, head->data);
    return 1;
}
int query_x(linklist &L,elemtype data){//按值查询
	linklist head=L;
    int index = 1;
	int flag=0;
    while (head->next != L)//头结点的前驱指向最先创建的节点,后驱指向第一个节点,这个第一个节点是最后创建的,节点的12345...索引是按头结点的next指针数下去的
    {
        if (data == head->next->data)
        {
			flag=1;
            printf("%d is on %d\n", data, index);
        }
        index++;
        head = head->next;
    }
	if(flag==0){
		printf("未找到值为%d的节点\n",data);
		return 0;
	}
    return 1;
}
int listdelete_i(linklist &L,int i){//删除带头结点的双向循环链表中第i个元素
	linklist p=L; 
	int j=0;
	if(i>lengthlist(L)){
		return 0;
	}
	while(j<i){//寻找第i个结点，并令p指向此结点
		p=p->next; ++j;
	}
	p->prior->next=p->next;//删除结点p
	free(p);//释放结点p
	return 1;
}
int listdelete_x(linklist &L,elemtype x){//删除值为x的元素
	linklist p=L->next,q;
	int i=0;
	while(p!=L){
		if(p->data==x){
			q=p->next;
			p->next->prior=p->prior;
			p->prior->next=p->next;
			free(p);
			p=q;
			++i;
		}
		else
			p=p->next;
	}
	return i;
}
int insert_index(linklist &L, int index, elemtype value)//在第i个节点上插入元素x
{
    if (index < 0 || index > lengthlist(L))
    {
        printf("out of range\n");
        return 0;
    }
	linklist head=L;
    linklist newnode=(linklist)malloc(sizeof(lnode));
    newnode->data = value;

    int i;
    for (i = 1; i < index; i++)
    {
        head = head->next;
    }
    newnode->next = head->next;
    head->next = newnode;

    newnode->prior = head;
    newnode->next->prior = newnode;
    return 1;    
}
int insert_head(linklist &L, elemtype value)//直接用头插法插入元素x
{
	linklist head=L;
    linklist newnode=(linklist)malloc(sizeof(lnode));
    newnode->data = value;

    newnode->next = head->next;
    head->next = newnode;

    newnode->prior = head;
    newnode->next->prior = newnode;
    return 1;
}
void main()
{
	linklist La;
	int menu,flag,i,x,c;
	do{ 
		printf("          制作人：杨志鹏\n");
	    printf("          学  号：201520460206\n");
	    printf("          专  业：信息管理与信息系统\n");
		printf("          指导老师：吴志强\n");
		printf("\n");	printf("\n");
		printf("1.利用头插法建立双向循环链表链表\n");
		printf("2.查询\n");
		printf("3.删除\n");
		printf("4.插入\n");
		printf("0.退出\n");
		printf("\n请输入所选菜单(0-6): ");
		scanf("%d",&menu);
		switch(menu){
		case 1: initlist(La);createlist(La);break;
		case 2: printf("请选择查询方式: 1查询值为x的节点   2 查询第i个节点  ");
			scanf("%d",&c);
			if(c==1){
				printf("请输入要查询的值: ");
				scanf("%d",&x);
				flag=query_x(La,x);
				if(flag){
					printf("查询成功!\n");
				}else
					printf("查询失败!\n");
				}
			else if(c==2){
				printf("请输入要查询的位置:");
				scanf("%d",&i);
				flag=query_i(La,i);
				if(flag){
					printf("查询成功!\n");
				}else
					printf("查询失败!\n");
			}
			break;
		case 3: printf("请选择删除方式：1 删除值为x的结点  2 删除第i个结点  ");
			scanf("%d",&c);
			if(c==1){
				printf("请输入要删除元素的值: ");
				scanf("%d",&x);
				flag=listdelete_x(La,x);
				if(flag){
					printf("删除成功!\n");
					printf("删除后的链表为:\n");
					shuchulist(La);
				}else
					printf("删除失败!\n");
			}else if(c==2){
				printf("请输入要删除的位置: ");
				scanf("%d",&i);
				flag=listdelete_i(La,i);
				if(flag){
					printf("删除成功!\n");
					printf("删除后的链表为:\n");
					shuchulist(La);
				}else
					printf("删除失败!\n");
			}
			break;
		case 4: printf("请选择插入方式:  1在第i个节点插入x值  2直接按头插法插入x值  ");
			scanf("%d",&c);
			if(c==1){
				printf("请输入节点之i和插入值x:  ");
				int index=0;
				elemtype value=0;
				scanf("%d%d",&index,&value);
				int flag=insert_index(La,index,value);
				if(flag){
					printf("插入成功!\n");
					printf("插入后的链表为:\n");
					shuchulist(La);
				}
				else
					printf("插入失败!\n");
			}else if(c==2){
				printf("请输入插入值x:   ");
				scanf("%d",&x);
				int flag=insert_head(La,x);
				if(flag){
					printf("插入成功!\n");
					printf("插入后的链表为:\n");
					shuchulist(La);
				}
			}
			break;		 
		case 0: exit(0);
		}
	}while(menu);
}
