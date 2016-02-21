/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "atax.h"

/* Array initialization. */
static void init_array (int m, int n,
		DATA_TYPE PENCILBENCH_2D(A,M,N,m,n),
		DATA_TYPE PENCILBENCH_1D(x,N,n))
{
	int i, j;
	DATA_TYPE fn;
	fn = (DATA_TYPE)n;
	for (i = 0; i < n; i++)
		x[i] = 1 + (i / fn);
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			A[i][j] = (DATA_TYPE) ((i+j) % n) / (5*m);
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array(int n,
		DATA_TYPE PENCILBENCH_1D(y,N,n))
{
	int i;
	PENCILBENCH_DUMP_START;
	PENCILBENCH_DUMP_BEGIN("y");
	for (i = 0; i < n; i++) {
		if (i % 20 == 0) fprintf (PENCILBENCH_DUMP_TARGET, "\n");
		fprintf (PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, y[i]);
	}
	PENCILBENCH_DUMP_END("y");
	PENCILBENCH_DUMP_FINISH;
}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_atax(int m, int n,
		DATA_TYPE PENCILBENCH_2D(A,M,N,m,n),
		DATA_TYPE PENCILBENCH_1D(x,N,n),
		DATA_TYPE PENCILBENCH_1D(y,N,n),
		DATA_TYPE PENCILBENCH_1D(tmp,M,m));

int main(int argc, char** argv)
{
	/* Retrieve problem size. */
	int m = M;
	int n = N;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A, DATA_TYPE, M, N, m, n);
	PENCILBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(tmp, DATA_TYPE, M, m);

	/* Initialize array(s). */
	init_array (m, n,A, x);

	printf("\n Problem Size : \n M = %d, N = %d",m,n);
	fflush(stdout);

	printf("\n Kernel Start");
	fflush(stdout);
	/* Start timer. */
	pencilbench_timer_start();

	/* Run kernel. */
	kernel_atax (m, n,A,x,y,tmp);

	/* Stop and print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Prevent dead-code elimination. All live-out data must be printed
	   by the function call in argument. */
	pencilbench_prevent_dce(print_array(n, y));

	/* Be clean. */
	PENCILBENCH_FREE_ARRAY(A);
	PENCILBENCH_FREE_ARRAY(x);
	PENCILBENCH_FREE_ARRAY(y);
	PENCILBENCH_FREE_ARRAY(tmp);

	return 0;
}
