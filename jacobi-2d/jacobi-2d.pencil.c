#include <pencil.h>
#include "jacobi-2d.h"
#include "../utilities/include/pencilbench.h"

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_jacobi_2d(int tsteps,
			    int n,
			    DATA_TYPE PENCILBENCH_2D(A,N,N,n,n),
			    DATA_TYPE PENCILBENCH_2D(B,N,N,n,n))
{
  int t, i, j;

  for (t = 0; t < tsteps; t++)
    {
#pragma pencil independent
      for (i = 1; i < n - 1; i++)
#pragma pencil independent
	    for (j = 1; j < n - 1; j++)
	      B[i][j] = SCALAR_VAL(0.2) * (A[i][j] + A[i][j-1] + A[i][1+j] + A[1+i][j] + A[i-1][j]);
#pragma pencil independent
      for (i = 1; i < n - 1; i++)
#pragma pencil independent
	    for (j = 1; j < n - 1; j++)
	      A[i][j] = SCALAR_VAL(0.2) * (B[i][j] + B[i][j-1] + B[i][1+j] + B[1+i][j] + B[i-1][j]);
    }

}
