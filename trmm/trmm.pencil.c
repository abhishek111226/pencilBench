#include <pencil.h>
#include "trmm.h"
#include"../utilities/include/pencilbench.h"

void kernel_trmm(const int ni,
		 const int alpha,
		 DATA_TYPE PENCILBENCH_2D(A,NI,NI,ni,ni),
		 DATA_TYPE PENCILBENCH_2D(B,NI,NI,ni,ni))
{
  int i, j, k;

  /*  B := alpha*A'*B, A triangular */
#pragma pencil independent 
  for (i = 1; i < ni; i++)
#pragma pencil independent 
    for (j = 0; j < ni; j++)
#pragma pencil independent reduction(+ :B[i][j])
      for (k = 0; k < i; k++)
        B[i][j] += alpha * A[i][k] * B[j][k];

}

