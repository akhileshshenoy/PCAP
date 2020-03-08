#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void add(int* d_a,int* d_b,int* d_r,int *d_m)
{
	int n = threadIdx.x;
	for(int i = 0;i<(*d_m);i++)
	{
		d_r[n*(*d_m)+i] = d_a[n*(*d_m)+i] + d_b[n*(*d_m)+i];
	}  
}

int main(void)
{
int *a,*b,*r,m,n,i;
int *d_a,*d_b,*d_r,*d_m;

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
cudaMalloc((void **)&d_m,sizeof(int));

cudaMemcpy(d_a,a,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_b,b,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_r,r,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_m,&m,sizeof(int),cudaMemcpyHostToDevice);


add<<<1,n>>>(d_a,d_b,d_r,d_m);
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