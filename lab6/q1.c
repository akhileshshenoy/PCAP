//sample code, notQ1
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <time.h>


#define MAX_SOURCE_SIZE	(0x100000)

int main()
{
	int i;
	time_t start, end;
	start = clock();

	int LIST_SIZE =100;

	char *A = (char*)malloc(sizeof(char)*100);
	printf("Enter String: ");
	scanf("%s",A);

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("q1kernel.cl","r");

	if(!fp)
	{
		printf("Failed to load kernel.\n");
		getchar();
		exit(1);
	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&ret_num_devices);

	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,CL_QUEUE_PROFILING_ENABLE,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE* sizeof(char),NULL,&ret);
	//cl_mem b_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE* sizeof(int),NULL,&ret);
	// cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,LIST_SIZE* sizeof(int),NULL,&ret);

	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(char),A,0,NULL,NULL);
	//ret = clEnqueueWriteBuffer(command_queue,b_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),B,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	cl_kernel kernel = clCreateKernel(program,"string_copy",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	//ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
	//ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&c_mem_obj);

	size_t global_item_size = 3;
	size_t local_item_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,&event);

	ret = clFinish(command_queue);

	cl_ulong time_start,time_end;
	double total_time;

	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);

	total_time=time_end-time_start;

	//int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
	//ret = clEnqueueReadBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE* sizeof(char)*3,A,0,NULL,NULL);

	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	//ret = clReleaseMemObject(b_mem_obj);
	//ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	end = clock();
	printf("\n\nTime taken to ex kernel in msec = %0.3f\n",total_time/1000000);
	printf("Time taken to ex whole in msec = %0.3f",(end-start)/(double)CLOCKS_PER_SEC);
	free(A);
	//free(B);
	//free(C);
	getchar();
	return 0;

}