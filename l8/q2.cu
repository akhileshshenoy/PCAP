%%cu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
__global__ void add(char * d_resbuffer , char * d_buffer, int * d_start,int * d_end)
{
 
  int threadid = threadIdx.x ;
  int start = d_start[threadid];
  int end = d_end[threadid];
 
  int pos = start ;
 int till = end-start+1;
  for(int i=1 ;i<=till;i++)
  {
      
      
      d_resbuffer[pos]=d_buffer[end];
      pos ++ ;
      end -- ;
  }
  d_resbuffer[pos]=' ';
  
}
int main(void)
{

char buffer[100] ="what a beautiful day";
int wstart[50];
int wend[50];
int wc = 0 ; 
char res[100] = "";

int length = strlen(buffer) ;
 
 wstart[0]=0 ;
 int spos = 1 ;
 int epos = 0 ;
for(int i = 0 ;i<=length-1;i++)
{
    if(buffer[i]==' ')
    {
        wc++;
        wstart[spos]=i+1 ;
        spos ++ ;
        wend[epos]=i-1 ;
        epos ++ ;
    }
}
wc++;
wend[epos]=length-1;
 
char * d_resbuffer ; 
char * d_buffer ; 
int * d_start ;
int * d_end ;

cudaMalloc((void **)&d_resbuffer,(length+1) * sizeof(char));
cudaMalloc((void **)&d_buffer,(length+1)*sizeof(char));
cudaMalloc((void **)&d_start , sizeof(int)*wc);
cudaMalloc((void **)&d_end ,sizeof(int) * wc);
  
cudaMemcpy(d_buffer,buffer,(length+1)*sizeof(char),cudaMemcpyHostToDevice);
cudaMemcpy(d_start , wstart , sizeof(int)*wc,cudaMemcpyHostToDevice);
cudaMemcpy(d_end , wend , sizeof(int)*wc,cudaMemcpyHostToDevice);


add<<<1,wc>>>(d_resbuffer,d_buffer,d_start,d_end);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }
cudaMemcpy(res,d_resbuffer,(length)*sizeof(char),cudaMemcpyDeviceToHost);
res[length]='\0';
 
printf("Result :%s",res);

}