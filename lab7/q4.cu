#include<cuda_runtime.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

__global__ void add(float* x,float* y,int* n)
{
	int id=blockIdx.x*blockDim.x+threadIdx.x;

	if(id<*n)
		y[id]=sinf(x[id]);
}

int main()
{
	float a[100],res[100],*da,*db;
	int *dn;
	int n;

	printf("Enter size");
	scanf("%d",&n);
	printf("Enter the elements:");
	for(int i=0;i<n;i++)
		scanf("%f",&a[i]);

	cudaMalloc((void**)&da,n*sizeof(float));
	cudaMalloc((void**)&db,n*sizeof(float));
	cudaMalloc((void**)&dn,sizeof(int));

	cudaMemcpy(da,a,n*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(dn,&n,sizeof(int),cudaMemcpyHostToDevice);

	add<<<n,1>>>(da,db,dn);

	cudaMemcpy(res,db,n*sizeof(float),cudaMemcpyDeviceToHost);

	printf("\n N,1: ");

	for(int i=0;i<n;i++)
		printf("sine(%f)  =  %f\n",a[i],res[i]);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dn);
}