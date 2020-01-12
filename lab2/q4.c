#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int x;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0)
	{
		printf("Enter a number:(master process) - ");
		scanf("%d",&x);
		MPI_Send(&x,1,MPI_INT,rank+1,rank+1,MPI_COMM_WORLD);
		printf("Sent(master process) %d to prcess %d.\n",x,rank+1);
	}
	else if(rank == size-1)
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,rank,MPI_COMM_WORLD,&status);
		printf("Received %d from process %d.",x,rank-1);
		x++;
		MPI_Send(&x,1,MPI_INT,0,0,MPI_COMM_WORLD);
		printf("Sent(from process %d) %d to prcess %d.\n",rank,x,0);
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,rank,MPI_COMM_WORLD,&status);
		printf("Received %d from process %d.",x,rank-1);
		x++;
		MPI_Send(&x,1,MPI_INT,rank+1,rank+1,MPI_COMM_WORLD);
		printf("Sent(from process %d) %d to prcess %d.\n",rank,x,rank+1);
	}

	MPI_Finalize();
	return 0;
}  