#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank; 

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if (rank==0)
	{
		for(int i = 1; i <= 50; i++)
		{
			int flag = 1;
			for(int j = 2; j <= i/2 ; j++)
				if(i%j==0)
					flag = 0;
			if(flag == 1)
				printf("Number %d is prime.\n",i);
			else
				printf("Number %d is not a prime.\n",i);
		}
	}	
	else
	{
		for(int i = 51; i <= 100; i++)
		{
			int flag = 1;
			for(int j = 2; j <= i/2 ; j++)
				if(i%j==0)
					flag = 0;
			if(flag == 1)
				printf("Number %d is prime.\n",i);
			else
				printf("Number %d is not a prime.\n",i);
		}
	}	
	MPI_Finalize();
	return 0;
}