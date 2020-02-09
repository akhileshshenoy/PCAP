__kernel void vector_com(__global int *A,__global int *C)
{
	int i = get_global_id(0);
	int dec = A[i];
	int temp=1,bin = 0;
	
	while(dec>0)
	{
		bin += (dec%2)*temp;
		dec /= 2;
		temp*=10;	
	}
	
	int temp1=1,com = 0,temp2;
	
	while(bin>0)
	{
		if((bin%10)==1)
			temp2 = 0;
		else 
		 	temp2 = 1;
		com += temp2*temp1;
		bin /= 10;
		temp1*=10;	
	}
	C[i] = com;
}