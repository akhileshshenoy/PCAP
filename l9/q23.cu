#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void add(int* d_a,int* d_b,int* d_r)
{
	int col = threadIdx.x;
	int row = blockIdx.x;
	int size = blockDim.x;
	d_r[row*(size)+col] = d_a[row*(size)+col] + d_b[row*(size)+col];	  
}

int main(void)
{
int *a,*b,*r,m,n,i;
int *d_a,*d_b,*d_r;

printf("Enter m,n : ");
scanf("%d %d",&m,&n);

a = (int*)malloc(m*n*sizeof(int));
b = (int*)malloc(m*n*sizeof(int));
r = (int*)malloc(m*n*sizeof(int));

printf("Enter matrix 1:\n");
for(i=0;i<m*n;i++)
{
	scanf("%d",&a[i]);	
}

printf("Enter matrix 2:\n");
for(i=0;i<m*n;i++)
{
	scanf("%d",&b[i]);	
}

cudaMalloc((void **)&d_a,(m*n)*sizeof(int));
cudaMalloc((void **)&d_b,(m*n)*sizeof(int));
cudaMalloc((void **)&d_r,(m*n)*sizeof(int));


cudaMemcpy(d_a,a,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_b,b,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_r,r,(m*n)*sizeof(int),cudaMemcpyHostToDevice);



add<<<m,n>>>(d_a,d_b,d_r);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }

cudaMemcpy(r,d_r,(m*n)*sizeof(int),cudaMemcpyDeviceToHost);
 
printf("Result matrix :\n");
for(i=0;i<m*n;i++)
{
	printf("%d ",r[i]);
	if((i+1)%m==0)
		printf("\n");	
}

}