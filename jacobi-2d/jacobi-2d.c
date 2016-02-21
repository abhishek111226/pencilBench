/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "jacobi-2d.h"

/* Array initialization. */
static void init_array (int n,
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n),
		DATA_TYPE PENCILBENCH_2D(B,N,N,n,n))
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			A[i][j] = ((DATA_TYPE) i*(j+2) + 2) / n;
			B[i][j] = ((DATA_TYPE) i*(j+3) + 3) / n;
		}
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array(int n,
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n))

{
	int i, j;
	PENCILBENCH_DUMP_START;
	PENCILBENCH_DUMP_BEGIN("A");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) 
		{
			if ((i * n + j) % 20 == 0) fprintf(PENCILBENCH_DUMP_TARGET, "\n");
				fprintf(PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i][j]);
		}
	PENCILBENCH_DUMP_END("A");
	PENCILBENCH_DUMP_FINISH;
}

void kernel_jacobi_2d(int tsteps,
		int n,
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n),
		DATA_TYPE PENCILBENCH_2D(B,N,N,n,n));

int main(int argc, char** argv)
{
	/* Retrieve problem size. */
	int n = N;
	int tsteps = TSTEPS;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
	PENCILBENCH_2D_ARRAY_DECL(B, DATA_TYPE, N, N, n, n);

	printf("\n Problem Size : \n N = %d, TSTEPS = %d"
			,n,tsteps);
	fflush(stdout);

	/* Initialize array(s). */
	init_array (n, A, B);

	printf("\n Kernel Start");
	fflush(stdout);

	/* Start timer. */
	pencilbench_timer_start();

	/* Run kernel. */
	kernel_jacobi_2d(tsteps, n, A, B);

	/* Stop and print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Prevent dead-code elimination. All live-out data must be printed
	   by the function call in argument. */
	pencilbench_prevent_dce(print_array(n, A));

	/* Be clean. */
	PENCILBENCH_FREE_ARRAY(A);
	PENCILBENCH_FREE_ARRAY(B);

	return 0;
}
