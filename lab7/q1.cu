#include<cuda_runtime.h>
#include<stdio.h>
#include<stdlib.h>

__global__ void add(int* a,int* b,int* c,int* n)
{
	int id=blockIdx.x*blockDim.x+threadIdx.x;

	if(id<*n)
		c[id]=a[id]+b[id];
}

int main()
{
	int a[100],b[100],c[100],n,*da,*db,*dc;
	int *dn;

	printf("Enter size: ");
	scanf("%d",&n);
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

	cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(db,b,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(dn,&n,sizeof(int),cudaMemcpyHostToDevice);

	add<<<n,1>>>(da,db,dc,dn);

	cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

	printf("\nBlock size as N: ");

	for(int i=0;i<n;i++)
		printf("%d+%d=%d\n",a[i],b[i],c[i]);

	add<<<1,n>>>(da,db,dc,dn);

	cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

	printf("\nN Threads: ");

	for(int i=0;i<n;i++)
		printf("%d+%d=%d\n",a[i],b[i],c[i]);

	int tsize=256;
	add<<<(n+tsize-1)/tsize,tsize>>>(da,db,dc,dn);

	cudaMemcpy(c,dc,n*sizeof(int),cudaMemcpyDeviceToHost);

	printf("\n256 threads: ");

	for(int i=0;i<n;i++)
		printf("%d+%d=%d\n",a[i],b[i],c[i]);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	cudaFree(dn);
}