__kernel void string_copy(__global char *A)
{
	A[i] = 'a';
	printf("%s",A);
}