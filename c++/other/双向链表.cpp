#include <stdio.h>
#include <stdlib.h>
typedef int elemtype;
typedef struct lnode    //����������
{
	elemtype data;
	struct lnode *next;
	struct lnode *prior;
}lnode,*linklist;

int initlist(linklist &L)   //��ʼ��������
{
	L=(linklist)malloc(sizeof(lnode));   //��ͷ���ӽ��
	if(!L) exit(-2);
	L->next=L;
	L->prior=L;
	return 1;                 
}
//��ʼ����һ���ձ�
//β�巨������һ�����ɵĽڵ�������һ���½ڵ�
//ͷ�巨������һ�����ɵĽڵ�����ͷ���֮�����һ���½ڵ�


void createlist(linklist &L)  //ͷ�巨����˫��ѭ������
{
	//�ڴ����ڵ������Lʼ��ָ��ͷ�ڵ㣨ͷ���û��ֵ),qʼ��ָ���´������Ǹ��ڵ�
	int x;
	linklist q=L;
	printf("������Ҫ����Ԫ�ص�ֵ(����0����):\n");
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
		q=p;//qʼ��ָ���´������Ǹ��ڵ�
		if(L->prior==L)L->prior=p;//����ǵ�һ�β������ͷ����ǰ��ָ���һ�β����ֵ
		scanf("%d",&x);
	}          
}

void shuchulist(linklist &L)  //������ͷ����˫��ѭ������
{
	linklist p=L->next;
	while(p->next!=L){
		printf("%4d",p->data);
		p=p->next;
	}
	printf("%4d",p->data);
	printf("\n");
}
int lengthlist(linklist L){//ͨ������ı�����ͳ�Ƴ���
	linklist p=L->next;
	int count=0;
	while(p!=L){
		p=p->next;
		count++;
	}
	return count;
}
int query_i(linklist &L,int index){//��������ѯ(��û��ͷ������һ���ڵ�)
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
int query_x(linklist &L,elemtype data){//��ֵ��ѯ
	linklist head=L;
    int index = 1;
	int flag=0;
    while (head->next != L)//ͷ����ǰ��ָ�����ȴ����Ľڵ�,����ָ���һ���ڵ�,�����һ���ڵ�����󴴽���,�ڵ��12345...�����ǰ�ͷ����nextָ������ȥ��
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
		printf("δ�ҵ�ֵΪ%d�Ľڵ�\n",data);
		return 0;
	}
    return 1;
}
int listdelete_i(linklist &L,int i){//ɾ����ͷ����˫��ѭ�������е�i��Ԫ��
	linklist p=L; 
	int j=0;
	if(i>lengthlist(L)){
		return 0;
	}
	while(j<i){//Ѱ�ҵ�i����㣬����pָ��˽��
		p=p->next; ++j;
	}
	p->prior->next=p->next;//ɾ�����p
	free(p);//�ͷŽ��p
	return 1;
}
int listdelete_x(linklist &L,elemtype x){//ɾ��ֵΪx��Ԫ��
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
int insert_index(linklist &L, int index, elemtype value)//�ڵ�i���ڵ��ϲ���Ԫ��x
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
int insert_head(linklist &L, elemtype value)//ֱ����ͷ�巨����Ԫ��x
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
		printf("          �����ˣ���־��\n");
	    printf("          ѧ  �ţ�201520460206\n");
	    printf("          ר  ҵ����Ϣ��������Ϣϵͳ\n");
		printf("          ָ����ʦ����־ǿ\n");
		printf("\n");	printf("\n");
		printf("1.����ͷ�巨����˫��ѭ����������\n");
		printf("2.��ѯ\n");
		printf("3.ɾ��\n");
		printf("4.����\n");
		printf("0.�˳�\n");
		printf("\n��������ѡ�˵�(0-6): ");
		scanf("%d",&menu);
		switch(menu){
		case 1: initlist(La);createlist(La);break;
		case 2: printf("��ѡ���ѯ��ʽ: 1��ѯֵΪx�Ľڵ�   2 ��ѯ��i���ڵ�  ");
			scanf("%d",&c);
			if(c==1){
				printf("������Ҫ��ѯ��ֵ: ");
				scanf("%d",&x);
				flag=query_x(La,x);
				if(flag){
					printf("��ѯ�ɹ�!\n");
				}else
					printf("��ѯʧ��!\n");
				}
			else if(c==2){
				printf("������Ҫ��ѯ��λ��:");
				scanf("%d",&i);
				flag=query_i(La,i);
				if(flag){
					printf("��ѯ�ɹ�!\n");
				}else
					printf("��ѯʧ��!\n");
			}
			break;
		case 3: printf("��ѡ��ɾ����ʽ��1 ɾ��ֵΪx�Ľ��  2 ɾ����i�����  ");
			scanf("%d",&c);
			if(c==1){
				printf("������Ҫɾ��Ԫ�ص�ֵ: ");
				scanf("%d",&x);
				flag=listdelete_x(La,x);
				if(flag){
					printf("ɾ���ɹ�!\n");
					printf("ɾ���������Ϊ:\n");
					shuchulist(La);
				}else
					printf("ɾ��ʧ��!\n");
			}else if(c==2){
				printf("������Ҫɾ����λ��: ");
				scanf("%d",&i);
				flag=listdelete_i(La,i);
				if(flag){
					printf("ɾ���ɹ�!\n");
					printf("ɾ���������Ϊ:\n");
					shuchulist(La);
				}else
					printf("ɾ��ʧ��!\n");
			}
			break;
		case 4: printf("��ѡ����뷽ʽ:  1�ڵ�i���ڵ����xֵ  2ֱ�Ӱ�ͷ�巨����xֵ  ");
			scanf("%d",&c);
			if(c==1){
				printf("������ڵ�֮i�Ͳ���ֵx:  ");
				int index=0;
				elemtype value=0;
				scanf("%d%d",&index,&value);
				int flag=insert_index(La,index,value);
				if(flag){
					printf("����ɹ�!\n");
					printf("����������Ϊ:\n");
					shuchulist(La);
				}
				else
					printf("����ʧ��!\n");
			}else if(c==2){
				printf("���������ֵx:   ");
				scanf("%d",&x);
				int flag=insert_head(La,x);
				if(flag){
					printf("����ɹ�!\n");
					printf("����������Ϊ:\n");
					shuchulist(La);
				}
			}
			break;		 
		case 0: exit(0);
		}
	}while(menu);
}
