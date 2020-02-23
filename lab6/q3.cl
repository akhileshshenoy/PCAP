__kernel void odd(__global int*A)
{
	int id=get_global_id(0);
	int n=get_global_size(0),t;
	
	if(id%2!=0 && (id+1)!=n)
	{
		if(A[id]>A[id+1])
		{
			t=A[id];
			A[id]=A[id+1];
			A[id+1]=t;
		}
	}
}


__kernel void even(__global int*A)
{
	int id=get_global_id(0);
	int n=get_global_size(0),t;

	if(id%2==0 && (id+1)!=n)
	{
		if(A[id]>A[id+1])
		{
			t=A[id];
			A[id]=A[id+1];
			A[id+1]=t;
		}
	}
}