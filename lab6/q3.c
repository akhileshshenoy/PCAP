#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE 0x100000

int main (void) {

	int i;

	int LIST_SIZE;

	printf("How many numbers?: ");
	scanf("%d", &LIST_SIZE);

	int *A = (int *)malloc(sizeof(int) * LIST_SIZE);
	printf("Enter the numbers to be sorted:");
	for (i = 0; i < LIST_SIZE; ++i) {
		scanf("%d", &A[i]);
	}

	FILE *kernel_code_file = fopen("q3.cl", "r");
	if (kernel_code_file == NULL) {
		printf("Kernel loading failed.");
		exit(1);
	}

	char *source_str = (char *)malloc(MAX_SOURCE_SIZE);
	size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, kernel_code_file);

	fclose(kernel_code_file);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;

	cl_uint ret_num_devices, ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);

	cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &ret);

	cl_mem mem_obj_a = clCreateBuffer(context, CL_MEM_READ_WRITE, LIST_SIZE * sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, mem_obj_a, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program, "odd", &ret);
	cl_kernel kernel2 = clCreateKernel(program, "even", &ret);
	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void *)&mem_obj_a);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void *)&mem_obj_a);

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

for(int k=0;k<(LIST_SIZE/2+1);k++)
{
	ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);

}


	ret = clEnqueueReadBuffer(command_queue, mem_obj_a, CL_TRUE, 0, LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
	printf("After Sorting: ");                                                                                                                   
	for (i = 0; i < LIST_SIZE; ++i) {
		printf("%d ",A[i]);
	}
	printf("\n");

	clFlush(command_queue);
	clReleaseKernel(kernel1);
	clReleaseKernel(kernel2);

	clReleaseProgram(program);

	clReleaseMemObject(mem_obj_a);
	//clReleaseMemObject(mem_obj_b);
	
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	free(A);
	//free(B);
	
	return 0;

}




// __kernel void odd(__global int*A)
// {
// 	int id=get_global_id(0);
// 	int n=get_global_size(0),t;
	
// 	if(id%2!=0 && (id+1)!=n)
// 	{
// 		if(A[id]>A[id+1])
// 		{
// 			t=A[id];
// 			A[id]=A[id+1];
// 			A[id+1]=t;
// 		}
// 	}
// }


// __kernel void even(__global int*A)
// {
// 	int id=get_global_id(0);
// 	int n=get_global_size(0),t;

// 	if(id%2==0 && (id+1)!=n)
// 	{
// 		if(A[id]>A[id+1])
// 		{
// 			t=A[id];
// 			A[id]=A[id+1];
// 			A[id+1]=t;
// 		}
// 	}
// }




