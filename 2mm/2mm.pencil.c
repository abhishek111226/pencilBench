#include<pencil.h> 
#include"2mm.h" 
#include"../utilities/include/pencilbench.h"

/*kernal funcion */
void kernel_2mm(const int ni, const int nj, const int nk, const int nl, const 
		int alpha, const int beta, 
		DATA_TYPE PENCILBENCH_2D_ARG(tmp, ni, nk, NI, NK),
		DATA_TYPE PENCILBENCH_2D_ARG(A, ni, nj, NI, NJ), 
		DATA_TYPE PENCILBENCH_2D_ARG(B, nj, nk, NJ, NK), 
		DATA_TYPE PENCILBENCH_2D_ARG(C, nk, nl,NK, NL), 
		DATA_TYPE PENCILBENCH_2D_ARG(D, ni, nl, NI, NL))
/* Pencil code */
{ 
	int i, j, k;
#pragma pencil independent 
	for (i = 0; i < ni; i++) 
#pragma pencil independent 
		for (j = 0; j < nj; j++) 
		{ 
#pragma pencil independent (+ :tmp[i][j]) 
			for (k = 0; k < nk; ++k) 
				tmp[i][j] += alpha * A[i][k] * B[k][j]; 
		}
#pragma pencil independent 
	for (i = 0; i < ni; i++) 
#pragma pencil independent 
		for (j = 0; j < nk; j++) 
		{ 
#pragma pencil independent (+ : D[i][j])
			for (k = 0; k < nl; ++k) 
				D[i][j] += alpha * tmp[i][k] * C[k][j]; 
		} 
}
