#include "atax.h"
#include "../utilities/include/pencilbench.h"

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_atax(int m, int n,
		DATA_TYPE PENCILBENCH_2D(A,M,N,m,n),
		DATA_TYPE PENCILBENCH_1D(x,N,n),
		DATA_TYPE PENCILBENCH_1D(y,N,n),
		DATA_TYPE PENCILBENCH_1D(tmp,M,m))
{
	int i, j;
#pragma pencil independent
	for (i = 0; i < n; i++)
		y[i] = 0;
#pragma pencil independent
	for (i = 0; i < m; i++)
	{
		tmp[i] = SCALAR_VAL(0.0);
#pragma pencil independent reduction(+ : tmp[i])
		for (j = 0; j < n; j++)
			tmp[i] += A[i][j] * x[j];
#pragma pencil independent reduction(+ : y[j])
		for (j = 0; j < n; j++)
			y[j] += A[i][j] * tmp[i];
	}

}
