#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    time_t t;
    srand((unsigned) time(&t));
    for(i=0;i<n;i++)
    {
        data[i]=i+1;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("i am rank %d\n",rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("process size is %d\n",size);
    if (rank == 1)  //process 1
    {
        double r1=cal(data,200000,n);
        //printf("------%f\n", r1);
        MPI_Send(&r1,1, MPI_DOUBLE, 0, 0,
                 MPI_COMM_WORLD);
    }
    else if (rank == 2)  //process 2
    {
        double r2=cal(&data[200000],200000,n);
        MPI_Send(&r2,1, MPI_DOUBLE, 0, 200000,
                 MPI_COMM_WORLD);
    }
    else if (rank == 3)  // process 3
    {
        double r3=cal(&data[400000],200000,n);
        MPI_Send(&r3,1, MPI_DOUBLE, 0, 400000,
                 MPI_COMM_WORLD);
    }
    else if (rank == 4)  //process 4
    {
        double r4=cal(&data[600000],200000,n);
        MPI_Send(&r4,1, MPI_DOUBLE, 0, 600000,
                 MPI_COMM_WORLD);
    }
    else if (rank == 5)  //process 5
    {
        double r5=cal(&data[800000],200000,n);
        MPI_Send(&r5,1, MPI_DOUBLE, 0, 800000,
                 MPI_COMM_WORLD);
    }
    else if(rank==0){  //process 0
            int j;
            double res[5];
            for(j=0;j<5;j++){
                MPI_Recv(&res[j],1, MPI_DOUBLE, MPI_ANY_SOURCE,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &status);
             }
            //MPI_Get_count(&status, MPI_INT, &count);
           // printf("worker ID: %d; task ID: %d; count: %d\n",
           //        status.MPI_SOURCE, status.MPI_TAG, count);
            double pi=0.0;
            for(i=0;i<5;i++)
            {
                pi+=1.0/n*res[i];
            }
            printf("pi is roughly %f\n",pi);
        
    }

     MPI_Finalize(); return 0;
}
