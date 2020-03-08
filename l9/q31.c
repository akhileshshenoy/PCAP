#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void add(int* d_a,int* d_b,int* d_r,int *d_m,int *d_n)
{
	int n = threadIdx.x;
	for(int i = 0;i<(*d_m);i++)
	{
		int sum = 0;
		for(int j=0;j<(*d_n);j++)
			sum += d_a[n*(*d_m)+j] * d_b[j*(*d_m)+n];
		d_r[n*(*d_m)+i] = sum;
	}  
}

int main(void)
{
int *a,*b,*r,m1,n1,m2,n2,i;
int *d_a,*d_b,*d_r,*d_m,*d_n;







printf("Enter m,n for m1: ");
scanf("%d %d",&m1,&n1);
a = (int*)malloc(m1*n1*sizeof(int));
printf("Enter matrix 1:\n");
for(i=0;i<m1*n1;i++)
{
	scanf("%d",&a[i]);	
}

printf("Enter m,n for m2: ");
scanf("%d %d",&m2,&n2);
b = (int*)malloc(m2*n2*sizeof(int));
printf("Enter matrix 2:\n");
for(i=0;i<m2*n2;i++)
{
	scanf("%d",&b[i]);	
}

r = (int*)malloc(m1*n2*sizeof(int));

cudaMalloc((void **)&d_a,(m1*n1)*sizeof(int));
cudaMalloc((void **)&d_b,(m2*n2)*sizeof(int));
cudaMalloc((void **)&d_r,(m1*n2)*sizeof(int));
cudaMalloc((void **)&d_m,sizeof(int));
cudaMalloc((void **)&d_n,sizeof(int));

cudaMemcpy(d_a,a,(m1*n1)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_b,b,(m2*n2)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_r,r,(m1*n2)*sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_m,&m1,sizeof(int),cudaMemcpyHostToDevice);
cudaMemcpy(d_n,&n1,sizeof(int),cudaMemcpyHostToDevice);



add<<<1,m1>>>(d_a,d_b,d_r,d_m,d_n);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }

cudaMemcpy(r,d_r,(m1*n2)*sizeof(int),cudaMemcpyDeviceToHost);
 
printf("Result matrix :\n");
for(i=0;i<m1*n2;i++)
{
	printf("%d ",r[i]);
	if((i+1)%m==0)
		printf("\n");	
}

}