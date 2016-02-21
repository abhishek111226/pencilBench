#include<pencil.h>
#include"mvt.h"
#include"../utilities/include/pencilbench.h"

void kernel_mvt(int n,
		DATA_TYPE PENCILBENCH_1D(x1,N,n),
		DATA_TYPE PENCILBENCH_1D(x2,N,n),
		DATA_TYPE PENCILBENCH_1D(y_1,N,n),
		DATA_TYPE PENCILBENCH_1D(y_2,N,n),
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n))
{
	int i, j;
#pragma pencil independent
	for (i = 0; i < n; ++i)
#pragma pencil independent reduction(+ : x1[i])
		for (j = 0; j < n; ++j)
			x1[i] += A[i][j] * y_1[j];
#pragma pencil independent
	for (i = 0; i < n; ++i)
#pragma pencil independent reduction(+ : x2[i])
		for (j = 0; j < n; ++j)
			x2[i] +=  A[j][i] * y_2[j];


}
