#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
void sort(int* a,int n)
{
	int i,j;
	int tmpmin,tmpminindex;
	int tmp;
	for(i=0;i<n;i++)
	{
		tmpmin=a[i];
		tmpminindex=i;
		for(j=i+1;j<n;j++)
		{
			if(a[j]<tmpmin)
			{
				tmpmin=a[j];
				tmpminindex=j;
			}
		}
		tmp=a[i];
		a[i]=tmpmin;
		a[tmpminindex]=tmp;
	}
}
//low--mid-1  mid--high 
void merge(int* arr, int low, int mid, int high){
	int n=high-low+1;
	int tmparr[n];
	int i=0,j;
	int tmpmid=mid;
	while(i<n)
	{
		if(low==tmpmid)
		{
			while(mid<=high)
			{
				tmparr[i++]=arr[mid++];
			}
			break;
		}
		if(mid>high)
		{
			while(low<mid)
			{
				tmparr[i++]=arr[low++];
			}
			break;
		}
		if(arr[low]<arr[mid])
		{
			tmparr[i++]=arr[low++];
		}
		else
		{
			tmparr[i++]=arr[mid++];
		}

	}
	for(i=0;i<n;i++)
	{
		arr[i]=tmparr[i];
	}
    
}
int main(int argc, char ** argv)
{
    int rank, a[12]={8,23,19,67,45,35,1,24,13,30,3,5}, b[6];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0){
        MPI_Send(&a[6], 6, MPI_INT, 1, 0, MPI_COMM_WORLD);
        sort(a, 6);
        MPI_Recv(b, 6, MPI_INT, 1, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);

        /* Serial: Merge array b and sorted part of array a */
        int i;
        for(i=6;i<12;i++)
        {
        	a[i]=b[i-6];
        }
        merge(a,0,6,11);
        for(i=0;i<12;i++)
        {
        	printf("%d ", a[i]);
        }
        printf("\n");
    }
    else if (rank == 1) {
        MPI_Recv(b, 6, MPI_INT, 0, 0, MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
        sort(b, 6);
        MPI_Send(b, 6, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize(); return 0;
}


