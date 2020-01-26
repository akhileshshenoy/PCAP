#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	int sc,mat[16],row[4],row1[4];


	if(rank == 0)
	{
		printf("Enter matrix:");
		for(int i = 0;i<16;i++)
		{
			scanf("%d",&mat[i]);
		}
	}

	MPI_Scatter(mat,4,MPI_INT,row,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(&row,&row1,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);


	for(int i =0;i<4 ;i++)
	{
		printf("%d\t",row1[i]);
		if(i==3) 
			printf("\n");
	}

	MPI_Finalize();
}


