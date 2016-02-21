/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "gemver.h"

/* FIXME: Correctness review remaining */

/* Kernel declaration	*/
void kernel_gemver(int n,
		DATA_TYPE alpha,
		DATA_TYPE beta,
		DATA_TYPE PENCILBENCH_2D_ARG(A,N,N,n,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(w,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(x,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(y,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(z,N,n));

/* Array initialization. */
void init_array (int n,
		DATA_TYPE *alpha,
		DATA_TYPE *beta,
		DATA_TYPE PENCILBENCH_2D_ARG(A,N,N,n,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v1,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(u2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(v2,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(w,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(x,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(y,N,n),
		DATA_TYPE PENCILBENCH_1D_ARG(z,N,n))
{
	int i, j;
	*alpha = 1;
	*beta = 1;
	for (i = 0; i < n; i++)
	{
		u1[i] = i;
		u2[i] = (i+1)/n/2.0;
		v1[i] = (i+1)/n/4.0;
		v2[i] = (i+1)/n/6.0;
		y[i] = (i+1)/n/8.0;
		z[i] = (i+1)/n/9.0;
		x[i] = 0.0;
		w[i] = 0.0;
		for (j = 0; j < n; j++)
			A[i][j] = ((DATA_TYPE) i*j) / n;
	}
}

/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
void print_array(int n,
		DATA_TYPE PENCILBENCH_1D_ARG(w,N,n))
{
	int i;
	for (i = 0; i < n; i++) 
	{
		fprintf (stderr, DATA_PRINTF_MODIFIER, w[i]);
		if (i % 20 == 0) fprintf (stderr, "\n");
	}
}

int main(int argc, char** argv)
{
	/* Retrieve problem size. */
	int n = N;

	/* Variable declaration/allocation. */
	DATA_TYPE alpha;
	DATA_TYPE beta;
	PENCILBENCH_2D_ARRAY_DECL(A, DATA_TYPE, N, N, n, n);
	PENCILBENCH_1D_ARRAY_DECL(u1, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(v1, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(u2, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(v2, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(w, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(x, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(y, DATA_TYPE, N, n);
	PENCILBENCH_1D_ARRAY_DECL(z, DATA_TYPE, N, n);

	/* Initialize array(s). */
 	init_array (n, &alpha, &beta,A,u1,v1,u2,v2,w,x,y,z);

	/* Start timer. */
	pencilbench_timer_start();
	printf("\n Kernel Start");

	/* Run kernel. */	
	kernel_gemver(n, alpha, beta,A,u1,v1,u2,v2,w,x,y,z);

	/* Stop and print timer. */
	pencilbench_timer_stop();
	printf("\n kernel end");
	printf("\n Execution time :");
	fflush(stdout);
	pencilbench_timer_print();
	printf("\n\n");

	/* Free arrays. */
  	PENCILBENCH_FREE_ARRAY(A);
  	PENCILBENCH_FREE_ARRAY(u1);
  	PENCILBENCH_FREE_ARRAY(v1);
  	PENCILBENCH_FREE_ARRAY(u2);
  	PENCILBENCH_FREE_ARRAY(v2);
  	PENCILBENCH_FREE_ARRAY(w);
  	PENCILBENCH_FREE_ARRAY(x);
  	PENCILBENCH_FREE_ARRAY(y);
  	PENCILBENCH_FREE_ARRAY(z);

	return 0;
}	
