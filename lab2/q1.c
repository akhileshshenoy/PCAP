#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size;
	char x[10],y[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	if(rank == 0)
	{
		printf("Enter a word:(process %d)",rank);
		scanf("%s",&x);
		MPI_Ssend(&x,10,MPI_CHAR,1,1,MPI_COMM_WORLD);
		printf("Sent(process %d) to prcess %d.\n",rank,1);
	}
	else
	{
		MPI_Recv(&y,10,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		for(int i = 0; i < strlen(y); i++)
		{
			if (y[i] < 92)
			{
				y[i]+=32;
			}
			else
			{
				y[i]-=32;
			}
		}
		printf("Received %s from process %d.",y,0);
	}

	MPI_Finalize();
	return 0;
}  