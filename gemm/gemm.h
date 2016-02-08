#define ROWB COLA
#define ROWC ROWA
#define COLC COLB
#define DIV 1
#define alpha 1
#define beta 1
#ifndef GEMM_H
# define GEMM_H

/* Default to STANDARD_DATASET. */
# if !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#  define STANDARD_DATASET
# endif

/* Do not define anything if the user manually defines the size. */
# if !defined(COLA) && !defined(ROWA) && !defined(COLB)
/* Define the possible dataset sizes. */
#  ifdef MINI_DATASET
#   define COLA 32
#   define ROWA 32
#   define COLB 32
#  endif

#  ifdef SMALL_DATASET
#   define COLA 128
#   define ROWA 128
#   define COLB 128
#  endif

#  ifdef STANDARD_DATASET /* Default if unspecified. */
#   define COLA 1024
#   define ROWA 1024
#   define COLB 1024
#  endif

#  ifdef LARGE_DATASET
#   define COLA 2000
#   define ROWA 2000
#   define COLB 2000
#  endif

#  ifdef EXTRALARGE_DATASET
#   define COLA 4000
#   define ROWA 4000
#   define COLB 4000
#  endif
# endif /* !N */

/*# define _PB_NI POLYBENCH_LOOP_BOUND(NI,ni)
# define _PB_NJ POLYBENCH_LOOP_BOUND(NJ,nj)
# define _PB_NK POLYBENCH_LOOP_BOUND(NK,nk)
*/

# ifndef DATATYPE
#  define DATATYPE int
#  define DATA_PRINTF_MODIFIER "%d"
# endif


#endif /* !GEMM */
