#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void add(char * d_resbuffer , char * d_buffer, int * d_length)
{
		
	int id = threadIdx.x ;
	int start = id * (*d_length);
	for(int i = 0 ; i<=(*d_length)-1;i++)
	{
		d_resbuffer[start] = d_buffer[i];
		start ++ ;
	}
}
int main(void)
{

char buffer[100] ="Hello";

char res[100] = "";

int length = strlen(buffer) ;

int duplicate = 4 ;
 
char * d_resbuffer ; 
  
char * d_buffer ; 
int * d_length ;

cudaMalloc((void **)&d_resbuffer,(length*duplicate+1) * sizeof(char));
cudaMalloc((void **)&d_buffer,(length+1)*sizeof(char));
cudaMalloc((void **)&d_length , sizeof(int));
  
cudaMemcpy(d_buffer,buffer,(length+1)*sizeof(char),cudaMemcpyHostToDevice);
cudaMemcpy(d_length , &length , sizeof(int),cudaMemcpyHostToDevice);


add<<<1,duplicate>>>(d_resbuffer,d_buffer,d_length);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }
cudaMemcpy(res,d_resbuffer,(length*duplicate)*sizeof(char),cudaMemcpyDeviceToHost);

 int location = length * duplicate ;
 res[location]='\0';
 
printf("Result :%s",res);

}