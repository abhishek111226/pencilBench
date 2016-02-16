/**
 * This version is stamped on Fed 13, 2016
 *
 * Contact:
 *   Ramakrishna upadrasta <ramakrishna@iith.ac.in>
 *   Indian Institute of Technology Hyderabad
 */
/* 2mm.c: this file is part of PencilBench/C */

/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "2mm.h"

void kernel_2mm(const int ni, const int nj, const int nk, const int nl,
				const int alpha,
				const int beta,
				DATATYPE PENCILBENCH_2D_ARG(tmp, ni, nk, NI, NK),
				DATATYPE PENCILBENCH_2D_ARG(A, ni, nj, NI, NJ),
				DATATYPE PENCILBENCH_2D_ARG(B, nj, nk, NJ, NK),
				DATATYPE PENCILBENCH_2D_ARG(C, nk, nl, NK, NL),
				DATATYPE PENCILBENCH_2D_ARG(D, ni, nl, NI, NL)
				);

/* Array initialization. */

void initializearray(int ni, int nj, int nk, int nl,
 		DATATYPE *alpha,
 	  	DATATYPE *beta,
 	  	DATATYPE A[ni][nj],
 	  	DATATYPE B[nj][nk],
 	  	DATATYPE C[nk][nl],
 	  	DATATYPE D[ni][nl])
{
	int i, j;
	*alpha = 1.5;
	*beta = 1.2;
	for (i = 0; i < ni; i++)
    	for (j = 0; j < nk; j++)
      		A[i][j] = (DATATYPE) (i*j % ni) / ni;
  	for (i = 0; i < nk; i++)
    	for (j = 0; j < nj; j++)
      		B[i][j] = (DATATYPE) (i*(j+1) % nj) / nj;
  	for (i = 0; i < nj; i++)
    	for (j = 0; j < nl; j++)
      		C[i][j] = (DATATYPE) (i*(j+3) % nl) / nl;
  	for (i = 0; i < ni; i++)
    	for (j = 0; j < nl; j++)
      		D[i][j] = (DATATYPE) (i*(j+2) % nk) / nk;
}
int main(int argc, char** argv)
{

	/* Retrive problem size. */
	int ni = NI;
	int nj = NJ;
	int nk = NK;
	int nl = NL;


	DATATYPE alpha;
	DATATYPE beta;

	/* Variable declaration/allocation. */
	
	PENCILBENCH_2D_ARRAY_DECL(A,DATATYPE,NI,NJ,ni,nj);
	PENCILBENCH_2D_ARRAY_DECL(B,DATATYPE,NJ,NK,nj,nk);
	PENCILBENCH_2D_ARRAY_DECL(tmp,DATATYPE,NI,NK,ni,nk);
	PENCILBENCH_2D_ARRAY_DECL(C,DATATYPE,NK,NL,nk,nl);
	PENCILBENCH_2D_ARRAY_DECL(D,DATATYPE,NI,NL,ni,nl);

	printf("\n Problem Size : \n RowA = %d, RowB = %d, RowC : %d, ColC : %d",ni, nj, nk, nl);
	fflush(stdout);

	/* Initialize array(s). */

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

	/* Stop and print timer. */

	pencilbench_timer_print();
	printf("\n\n");

	/* Free arrays */

	/*PENCILBENCH_FREE_ARRAY(A)
	PENCILBENCH_FREE_ARRAY(B)
	PENCILBENCH_FREE_ARRAY(C)
	PENCILBENCH_FREE_ARRAY(D)
	//PENCILBENCH_FREE_ARRAY(tmp)
*/

	return 0;	
} 

