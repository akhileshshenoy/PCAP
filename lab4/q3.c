#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	int sc,mat[9],totocc;


	if(rank == 0)
	{
		printf("Enter matrix:");
		for(int i = 0;i<9;i++)
		{
			scanf("%d",&mat[i]);
		}
		printf("Enter search element:");
		scanf("%d",&sc);
	}

	int occ=0,row[3];
	MPI_Bcast(&sc,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(mat,3,MPI_INT,row,3,MPI_INT,0,MPI_COMM_WORLD);
	for(int i =0;i<3;i++)
	{
		if(row[i]==sc)
			occ++;
	}

	MPI_Reduce(&occ,&totocc,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
		printf("Total occurance is %d", totocc);

	MPI_Finalize()
}


