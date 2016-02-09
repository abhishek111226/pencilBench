/**
 * This version is stamped on Apr. 14, 2015
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://pencilbench.sourceforge.net
 */
/* jacobi-1d.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* Include pencilbench common header. */
#include "../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "jacobi-1d.h"


/* Array initialization. */
static
void init_array (int n,
		 DATA_TYPE PENCILBENCH_1D(A,N,n),
		 DATA_TYPE PENCILBENCH_1D(B,N,n))
{
  int i;

  for (i = 0; i < n; i++)
      {
	A[i] = ((DATA_TYPE) i+ 2) / n;
	B[i] = ((DATA_TYPE) i+ 3) / n;
      }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n,
		 DATA_TYPE PENCILBENCH_1D(A,N,n))

{
  int i;

  PENCILBENCH_DUMP_START;
  PENCILBENCH_DUMP_BEGIN("A");
  for (i = 0; i < n; i++)
    {
      if (i % 20 == 0) fprintf(PENCILBENCH_DUMP_TARGET, "\n");
      fprintf(PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, A[i]);
    }
  PENCILBENCH_DUMP_END("A");
  PENCILBENCH_DUMP_FINISH;
}

void kernel_jacobi_1d(int tsteps,
          int n,
          DATA_TYPE PENCILBENCH_1D(A,N,n),
          DATA_TYPE PENCILBENCH_1D(B,N,n));

int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;
  int tsteps = TSTEPS;

  /* Variable declaration/allocation. */
  PENCILBENCH_1D_ARRAY_DECL(A, DATA_TYPE, N, n);
  PENCILBENCH_1D_ARRAY_DECL(B, DATA_TYPE, N, n);

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
  kernel_jacobi_1d(tsteps, n, A, B);

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
