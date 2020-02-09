__kernel void vector_swap(__global int *A)
{
	int i = get_global_id(0);
	int j =0;

	while(j<i)
	{
		A[j] = A[j] + A[j+2];
		A[j+2] = A[j] - A[j+2];
		A[j] = A[j] - A[j+2];
		j++;
		A[j] = A[j] + A[j+2];
		A[j+2] = A[j] - A[j+2];
		A[j] = A[j] - A[j+2];
		j+=3;
	}
}