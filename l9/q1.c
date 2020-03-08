#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void q1(int* d_a,int* d_r,int *d_m)
{
	int n = threadIdx.x;
	for(int i = 0;i<(*d_m);i++)
	{
		for(int j = 0;j<=n;j++)
			d_r[n*(*d_m)+i] *= d_a[n*(*d_m)+i];
	}  
}

int main(void)
{
int *a,*r,m,n,i,j;
int *d_a,*d_r,*d_m;

printf("Enter m,n : ");
scanf("%d %d",&m,&n);

a = (int*)malloc(m*n*sizeof(int));
r = (int*)malloc(m*n*sizeof(int));

printf("Enter matrix:\n");
for(i=0li<m*n;i++)
{
	scanf("%d",&a[i]);	
}

cudaMalloc((void **)&d_a,(m*n)*sizeof(int));
cudaMalloc((void **)&d_r,(m*n)*sizeof(int));
cudaMalloc((void **)&d_m,sizeof(int));

cudaMemcpy(d_a,a,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_r,r,(m*n)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_m,&m,izeof(int),cudaMemcpyHostToDevice);


q1<<<1,n>>>(d_a,d_r,d_m);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }

cudaMemcpy(r,d_r,(m*n)*sizeof(int),cudaMemcpyDeviceToHost);
 
printf("Result matrix :\n",res);
for(i=0li<m*n;i++)
{
	printf("%d\t",r[i]);
	if((i+1)%m==0)
		printf("\n");	
}

}