#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>
#define DATA_SIZE (1024)

int main (int argc, char** argv) {

	int err;                          
	size_t global_work_size;			
	size_t local_work_size;				
	cl_platform_id platform_id;			
	cl_device_id device_id;				
	cl_context context;					
	cl_command_queue command_queue;		
	cl_program program;					
	cl_kernel kernel;					

	cl_mem mem_input;					
	cl_mem mem_indices;					

	int i = 0;

	
	char input[100];
	printf("Enter string: ");
	gets(input);

	
	unsigned int len = strlen(input);
	char *output = (char *)malloc(len * sizeof(char));

	int spaces = 0;
	for (i = 0; i < len; ++i) {
		spaces += (input[i] == ' ');
	}
	spaces += 1;
	//printf("Spaces count = %d\n", spaces);

	int *indices = (int *)calloc(spaces + 1, sizeof(int));
	int k = 0;
	indices[k++] = -1;
	//printf("Indices: %d ", indices[k-1]);

	for (i = 0; i < len; ++i) {
		if (input[i] == ' ') {
			indices[k++] = i;
			printf("%d ", indices[k-1]);
		}
	}
	indices[k++] = len;
	//printf("%d\n", indices[k-1]);

	FILE *kernel_code_file = fopen("q4.cl", "r");
	if (kernel_code_file == NULL) {
		printf("Kernel loading failed.");
		exit(1);
	}

	char *source_str = (char *)malloc(DATA_SIZE);
	size_t source_size = fread(source_str, 1, DATA_SIZE, kernel_code_file);
	source_str[source_size] = '\0';

	fclose(kernel_code_file);

	err = clGetPlatformIDs(1, &platform_id, NULL);
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);

	if (err != CL_SUCCESS) {
		printf("Error: Failed to create a device group!\n");
		return EXIT_FAILURE;
	}


	context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);

	if (!context) {
		printf("Error: Failed to create a compute context!\n");
		return EXIT_FAILURE;
	}


	command_queue = clCreateCommandQueue(context, device_id, 0, &err);

	if (!command_queue) {
		printf("Error: Failed to create a command commands!\n");
		return EXIT_FAILURE;
	}

	mem_input = clCreateBuffer(context,  CL_MEM_READ_WRITE,  sizeof(char) * len, NULL, NULL);
	mem_indices = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(int) * spaces + 1, NULL, NULL);

	if (!mem_input) {
		printf("Error: Failed to allocate device memory!\n");
		exit(1);
	}


	err = clEnqueueWriteBuffer(command_queue, mem_input, CL_TRUE, 0, sizeof(char) * len, input, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(command_queue, mem_indices, CL_TRUE, 0, sizeof(int) * spaces + 1, indices, 0, NULL, NULL);

	if (err != CL_SUCCESS) {
		printf("Error: Failed to write to source array!\n");
		exit(1);
	}

	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, NULL, &err);

	if (!program) {
		printf("Error: Failed to create compute program!\n");
		return EXIT_FAILURE;
	}

	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

	if (err != CL_SUCCESS) {
		size_t len;
		char buffer[2048];
		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(1);
	}


	kernel = clCreateKernel(program, "reversestr", &err);

	if (!kernel || err != CL_SUCCESS) {
		printf("Error: Failed to create compute kernel!\n");
		exit(1);
	}

	err  = 0;
	err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem_input);
	err |= clSetKernelArg(kernel, 1, sizeof(int), &len);
	err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &mem_indices);

	if (err != CL_SUCCESS) {
		printf("Error: Failed to set kernel arguments! %d\n", err);
		exit(1);
	}


	global_work_size = spaces;
	local_work_size = 1;

	//printf("Global work size = %li, Local work size = %li\n", global_work_size, local_work_size);

	err = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);

	if (err) {
		printf("Error: Failed to execute kernel!\n");
		return EXIT_FAILURE;
	}

 	clFinish(command_queue);

	err = clEnqueueReadBuffer(command_queue, mem_input, CL_TRUE, 0, sizeof(char) * len, output, 0, NULL, NULL );

	if (err != CL_SUCCESS) {
		printf("Error: Failed to read output array! %d\n", err);
		exit(1);
	}

	printf("Inp:%s\nRev:%s", input, output);


	clReleaseMemObject(mem_input);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	return 0;

}


