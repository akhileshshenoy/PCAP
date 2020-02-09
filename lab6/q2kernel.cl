__kernel void prl_selsort(__global int *a)
{
	int i = get_global_id(0);

	int min = a[i],minind = i;
	for(int j = i;j<10;j++)
	{
		if(a[j]<min)
			minind = j;
	}
	a[i] = a[i]+a[j];
	a[j] = a[i]-a[j];
	a[i] = a[i]-a[j];
	print("%d",j);
}