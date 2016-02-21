#include <pencil.h>
#include "jacobi-1d.h"
#include "../utilities/include/pencilbench.h"

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_jacobi_1d(int tsteps,
		int n,
		DATA_TYPE PENCILBENCH_1D(A,N,n),
		DATA_TYPE PENCILBENCH_1D(B,N,n))
{
	int t, i;

	for (t = 0; t < tsteps; t++)
	{
#pragma pencil independent
		for (i = 1; i < n - 1; i++)
			B[i] = 0.33333 * (A[i-1] + A[i] + A[i + 1]);
#pragma pencil independent
		for (i = 1; i < n - 1; i++)
			A[i] = 0.33333 * (B[i-1] + B[i] + B[i + 1]);
	}

}
