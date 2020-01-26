#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	float d;
	float area,sum;

	if(rank == 0)
	{
		printf("Enter d:");
		scanf("%f",&d);
	}

	MPI_Bcast(&d,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	area = (4/1+rank*rank);
	MPI_Reduce(&area,&sum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
		printf("Sum is %f", sum);

	MPI_Finalize();
}


