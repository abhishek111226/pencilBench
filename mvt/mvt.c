/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "mvt.h"

/* Kernel declaration	*/
void kernel_mvt(int n,
		DATA_TYPE PENCILBENCH_1D(x1,N,n),
		DATA_TYPE PENCILBENCH_1D(x2,N,n),
		DATA_TYPE PENCILBENCH_1D(y_1,N,n),
		DATA_TYPE PENCILBENCH_1D(y_2,N,n),
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n));

/* Array initialization. */
void init_array(int n,
		DATA_TYPE x1[n],
		DATA_TYPE x2[n],
		DATA_TYPE y_1[n],
		DATA_TYPE y_2[n],
		DATA_TYPE A[n][n])
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		x1[i] = (DATA_TYPE) (i % n) / n;
		x2[i] = (DATA_TYPE) ((i + 1) % n) / n;
		y_1[i] = (DATA_TYPE) ((i + 3) % n) / n;
		y_2[i] = (DATA_TYPE) ((i + 4) % n) / n;
		for (j = 0; j < n; j++)
			A[i][j] = (DATA_TYPE) (i*j % n) / n;
	}
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array(int n,
		DATA_TYPE PENCILBENCH_1D(X,N,n))
{
	int i;
	PENCILBENCH_DUMP_START;
	PENCILBENCH_DUMP_BEGIN("X");
	for (i = 0; i < n; i++)
	{
		if (i % 20 == 0) fprintf(PENCILBENCH_DUMP_TARGET, "\n");
			fprintf(PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, X[i]);
	}
	PENCILBENCH_DUMP_END("X");
	PENCILBENCH_DUMP_FINISH;
}

int main(int argc,char**argv)
{
	/* Retrieve problem size. */
	int n = N;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
	PENCILBENCH_1D_ARRAY_DECL(x1, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(x2, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(y_1, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(y_2, DATA_TYPE, N, n);

	printf("\n Problem Size : %d",n);
	fflush(stdout);

	/* Initialize array(s). */	
	init_array (n,x1,x2,y_1,y_2,A);

	/* Start timer. */
	printf("\n Kernel Start");	
	pencilbench_timer_start();

	/* Run kernel. */
	kernel_mvt (n,x1,x2,y_1,y_2,A);

	/* Stop & print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Prevent dead-code elimination. All live-out data must be printed
	   by the function call in argument. */
	pencilbench_prevent_dce(print_array(n, x1));

	/* Free arrays. */
	PENCILBENCH_FREE_ARRAY(A);
	PENCILBENCH_FREE_ARRAY(x1);
	PENCILBENCH_FREE_ARRAY(x2);
	PENCILBENCH_FREE_ARRAY(y_1);
	PENCILBENCH_FREE_ARRAY(y_2);
	return 0; 
} 
