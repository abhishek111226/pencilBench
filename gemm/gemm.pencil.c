#include<pencil.h>
#include"gemm.h"
#include"../utilities/include/pencilbench.h"
/*
 *	Main computational kernel. 
 *
 *	C = beta*C + alpha*A*B 
 */
void kernel_gemm(const int rowA,const int colA,
		const int rowB,const int colB,
		const int rowC,const int colC, 
		DATA_TYPE PENCILBENCH_2D_ARG(A,rowA,colA,ROWA,COLA),
		DATA_TYPE PENCILBENCH_2D_ARG(B,rowB,colB,ROWB,COLB),
		DATA_TYPE PENCILBENCH_2D_ARG(C,rowC,colC,ROWC,COLC))
{

	int i, j, k;

	/* C := alpha*A*B + beta*C */
#pragma pencil independent
	for (i = 0; i < rowA; i++)
#pragma pencil independent
		for (j = 0; j < colA; j++)
		{
			C[i][j] *= beta;
#pragma pencil independent (+ : C[i][j])
			for (k = 0; k < colB; ++k)
				C[i][j] += alpha * A[i][k] * B[k][j];
		}

}
