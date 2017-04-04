#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
double f(double x)
{
    return 4.0/(1+x*x);
}
double cal(int* a,int len,int n)
{
    int i;
    double res=0.0;
    for(i=0;i<len;i++)
    {
        res+=f((a[i]-0.5)/n*1.0);
    }
    return res;
}
int main(int argc, char ** argv)
{
    int n=1000000;
    int data[n];
    int i;
    int size,rank,count;
    MPI_Status status;
    for(i=0;i<n;i++)
    {
        data[i]=i+1;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("i am rank %d\n",rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("process size is %d\n",size);

    //split the input data
    //rank 0 for reduce
    int avgn=n/(size-1);
    if(rank!=0&&rank<size-1)
    {
        double r=cal(&data[(rank-1)*avgn],avgn,n);
        MPI_Send(&r,1, MPI_DOUBLE, 0,0,
                 MPI_COMM_WORLD);
    }
    else if(rank==size-1)
    {
        double r=cal(&data[(rank-1)*avgn],n-(size-2)*avgn,n);
        MPI_Send(&r,1, MPI_DOUBLE, 0,0,
                 MPI_COMM_WORLD);
    }
    else if(rank==0){  //process 0
            int j;
            double res[size-1];
            for(j=0;j<size-1;j++)
            {
                MPI_Recv(&res[j],1, MPI_DOUBLE, MPI_ANY_SOURCE,
                     0, MPI_COMM_WORLD, &status);
             }
            //MPI_Get_count(&status, MPI_INT, &count);
           // printf("worker ID: %d; task ID: %d; count: %d\n",
           //        status.MPI_SOURCE, status.MPI_TAG, count);
            double pi=0.0;
            for(i=0;i<size-1;i++)
            {
                pi+=1.0/n*res[i];
            }
            printf("pi is roughly %.15f\n",pi);
        
    }

     MPI_Finalize(); return 0;
}
