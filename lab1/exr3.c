#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if (rank==0)
		printf("2 + 3 = %d \n",2+3);
	else if (rank==1)
		printf("2 - 3 = %d \n",2-3);
	else if (rank==2)
		printf("2 * 3 = %d \n",2*3);
	else if (rank==3)
		printf("2 / 3 = %f \n",2.0/3);
	else
		printf("%d\n",rank );

	MPI_Finalize();

}