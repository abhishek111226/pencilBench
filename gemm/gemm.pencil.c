#include<pencil.h>
#include"gemm.h"
#include"../utilities/include/pencilbench.h"

/* kernel function */
void kernel_gemm(const int rowA,const int colA,
		const int rowB,const int colB,
		const int rowC,const int colC, 
		DATATYPE PENCILBENCH_2D_ARG(A,rowA,colA,ROWA,COLA),
		DATATYPE PENCILBENCH_2D_ARG(B,rowB,colB,ROWB,COLB),
		DATATYPE PENCILBENCH_2D_ARG(C,rowC,colC,ROWC,COLC))
{
	/* PENCIL Code  */
	{	 
		__pencil_kill(C);	
#pragma pencil independent
		for (int i = 0; i < rowC; ++i)
#pragma pencil independent
			for (int j = 0; j < colC; ++j)
			{
				C[i][j] *= beta;
#pragma pencil independent reduction(+: C[i][j])
				for (int k = 0; k < rowB; ++k)
					C[i][j] += alpha * A[i][k] * B[k][j];
			}
	}
}
