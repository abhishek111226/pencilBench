#include <pencil.h>
#include "syrk.h"
#include"../utilities/include/pencilbench.h"

void kernel_syrk(const int ni, const int nj,
		 const int alpha,
		 const int beta,
		 DATA_TYPE PENCILBENCH_2D(C,NI,NI,ni,ni),
		 DATA_TYPE PENCILBENCH_2D(A,NI,NJ,ni,nj))
{
  int i, j, k;

  /*  C := alpha*A*A' + beta*C */

#pragma pencil independent 
  for (i = 0; i < ni; i++)
#pragma pencil independent 
    for (j = 0; j < ni; j++)
      C[i][j] = C[i][j] * beta;

#pragma pencil independent 
  for (i = 0; i < ni; i++)
#pragma pencil independent 
    for (j = 0; j < ni; j++)
    {
#pragma pencil independent reduction(+ :C[i][j])
      for (k = 0; k < nj; k++)
	  C[i][j] += alpha * A[i][k] * A[j][k];
    }
}
