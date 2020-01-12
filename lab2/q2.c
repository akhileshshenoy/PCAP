#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int x,y;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0)
	{
		for(int i =0;i<size-1;i++)
		{
			x = i+1;
			MPI_Send(&x,1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			printf("Sent %d to prcess %d.\n",i+1,i+1);
		}
		
	}
	else
	{
		MPI_Recv(&y,11,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		printf("Received %d in process %d.\n",y,rank);
	}

	MPI_Finalize();
	return 0;
}  