
 __kernel void strcopy(__global char*A,__global char*B,int n)
 {
 	int id=get_global_id(0);
 	int j;
 for( j=0;j<n;j++)
 	B[j+id*n]=A[j];

 }