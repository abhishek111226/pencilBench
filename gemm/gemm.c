/* Include pencilbench common header. */
#include<pencil.h>
#include"../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "gemm.h"

void kernel_gemm(const int rowA,const int colA,
		const int rowB,const int colB,
		const int rowC,const int colC, 
		DATA_TYPE PENCILBENCH_2D_ARG(A,rowA,colA,ROWA,COLA),
		DATA_TYPE PENCILBENCH_2D_ARG(B,rowB,colB,ROWB,COLB),
		DATA_TYPE PENCILBENCH_2D_ARG(C,rowC,colC,ROWC,COLC));

/* Array initialization. */
void initializearray(int rowA,int colA,
		int rowB,int colB,
		int rowC,int colC, 
		DATA_TYPE A[rowA][colA],
		DATA_TYPE B[rowB][colB] ,
		DATA_TYPE C[rowC][colC])
{
	for (int i = 0; i < rowC; ++i)
		for (int j = 0; j < colC; ++j)
			C[i][j] = ((DATA_TYPE) i*j) / rowA;
	for (int i = 0; i < rowA; ++i)
		for (int j = 0; j < colA; ++j)
			A[i][j] = ((DATA_TYPE) i*j) / rowA;
	for (int i = 0; i < rowB; ++i)
		for (int j = 0; j < colB; ++j)
			B[i][j] = ((DATA_TYPE) i*j) / rowA;
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
void print_array(int rowC,int colC,
		DATA_TYPE PENCILBENCH_2D(C,ROWC,COLC,rowC,colC))
{
	int i, j;
	printf("Here");
	PENCILBENCH_DUMP_START;
	PENCILBENCH_DUMP_BEGIN("C");
	for (i = 0; i < rowC; i++)
		for (j = 0; j < colC; j++) 
		{
			if ((i * colC + j) % 20 == 0) fprintf(PENCILBENCH_DUMP_TARGET, "\n");
				fprintf(PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
		}
	PENCILBENCH_DUMP_END("C");
	PENCILBENCH_DUMP_FINISH;
}

int main(int argc,char**argv)
{
	/* Retrieve problem size. */
	int rowA = ROWA;
	int colA = COLA;
	int colB = COLB;
	int rowB = ROWB;
	int rowC = ROWC;
	int colC = COLC; 

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A,DATA_TYPE,ROWA,COLA,rowA,colA);
	PENCILBENCH_2D_ARRAY_DECL(B,DATA_TYPE,ROWB,COLB,rowB,colB);
	PENCILBENCH_2D_ARRAY_DECL(C,DATA_TYPE,ROWC,COLC,rowC,colC);

	printf("\n Problem Size : \n RowA = %d, ColA = %d, ColB : %d"
			,rowA,colA,colB);
	fflush(stdout);

	/* Initialize array(s). */	
	initializearray(rowA,colA,rowB,colB,rowC,colC,A,B,C);

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

	pencilbench_prevent_dce(print_array(rowC,colC,C));

	/* Free arrays. */
	PENCILBENCH_FREE_ARRAY(A)
	PENCILBENCH_FREE_ARRAY(B)
	PENCILBENCH_FREE_ARRAY(C)
		
	return 0;	
} 
