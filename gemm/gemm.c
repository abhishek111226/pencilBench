/* Include pencilbench common header. */
#include<pencil.h>
#include"../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "gemm.h"

/* Array initialization. */
void initializearray(int rowA,int colA,
		int rowB,int colB,
		int rowC,int colC, 
		DATATYPE A[rowA][colA],
		DATATYPE B[rowB][colB] ,
		DATATYPE C[rowC][colC])
{
#pragma scop
	__pencil_kill(A);
	__pencil_kill(B);
	__pencil_kill(C);
#pragma endscop
	for (int i = 0; i < rowC; ++i)
		for (int j = 0; j < colC; ++j)
			C[i][j] = ((DATATYPE) i*j) / DIV;
	for (int i = 0; i < rowA; ++i)
		for (int j = 0; j < colA; ++j)
			A[i][j] = ((DATATYPE) i*j) / DIV;
	for (int i = 0; i < rowB; ++i)
		for (int j = 0; j < colB; ++j)
			B[i][j] = ((DATATYPE) i*j) / DIV;
}

/*
 *
 *	Main computational kernel gemm. 
 *
 *	C := alpha*A*B + beta*C 
 */
void kernel_gemm(const int rowA,const int colA,
		const int rowB,const int colB,
		const int rowC,const int colC, 
		DATATYPE PENCILBENCH_2D_ARG(A,rowA,colA,ROWA,COLA),
		DATATYPE PENCILBENCH_2D_ARG(B,rowB,colB,ROWB,COLB),
		DATATYPE PENCILBENCH_2D_ARG(C,rowC,colC,ROWC,COLC))
{
	/* PENCIL Code  */
#pragma scop
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
#pragma endscop
}

int main(int argc,char**argv)
{
	/* Retrieve problem size. */
	int rowA = ROWA;
	int colA = COLA;
	int colB = COLB;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A,DATATYPE,ROWA,COLA,rowA,colA);
	PENCILBENCH_2D_ARRAY_DECL(B,DATATYPE,ROWB,COLB,ROWB,COLB);
	PENCILBENCH_2D_ARRAY_DECL(C,DATATYPE,ROWB,COLB,ROWB,COLB);

	printf("\n Problem Size :\n RowA = %d, ColA = %d, ColB : %d"
	,rowA,colA,colB);
	fflush(stdout);

	/* Initialize array(s). */
	initializearray(ROWA,COLA,ROWB,COLB,ROWC,COLC,A,B,C);

	/* Start timer. */
	pencilbench_timer_start();
	printf("\n Kernel Start");

	/* Run kernel. */	
	kernel_gemm(ROWA,COLA,ROWB,COLB,ROWC,COLC,A,B,C);	

	/* Stop and print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Free arrays. */
	PENCILBENCH_FREE_ARRAY(A)
	PENCILBENCH_FREE_ARRAY(B)
	PENCILBENCH_FREE_ARRAY(C)

	return 0;	
} 
