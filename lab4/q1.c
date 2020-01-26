#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int fact = 1;
	for(int i=1; i<=rank+1; i++)
	{
		fact*=i;
	}
	int factsum;

	int error = MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	if(error != MPI_SUCCESS)
		printf("error");
	if(rank == size-1)
		printf("Sum is %d", factsum);

	MPI_Finalize();
}


