#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc, char *argv[])
{
	int rank,size;
	int x[10],y,num;
	//float buf[100];
	void* buf;
	int sz =100;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	MPI_Buffer_attach(buf,sz);
	if(rank == 0)
	{
		printf("Enter %d integers:",size-1);
		 	
		for(int i =0;i<size-1;i++)
		{
			scanf("%d",&x[i]);
		}

		for(int i =0;i<size-1;i++)
		{
			MPI_Bsend(&x[i],1,MPI_INT,i+1,i+1,MPI_COMM_WORLD);
			printf("Sent %d to prcess %d.\n",x[i],i+1);
		}  
		
	}
	else if(rank % 2 == 0)
	{
		MPI_Recv(&y,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		printf("%d square is %d in (%d).\n",y,y*y,rank);
	}
	else
	{
		MPI_Recv(&y,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		printf("%d cube is %d in (%d).\n",y,y*y*y,rank);
	}
	MPI_Buffer_detach(buf,&sz);

	MPI_Finalize();
	return 0;
}  