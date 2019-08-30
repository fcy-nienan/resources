#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define OK 1
#define ERROR 0
#define MAXSIZE 100  //最多非0元素的个数 
#define MAXR 50      //rpos所能处理的最大行数 
#define MAXC 50   //系数矩阵相乘时，保留临时列结果的数组temp[MAXC]
typedef struct NODE{ //定义稀疏矩阵结点
        int i;
        int j;
        int data;
} Node;

typedef struct MATRIX{ //定义稀疏矩阵（可以快速访问）
        int mu, nu, tu;
        Node matrix[MAXSIZE+1];
        int rpos[MAXR+1];
} Matrix;

int CreatSMatrix( Matrix* M ); //创建一个矩阵（由用户输入原始矩阵，转化为稀疏矩阵方式储存）
int AddSMatrix( Matrix M, Matrix N, Matrix *Q);  //两个稀疏矩阵相加
int Print( Matrix M );        //打印一个稀疏矩阵
main()
{
      Matrix A1, A2, A3;  //定义矩阵
      CreatSMatrix( &A1 );
      CreatSMatrix( &A2 );
     if( A1.mu==A2.mu && A1.nu==A2.nu ){ //判断能否相加
          AddSMatrix( A1, A2, &A3 );
    printf("两矩阵相加得：\n");
          Print(A3);
      }
      else
        printf("规模不一致，不能相加！\n");
system("pause");
      return 0;
}
//构建稀疏矩阵 
int CreatSMatrix( Matrix* M )
{
      int temp, i,j;
      printf("输入矩阵的行列数：");
      scanf("%d%d", &M->mu, &M->nu);
   M->tu=0;
      printf("按行序输入矩阵：\n");
      for( i=1; i<=M->mu; i++){
   M->rpos[i]=M->tu+1;  //每计算完一行，给rpos[]赋值
         for( j=1; j<=M->nu; j++){
            scanf("%d",&temp );  
            if( temp ){      //非0值保存 
               M->matrix[M->tu+1].i= i;
               M->matrix[M->tu+1].j= j;
               M->matrix[M->tu+1].data=temp;
               M->tu++;
             }
         }
       }
     
   return OK;
}
//两矩阵相加
int AddSMatrix( Matrix M, Matrix N, Matrix *Q) 
{
         int arow, Mcol, Ncol, i=1;
         int Mlim,Nlim;
  
   Q->tu=0; //给Q赋初值
   Q->mu=M.mu;
   Q->nu=M.nu;
         for( arow=1; arow<=M.mu; arow++ )//逐行遍历
         {
    Q->rpos[arow] = Q->tu+1;             
    //确定第i行的j在M、N矩阵中的范围 
                  Mlim =  arow<M.mu ? M.rpos[arow+1] : M.tu+1;
                  Nlim =  arow<N.mu ? N.rpos[arow+1] : N.tu+1;
              for( Mcol=M.rpos[arow], Ncol=N.rpos[arow]; Mcol<Mlim && Ncol<Nlim; i++ ){
                    if( M.matrix[Mcol].j == N.matrix[Ncol].j ){  //j相等
      if(M.matrix[Mcol].data+N.matrix[Ncol].data) {//相加之后不为0，存入Q
       Q->matrix[i].data = M.matrix[Mcol].data+N.matrix[Ncol].data;
       Q->matrix[i].i = M.matrix[Mcol].i;
       Q->matrix[i].j = M.matrix[Mcol].j;
       Q->tu++;
      }
      else i--;  //相加为0，i自减（保持i不变）
      Mcol++;
      Ncol++;
     }
                    else{ //谁的j小，把谁存入Q
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
//打印稀疏矩阵
int Print( Matrix M)
{
	int i,j,k=1;
	if(M.tu==0){
		printf("空矩阵\n\n");
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
      
