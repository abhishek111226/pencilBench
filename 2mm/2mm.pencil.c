#include<pencil.h>
#include"2mm.h"
#include"../utilities/include/pencilbench.h"

/*kernal funcion */
void kernel_2mm(const int ni, const int nj, const int nk, const int nl,
				const int alpha,
				const int beta,
				DATATYPE PENCILBENCH_2D_ARG(tmp, ni, nk, NI, NK),
				DATATYPE PENCILBENCH_2D_ARG(A, ni, nj, NI, NJ),
				DATATYPE PENCILBENCH_2D_ARG(B, nj, nk, NJ, NK),
				DATATYPE PENCILBENCH_2D_ARG(C, nk, nl, NK, NL),
				DATATYPE PENCILBENCH_2D_ARG(D, ni, nl, NI, NL)
				)
	/* Pencil code */
{
	int i, j, k;
	__pencil_kill(D);
	#pragma pencil independent	
	for (i = 0; i < ni; i++)
		#pragma pencil independent		
    	for (j = 0; j < nj; j++)
      	{
			#pragma pencil independent reduction(+: tmp[i][j])	    	
       		for (k = 0; k < nk; ++k)
       			tmp[i][j] += alpha * A[i][k] * B[k][j];
      	}
    #pragma pencil independent	
    for (i = 0; i < ni; i++)
    	#pragma pencil independent
    	for (j = 0; j < nl; j++)
      	{
      		D[i][j] *= beta;
      		#pragma pencil independent reduction(+: D[i][j])
      		for (k = 0; k < nj; ++k)
      			D[i][j] += tmp[i][k] * C[k][j];
      	}
}