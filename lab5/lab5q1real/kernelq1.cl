__kernel void vector_oct(__global int *A,__global int *C)
{
	int i = get_global_id(0);
	int dec = A[i];
	int temp=1,oct = 0;
	
	while(dec>0)
	{
		oct += (dec%8)*temp;
		dec /= 8;
		temp*=10;	
	}
	C[i] = oct;
}