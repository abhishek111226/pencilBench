#include "lu.h"
#include"../utilities/include/pencilbench.h"


void kernel_lu(int n,DATA_TYPE PENCILBENCH_2D(A,N,N,n,n))
{
	int i, j, k;
	for (k = 0; k < n; k++)
	{
#pragma pencil independent
		for (j = k + 1; j < n; j++)
			A[k][j] = A[k][j] / (A[k][k]==0?1:A[k][k]);
#pragma pencil independent
		for(i = k + 1; i < n; i++)
#pragma pencil independent reduction(+ : A[i][j])
			for (j = k + 1; j < n; j++)
				A[i][j] -=  A[i][k] * A[k][j];
	}
}
