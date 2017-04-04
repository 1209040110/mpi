#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f(double);
double f(double a)
{
	return (4.0/(1+a*a));
}
int main(int argc, char ** argv)
{
	int done=0,n,myid,numprocs,i;
	double mypi,pi,w,sum,x;
    double startwtime=0.0,endwtime;
    MPI_Init(&argc, &argv);
	n=100000;
    if(myid==0)
    {
        startwtime=MPI_Wtime();
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    printf("i am rank %d\n",myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    printf("process size is %d\n",numprocs);

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    w=1.0/n;
    sum=0.0;
    for(i=myid+1;i<=n;i+=numprocs)
    {
    	x=w*(i-0.5);
    	sum+=f(x);
    }
    mypi=w*sum;
    MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0)
    {
    	printf("pi is roughly  %.16f\n",pi);
        endwtime=MPI_Wtime();
        printf("wall clock time=%f\n",endwtime - startwtime);
    }
    MPI_Finalize();
    return 0;
    
}