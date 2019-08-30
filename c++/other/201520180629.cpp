#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXSIZE 100  //����0Ԫ�صĸ��� 
#define MAXR 50      //rpos���ܴ����������� 
#define MAXC 50   //ϵ���������ʱ��������ʱ�н��������temp[MAXC]
typedef struct NODE{ //����ϡ�������
        int i;
        int j;
        int data;
} Node;

typedef struct MATRIX{ //����ϡ����󣨿��Կ��ٷ��ʣ�
        int mu, nu, tu;
        Node matrix[MAXSIZE+1];
        int rpos[MAXR+1];
} Matrix;

int CreatSMatrix( Matrix* M ); //����һ���������û�����ԭʼ����ת��Ϊϡ�����ʽ���棩
int AddSMatrix( Matrix M, Matrix N, Matrix *Q);  //����ϡ��������
int Print( Matrix M );        //��ӡһ��ϡ�����
main()
{
      Matrix A1, A2, A3;  //�������
      CreatSMatrix( &A1 );
      CreatSMatrix( &A2 );
     if( A1.mu==A2.mu && A1.nu==A2.nu ){ //�ж��ܷ����
          AddSMatrix( A1, A2, &A3 );
    printf("��������ӵã�\n");
          Print(A3);
      }
      else
        printf("��ģ��һ�£�������ӣ�\n");
system("pause");
      return 0;
}
//����ϡ����� 
int CreatSMatrix( Matrix* M )
{
      int temp, i,j;
      printf("����������������");
      scanf("%d%d", &M->mu, &M->nu);
   M->tu=0;
      printf("�������������\n");
      for( i=1; i<=M->mu; i++){
   M->rpos[i]=M->tu+1;  //ÿ������һ�У���rpos[]��ֵ
         for( j=1; j<=M->nu; j++){
            scanf("%d",&temp );  
            if( temp ){      //��0ֵ���� 
               M->matrix[M->tu+1].i= i;
               M->matrix[M->tu+1].j= j;
               M->matrix[M->tu+1].data=temp;
               M->tu++;
             }
         }
       }
     
   return OK;
}
//���������
int AddSMatrix( Matrix M, Matrix N, Matrix *Q) 
{
         int arow, Mcol, Ncol, i=1;
         int Mlim,Nlim;
  
   Q->tu=0; //��Q����ֵ
   Q->mu=M.mu;
   Q->nu=M.nu;
         for( arow=1; arow<=M.mu; arow++ )//���б���
         {
    Q->rpos[arow] = Q->tu+1;             
    //ȷ����i�е�j��M��N�����еķ�Χ 
                  Mlim =  arow<M.mu ? M.rpos[arow+1] : M.tu+1;
                  Nlim =  arow<N.mu ? N.rpos[arow+1] : N.tu+1;
              for( Mcol=M.rpos[arow], Ncol=N.rpos[arow]; Mcol<Mlim && Ncol<Nlim; i++ ){
                    if( M.matrix[Mcol].j == N.matrix[Ncol].j ){  //j���
      if(M.matrix[Mcol].data+N.matrix[Ncol].data) {//���֮��Ϊ0������Q
       Q->matrix[i].data = M.matrix[Mcol].data+N.matrix[Ncol].data;
       Q->matrix[i].i = M.matrix[Mcol].i;
       Q->matrix[i].j = M.matrix[Mcol].j;
       Q->tu++;
      }
      else i--;  //���Ϊ0��i�Լ�������i���䣩
      Mcol++;
      Ncol++;
     }
                    else{ //˭��jС����˭����Q
      if(M.matrix[Mcol].j < N.matrix[Ncol].j){
                                Q->matrix[i].i = M.matrix[Mcol].i;
                                Q->matrix[i].j = M.matrix[Mcol].j;
                                Q->matrix[i].data = M.matrix[Mcol].data;
                                Q->tu++;
        Mcol++;
                         }
      else{
                                Q->matrix[i].i = N.matrix[Ncol].i;
                                Q->matrix[i].j = N.matrix[Ncol].j;
                                Q->matrix[i].data = N.matrix[Ncol].data;
          Q->tu++;
                                Ncol++;
                         }
                     }//else
                    
              }//for 
     if( Mcol<Mlim ){
      for( ; Mcol<Mlim; i++ ){
       Q->matrix[i].i = M.matrix[Mcol].i;
                                Q->matrix[i].j = M.matrix[Mcol].j;
                                Q->matrix[i].data = M.matrix[Mcol].data;
                                Q->tu++;
        Mcol++;
      }
     }
     if( Ncol<Nlim ){
      for( ; Ncol<Nlim; i++ ){
       Q->matrix[i].i = N.matrix[Ncol].i;
                      Q->matrix[i].j = N.matrix[Ncol].j;
                      Q->matrix[i].data = N.matrix[Ncol].data;
                      Q->tu++;
                      Ncol++;
      }
     }

         }
         return 1; 
}
//��ӡϡ�����
int Print( Matrix M)
{
	int i,j,k=1;
	if(M.tu==0){
		printf("�վ���\n\n");
		return ERROR;
	}
	for(i=1;i<=M.mu;i++)
	{
		for(j=1;j<=M.nu;j++)
		{
			cout<<M.matrix[k].data<<'\t'; 
			k++;
		}
		printf("\n");
		
	}
}
      
