/* Include pencilbench common header. */
#include<pencil.h>
#include"../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include ""

/* Array initialization. */
void initializearray(int rowA,int colA,
		int rowB,int colB,
		int rowC,int colC, 
		DATATYPE A[rowA][colA],
		DATATYPE B[rowB][colB] ,
		DATATYPE C[rowC][colC])
{
	//...
}

/*
 *
 *	Main computational kernel. 
 *
 *	C := <Equation goes here>
 */
void kernel(const int rowA,const int colA,
		const int rowB,const int colB,
		const int rowC,const int colC, 
		DATATYPE PENCILBENCH_2D_ARG(A,rowA,colA,ROWA,COLA),
		DATATYPE PENCILBENCH_2D_ARG(B,rowB,colB,ROWB,COLB),
		DATATYPE PENCILBENCH_2D_ARG(C,rowC,colC,ROWC,COLC))
{
	/* PENCIL Code  */
#pragma scop
	{
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

	printf("\n Problem Size : \n RowA = %d, ColA = %d, ColB : %d"
	,rowA,colA,colB);
	fflush(stdout);

	/* Initialize array(s). */	
	init(...)

	/* Start timer. */
	pencilbench_timer_start();
	printf("\n Kernel Start");

	/* Run kernel. */	
	kernel(.....);	

	/* Stop and print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Free arrays. */
	PENCILBENCH_FREE_ARRAY(A)

	return 0;	
} 
