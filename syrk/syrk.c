/* Include pencilbench common header. */
#include <pencil.h>
#include"../utilities/include/pencilbench.h"

/* Include benchmark-specific header. */
#include "syrk.h"

/* Main computational kernel. The whole function will be timed,
   including the call and return. */
void kernel_syrk(const int ni, const int nj,
		const int alpha,
		 const int beta,
		 DATA_TYPE PENCILBENCH_2D(C,NI,NI,ni,ni),
		 DATA_TYPE PENCILBENCH_2D(A,NI,NJ,ni,nj));

/* Array initialization. */
void init_array(int ni, int nj,
		DATA_TYPE *alpha,
		DATA_TYPE *beta,
		DATA_TYPE PENCILBENCH_2D(C,NI,NI,ni,ni),
		DATA_TYPE PENCILBENCH_2D(A,NI,NJ,ni,nj))
{
  int i, j;

  *alpha = 32412;
  *beta = 2123;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      A[i][j] = ((DATA_TYPE) i*j) / ni;
  for (i = 0; i < ni; i++)
    for (j = 0; j < ni; j++)
      C[i][j] = ((DATA_TYPE) i*j) / ni;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
void print_array(int ni,
		 DATA_TYPE PENCILBENCH_2D(C,NI,NI,ni,ni))
{
  int i, j;

  PENCILBENCH_DUMP_START;
  PENCILBENCH_DUMP_BEGIN("A");
  for (i = 0; i < ni; i++)
    for (j = 0; j < ni; j++) {
	fprintf (PENCILBENCH_DUMP_TARGET, DATA_PRINTF_MODIFIER, C[i][j]);
	if ((i * ni + j) % 20 == 0) fprintf (PENCILBENCH_DUMP_TARGET, "\n");
    }
  fprintf (stderr, "\n");

   PENCILBENCH_DUMP_END("A");
   PENCILBENCH_DUMP_FINISH;
}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int ni = NI;
  int nj = NJ;

  /* Variable declaration/allocation. */
  DATA_TYPE alpha;
  DATA_TYPE beta;

  PENCILBENCH_2D_ARRAY_DECL(C,DATA_TYPE,NI,NI,ni,ni);
  PENCILBENCH_2D_ARRAY_DECL(A,DATA_TYPE,NI,NJ,ni,nj);

  /* Initialize array(s). */
  init_array (ni, nj, &alpha, &beta, C, A);

  /* Start timer. */
  pencilbench_timer_start();
  printf("\n Kernel Start");
  
  /* Run kernel. */
  kernel_syrk (ni, nj, alpha, beta, C, A);

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
  pencilbench_prevent_dce(print_array(ni, C));

  /* Be clean. */
  PENCILBENCH_FREE_ARRAY(C);
  PENCILBENCH_FREE_ARRAY(A);

  return 0;
}
