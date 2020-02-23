#include<cuda_runtime.h>
#include<stdio.h>
#include<stdlib.h>

__global__ void q3(int* x,int* y,int* f,int* n,int* alpha)
{
	int id=blockIdx.x*blockDim.x+threadIdx.x;

	if(id<*n)
		f[id]=(*alpha)*x[id]+y[id];
}

int main()
{
	int a[100],b[100],c[100],n,alpha,*dalpha,*da,*db,*dc;
	int *dn;

	printf("Enter size: ");
	scanf("%d",&n);
	printf("Enter alpha: ");
	scanf("%d",&alpha);
	printf("Enter elements for A: ");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter elements for B: ");
	for(int i=0;i<n;i++)
		scanf("%d",&b[i]);

	cudaMalloc((void**)&da,n*sizeof(int));
	cudaMalloc((void**)&db,n*sizeof(int));
	cudaMalloc((void**)&dc,n*sizeof(int));
	cudaMalloc((void**)&dn,sizeof(int));
	cudaMalloc((void**)&dalpha,sizeof(int));

	cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(db,b,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(dn,&n,sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(dalpha,&alpha,sizeof(int),cudaMemcpyHostToDevice);

	q3<<<n,1>>>(da,db,dc,dn,dalpha);

	cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

	for(int i=0;i<n;i++)
		printf("%d*%d+%d=%d\n",alpha,a[i],b[i],c[i]);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	cudaFree(dn);
	cudaFree(dalpha);
}