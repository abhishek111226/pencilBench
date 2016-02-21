#include"gemver.h"
#include "../utilities/include/pencilbench.h"

/* FIXME: Infinite Compilation Time */

/* kernel function */
void kernel_gemver (int n,DATA_TYPE alpha, DATA_TYPE beta,
		DATA_TYPE PENCILBENCH_2D_ARG(A,N,N,n,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(w,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(x,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(y,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(z,N,n))
	/* PENCIL Code  */
{
	int i, j;

	#pragma pencil independent
	for (i = 0; i < n; i++)
		#pragma pencil independent reduction(+: A[i][j])
		for (j = 0; j < n; j++)
			A[i][j] = A[i][j] + u1[i] * v1[j] + u2[i] * v2[j];

	#pragma pencil independent
	for (i = 0; i < n; i++)
		#pragma pencil independent reduction(+: x[i])
		for (j = 0; j < n; j++)
			x[i] = x[i] + beta * A[j][i] * y[j];
	#pragma pencil independent
	for (i = 0; i < n; i++)
		x[i] = x[i] + z[i];

	#pragma pencil independent
	for (i = 0; i < n; i++)
		#pragma pencil independent reduction(+: w[i])
		for (j = 0; j < n; j++)
			w[i] = w[i] +  alpha * A[i][j] * x[j];
}
