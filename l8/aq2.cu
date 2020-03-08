%%cu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
__global__ void add(char * d_res , char * d_buffer)
{
    int tid = threadIdx.x;
    int start = (tid*tid + tid)/2 ;
    for(int i = 1 ;i<=tid+1;i++)
    {
        d_res[start]=d_buffer[tid];
        start++;
    }
    
 }
int main(void)
{

char buffer[100] ="abcdef";
char res[100]="";
int length = strlen(buffer) ;
int len2 = (length*(length+1))/2 + 1 ;
char * d_res ; 
char * d_buffer ; 


cudaMalloc((void **)&d_res,(len2) * sizeof(char));
cudaMalloc((void **)&d_buffer,(length+1)*sizeof(char));


cudaMemcpy(d_buffer,buffer,(length+1)*sizeof(char),cudaMemcpyHostToDevice);

add<<<1,length>>>(d_res,d_buffer);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }
cudaMemcpy(&res,d_res,sizeof(char) * (len2-1),cudaMemcpyDeviceToHost);
res[len2-1]='\0';
printf("Result :%s",res);

}