/* Include pencilbench common header. */
#include<pencil.h>
#include"../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "lu.h"

/* Array initialization. */
static void init_array (int n,
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n))
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			A[i][j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
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
			fprintf (stderr, DATA_PRINTF_MODIFIER, A[i][j]);
				if ((i * n + j) % 20 == 0) fprintf (stderr, "\n");
		}
	fprintf (stderr, "\n");
	PENCILBENCH_DUMP_END("A");
	PENCILBENCH_DUMP_FINISH;
}

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_lu(int n,
		DATA_TYPE PENCILBENCH_2D(A,N,N,n,n));

int main(int argc, char** argv)
{
	/* Retrieve problem size. */
	int n = N;

	/* Variable declaration/allocation. */
	PENCILBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);

	printf("\n Problem Size : \n n= %d",n);
	fflush(stdout);	

	/* Initialize array(s). */
	init_array (n, A);

	/* Start timer. */
	pencilbench_timer_start();
	printf("\n Kernel Start");
	/* Run kernel. */
	kernel_lu(n,A);

	/* Stop and print timer. */
	printf("\n Kernel End"); 
	fflush(stdout); 	
	pencilbench_timer_stop();

	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Prevent dead-code elimination. All live-out data must be printed
	   by the function call in argument. */
	pencilbench_prevent_dce(print_array(n,A));

	/* Free arrays. */
	PENCILBENCH_FREE_ARRAY(A);

	return 0;
}
