/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "2mm.h"

void kernel_2mm(const int ni, const int nj, const int nk, const int nl, 
		const int alpha, const int beta, 
		DATA_TYPE PENCILBENCH_2D_ARG(tmp, ni,nk, NI, NK),
		DATA_TYPE PENCILBENCH_2D_ARG(A, ni, nj, NI, NJ), 
		DATA_TYPE PENCILBENCH_2D_ARG(B,nj, nk, NJ, NK), 
		DATA_TYPE PENCILBENCH_2D_ARG(C, nk, nl,NK, NL), 
		DATA_TYPE PENCILBENCH_2D_ARG(D, ni, nl, NI, NL));

/* Array initialization. */
void initializearray(int ni, int nj, int nk, int nl, 
		DATA_TYPE *alpha, DATA_TYPE *beta, 
		DATA_TYPE PENCILBENCH_2D_ARG(A, ni, nj, NI, NJ), 
		DATA_TYPE PENCILBENCH_2D_ARG(B, nj, nk, NJ, NK), 
		DATA_TYPE PENCILBENCH_2D_ARG(C, nk, nl,NK, NL), 
		DATA_TYPE PENCILBENCH_2D_ARG(D, ni, nl, NI, NL)) 
{ 
	int i, j; 
	*alpha =1; *beta = 1; 
	for (i = 0; i < ni; i++) 
		for (j = 0; j < nj; j++) 
			A[i][j] =(DATA_TYPE) (i*j % ni) / ni;

	for (i = 0; i < nj; i++) 
		for (j = 0; j < nk; j++) 
		{ 
			B[i][j] =(DATA_TYPE) (i*(j+1) % nj) / nj; 
		}  	
	for (i = 0; i < nk; i++)
		for (j = 0; j <nl; j++) 
		{ 
			C[i][j] = (DATA_TYPE) (i*(j+3) % nl) / nl; 
		}
	for (i = 0; i < ni; i++)
		for (j = 0; j < nl; j++) 
			D[i][j] = (DATA_TYPE) (i*(j+2) % nk) / nk; 
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */ 
void print_array(int ni,int nl, 
		DATA_TYPE PENCILBENCH_2D(D,NI,NL,ni,nl)) 
{ 
	int i, j;
	PENCILBENCH_DUMP_START; 
	PENCILBENCH_DUMP_BEGIN("D"); 
	for (i = 0;i < ni; i++)
		for (j = 0; j < nl; j++) 
		{ 
			if ((i * nl +j) % 20 == 0)
				fprintf(PENCILBENCH_DUMP_TARGET,"\n"); 
			fprintf(PENCILBENCH_DUMP_TARGET,DATA_PRINTF_MODIFIER, D[i][j]); 
		} 
	PENCILBENCH_DUMP_END("D");
	PENCILBENCH_DUMP_FINISH; 
}

int main(int argc, char** argv) 
{
	/* Retrive problem size.*/
	int ni = NI; 
	int nj = NJ; 
	int nk = NK; 
	int nl = NL;

	DATA_TYPE alpha; 
	DATA_TYPE beta;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A,DATA_TYPE,NI,NJ,ni,nj);
	PENCILBENCH_2D_ARRAY_DECL(B,DATA_TYPE,NJ,NK,nj,nk);
	PENCILBENCH_2D_ARRAY_DECL(C,DATA_TYPE,NK,NL,nk,nl);
	PENCILBENCH_2D_ARRAY_DECL(D,DATA_TYPE,NI,NL,ni,nl);
	PENCILBENCH_2D_ARRAY_DECL(tmp,DATA_TYPE,NI,NK,ni,nk);

	printf("\n Problem Size : \n RowA = %d, RowB = %d, \
	RowC : %d, ColC :%d",ni, nj, nk, nl); 
	fflush(stdout);

	/* Initialize array(s).*/

	initializearray(ni, nj, nk, nl, &alpha, &beta, A, B, C, D);

	/* start timer */

	pencilbench_timer_start(); 
	printf("\n Kernel Start");

	/* Run kernal */
	kernel_2mm(ni, nj, nk, nl, alpha, beta, tmp, A, B, C, D);

	pencilbench_timer_stop(); 
	printf("\n kernel end"); 
	printf("\n Execution time :"); 
	fflush(stdout);

	/* Stop and print timer.*/
	pencilbench_timer_print(); 
	printf("\n\n");

	/* Prevent dead-code elimination. All live-out data must 
	be printed by the function call in argument. */
	pencilbench_prevent_dce(print_array(ni,nl, D));

	/* Free arrays */
	PENCILBENCH_FREE_ARRAY(A) 
	PENCILBENCH_FREE_ARRAY(B)
	PENCILBENCH_FREE_ARRAY(C) 
	PENCILBENCH_FREE_ARRAY(D) 
	PENCILBENCH_FREE_ARRAY(tmp)

	return 0;	
} 

