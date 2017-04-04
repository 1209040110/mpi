
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void initMatrixWithRV(float *A, int rows, int cols,unsigned seed)
{
    srand(seed);
    for(int i = 0; i < rows*cols; i++){
        A[i] = (float)rand() / RAND_MAX;
    }
}
void matMultiplyWithSingleThread(float *A, float *B, float *matResult, int m, int p, int n)
{
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            float temp = 0;
            for(int k=0; k<p; k++){
                temp += A[i*p+k] * B[k*n + j];
            }
            matResult[i*n+j] = temp;
        }
    }
}
void printMatrix(float* M,int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%f ",M[i*col+j]);
        }
        printf("\n");
    }
}
int main(int argc, char ** argv)
{
	int m = atoi(argv[1]);
    printf("%d\n", m);
    int p = atoi(argv[2]);
    printf("%d\n", p);
    int n = atoi(argv[3]);
    printf("%d\n", n);
    clock_t start,finish;
    double totaltime;
    float *A, *B, *C;
    B=new float[p*n];
    A=new float[m*p];
    C=new float[m*n];
    initMatrixWithRV(A,m,p,9899);
    initMatrixWithRV(B,p,n,12);
        //printf("matrix A:\n");
        //printMatrix(A,m,p);
       // printf("matrix B:\n");
       // printMatrix(B,p,n);
    start=clock();
    matMultiplyWithSingleThread(A,B,C,m,p,n);
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("time=%f\n",totaltime);
        //printf("result:\n");
       // printMatrix(C,m,n);
  
    delete B;
    delete A;
    delete C;


    return 0;
    
}