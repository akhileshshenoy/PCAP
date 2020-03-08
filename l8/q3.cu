%%cu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
__global__ void add(char * d_searchfor , char * d_buffer, int * d_start,int * d_end,int * res)
{
    int threadid = threadIdx.x;
    char temp[100];
    int pos = 0 ;
    int check = 0 ;
    for(int i = d_start[threadid];i<=d_end[threadid];i++)
    {
        if(d_searchfor[pos]=='\0')
        {
            check=1 ;
            break ;
        }
        if(d_buffer[i]!=d_searchfor[pos])
        {
            check = 1 ;
            break ;
        }
        pos ++ ;
    }
    if(check==0)
    {
        atomicAdd(res,1);
    }
 }
int main(void)
{

char buffer[100] ="a bcdef a a a xyt a";
 char searchfor[100]="a";
int wstart[50];
int wend[50];
int wc = 0 ; 
int length = strlen(buffer) ;
int slen = strlen(searchfor);
 int result = 0 ;

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
 
char * d_searchfor ; 
char * d_buffer ; 
int * d_start ;
int * d_end ;
int * d_res ;

cudaMalloc((void **)&d_searchfor,(slen+1) * sizeof(char));
cudaMalloc((void **)&d_buffer,(length+1)*sizeof(char));
cudaMalloc((void **)&d_start , sizeof(int)*wc);
cudaMalloc((void **)&d_end ,sizeof(int) * wc);
cudaMalloc((void **)&d_res ,sizeof(int));
  
cudaMemcpy(d_buffer,buffer,(length+1)*sizeof(char),cudaMemcpyHostToDevice);
cudaMemcpy(d_searchfor,searchfor,(slen+1)*sizeof(char),cudaMemcpyHostToDevice);
cudaMemcpy(d_start , wstart , sizeof(int)*wc,cudaMemcpyHostToDevice);
cudaMemcpy(d_end , wend , sizeof(int)*wc,cudaMemcpyHostToDevice);
 cudaMemcpy(d_res , &result , sizeof(int),cudaMemcpyHostToDevice);


add<<<1,wc>>>(d_searchfor,d_buffer,d_start,d_end,d_res);
cudaError_t error = cudaGetLastError();
 if(error!= cudaSuccess)
 {
	 	printf("%s\n",cudaGetErrorString(error));
 }
cudaMemcpy(&result,d_res,sizeof(int),cudaMemcpyDeviceToHost);

printf("Result :%d",result);

}