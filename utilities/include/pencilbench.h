/**
 * This version is stamped on Apr. 14, 2015
 *
 * Contact:
 *   Louis-Noel Pouchet <pouchet.ohio-state.edu>
 *   Tomofumi Yuki <tomofumi.yuki.fr>
 *
 * Web address: http://pencilbench.sourceforge.net
 */
/*
 * Polybench header for instrumentation.
 *
 * Programs must be compiled with `-I utilities utilities/pencilbench.c'
 *
 * Optionally, one can define:
 *
 * -DPENCILBENCH_TIME, to report the execution time,
 *   OR (exclusive):
 * -DPENCILBENCH_PAPI, to use PAPI H/W counters (defined in pencilbench.c)
 *
 *
 * See README or utilities/pencilbench.c for additional options.
 *
 */
#ifndef PENCILBENCH_H
# define PENCILBENCH_H

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <math.h>
#include <features.h>
#include <time.h>
#include <pencil.h>

//#define PENCILBENCH_STACK_ARRAYS 1

#ifdef _OPENMP
# include <omp.h>
#endif
# ifndef PENCILBENCH_PADDING_FACTOR
/* default: */
#  define PENCILBENCH_PADDING_FACTOR 0
# endif

#undef PENCILBENCH_USE_C99_PROTO
/* C99 arrays in function prototype. By default, do not use. */
# ifdef PENCILBENCH_USE_C99_PROTO
#  define PENCILBENCH_C99_SELECT(x,y) y
# else
/* default: */
#  define PENCILBENCH_C99_SELECT(x,y) x
# endif

/* Macros to reference an array. Generic for heap and stack arrays
   (C99).  Each array dimensionality has his own macro, to be used at
   declaration or as a function argument.
   Example:
   int b[x] => PENCILBENCH_1D_ARRAY(b, x)
   int A[N][N] => PENCILBENCH_2D_ARRAY(A, N, N)
*/
# ifndef PENCILBENCH_STACK_ARRAYS
#  define PENCILBENCH_ARRAY(x) *x
#  define PENCILBENCH_FREE_ARRAY(x) free((void*)x);
#  define PENCILBENCH_DECL_VAR(x) (*x)
# else
#  define PENCILBENCH_ARRAY(x) x
#  define PENCILBENCH_FREE_ARRAY(x)
#  define PENCILBENCH_DECL_VAR(x) x
# endif

/* Macros for using arrays during declration (Not to be used while declaring 
argument to PENCIL function call). */
# define PENCILBENCH_1D(var, dim1,ddim1) var[PENCILBENCH_C99_SELECT(dim1,ddim1) \
+ PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_2D(var, dim1, dim2, ddim1, ddim2) \
var[PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR] 

# define PENCILBENCH_3D(var, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
var[PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR]
# define PENCILBENCH_4D(var, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, \
ddim4) var[PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim4,ddim4) + \
PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_5D(var, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, \
ddim4, ddim5) var[PENCILBENCH_C99_SELECT(dim1,ddim1) +   \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim4,ddim4) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim5,ddim5) + \
PENCILBENCH_PADDING_FACTOR]

/* Macros for using arrays when passed as argument. Appends PENCIL_ARRAY */
# define PENCILBENCH_1D_ARG(var, dim1,ddim1) var[PENCIL_ARRAY \
PENCILBENCH_C99_SELECT(dim1,ddim1) + PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_2D_ARG(var, dim1, dim2, ddim1, ddim2) var[PENCIL_ARRAY \
PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_3D_ARG(var, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
var[PENCIL_ARRAY PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_4D_ARG(var, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, \
ddim4) var[PENCIL_ARRAY PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim4,ddim4) + \
PENCILBENCH_PADDING_FACTOR]

# define PENCILBENCH_5D_ARG(var, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, \
ddim3, ddim4, ddim5) var[PENCIL_ARRAY PENCILBENCH_C99_SELECT(dim1,ddim1) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim2,ddim2) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim3,ddim3) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim4,ddim4) + \
PENCILBENCH_PADDING_FACTOR][PENCILBENCH_C99_SELECT(dim5,ddim5) + \
PENCILBENCH_PADDING_FACTOR]

/* Macros to allocate heap arrays.
   Example:
   PENCILBENCH_ALLOC_2d_ARRAY(N, M, double) => allocates N x M x sizeof(double)
					  and returns a pointer to the 2d array
 */
# define PENCILBENCH_ALLOC_1D_ARRAY(n1, type)	\
  (type(*)[n1 + PENCILBENCH_PADDING_FACTOR])pencilbench_alloc_data (n1 + \
PENCILBENCH_PADDING_FACTOR, sizeof(type))

# define PENCILBENCH_ALLOC_2D_ARRAY(n1, n2, type) \
  (type(*)[n1 + PENCILBENCH_PADDING_FACTOR][n2 + \
PENCILBENCH_PADDING_FACTOR])pencilbench_alloc_data ((n1 + \
PENCILBENCH_PADDING_FACTOR) * (n2 + PENCILBENCH_PADDING_FACTOR), sizeof(type)) \

# define PENCILBENCH_ALLOC_3D_ARRAY(n1, n2, n3, type)		\
  (type(*)[n1 + PENCILBENCH_PADDING_FACTOR][n2 + PENCILBENCH_PADDING_FACTOR][n3 \
+ PENCILBENCH_PADDING_FACTOR])pencilbench_alloc_data ((n1 + \
PENCILBENCH_PADDING_FACTOR) * (n2 + PENCILBENCH_PADDING_FACTOR) * (n3 + \
PENCILBENCH_PADDING_FACTOR), sizeof(type)) \

# define PENCILBENCH_ALLOC_4D_ARRAY(n1, n2, n3, n4, type) \
  (type(*)[n1 + PENCILBENCH_PADDING_FACTOR][n2 + PENCILBENCH_PADDING_FACTOR][n3 \
+ PENCILBENCH_PADDING_FACTOR][n4 + \
PENCILBENCH_PADDING_FACTOR])pencilbench_alloc_data ((n1 + \
PENCILBENCH_PADDING_FACTOR) * (n2 + PENCILBENCH_PADDING_FACTOR) * (n3 + \
PENCILBENCH_PADDING_FACTOR) * (n4 + PENCILBENCH_PADDING_FACTOR), sizeof(type)) \

# define PENCILBENCH_ALLOC_5D_ARRAY(n1, n2, n3, n4, n5, type)		\
  (type(*)[n1 + PENCILBENCH_PADDING_FACTOR][n2 + PENCILBENCH_PADDING_FACTOR][n3 \
+ PENCILBENCH_PADDING_FACTOR][n4 + PENCILBENCH_PADDING_FACTOR][n5 + \
PENCILBENCH_PADDING_FACTOR])pencilbench_alloc_data ((n1 + \
PENCILBENCH_PADDING_FACTOR) * (n2 + PENCILBENCH_PADDING_FACTOR) * (n3 + \
PENCILBENCH_PADDING_FACTOR) * (n4 + PENCILBENCH_PADDING_FACTOR) * (n5 + \
PENCILBENCH_PADDING_FACTOR), sizeof(type))

/* Macros for array declaration. */
# ifndef PENCILBENCH_STACK_ARRAYS
#  define PENCILBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1)		\
  type (PENCILBENCH_DECL_VAR(var)); \
  var = pencilbench_alloc_data (PENCILBENCH_C99_SELECT(dim1, \
ddim1),sizeof(PENCILBENCH_DECL_VAR(var)));

#  define PENCILBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2) \
  type PENCILBENCH_1D(PENCILBENCH_DECL_VAR(var), dim2, ddim2); \
  var = pencilbench_alloc_data (PENCILBENCH_C99_SELECT(dim1, \
ddim1),sizeof(PENCILBENCH_DECL_VAR(var)));

#  define PENCILBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2, \
ddim3) \
type PENCILBENCH_2D(PENCILBENCH_DECL_VAR(var), dim2, dim3, ddim2, ddim3); \
  var = pencilbench_alloc_data (PENCILBENCH_C99_SELECT(dim1, \
ddim1),sizeof(PENCILBENCH_DECL_VAR(var))); \

#  define PENCILBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, \
ddim2, ddim3, ddim4) \
  type PENCILBENCH_3D(PENCILBENCH_DECL_VAR(var), dim2, dim3, dim4, ddim2, \
ddim3, ddim4); \
var = pencilbench_alloc_data (PENCILBENCH_C99_SELECT(dim1, \
ddim1),sizeof(PENCILBENCH_DECL_VAR(var)));

#  define PENCILBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, \
ddim1, ddim2, ddim3, ddim4, ddim5) \
  type PENCILBENCH_4D(PENCILBENCH_DECL_VAR(var), dim2, dim3, dim4, dim5, ddim2, \
ddim3, ddim4, ddim5); \
  var = pencilbench_alloc_data (PENCILBENCH_C99_SELECT(dim1, \
ddim1),sizeof(PENCILBENCH_DECL_VAR(var)));

# else
#  define PENCILBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1) \
  static type PENCILBENCH_1D(PENCILBENCH_DECL_VAR(var), dim1, ddim1);

#  define PENCILBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2) \
  static type PENCILBENCH_2D(PENCILBENCH_DECL_VAR(var), dim1, dim2, ddim1, \
ddim2);

#  define PENCILBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2,\
ddim3) \
  static type PENCILBENCH_3D(PENCILBENCH_DECL_VAR(var), dim1, dim2, dim3, \
ddim1, ddim2, ddim3);

#  define PENCILBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, \
ddim2, ddim3, ddim4) \
  static type PENCILBENCH_4D(PENCILBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, \
ddim1, ddim2, ddim3, ddim4);
#  define PENCILBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, \
ddim1, ddim2, ddim3, ddim4, ddim5) \
  static type PENCILBENCH_5D(PENCILBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, \
dim5, ddim1, ddim2, ddim3, ddim4, ddim5);

# endif

/* Not found in PENCIL headers */
#define PENCIL_ARRAY static const restrict

/* Dead-code elimination macros. Use argc/argv for the run-time check. */
# ifndef PENCILBENCH_DUMP_ARRAYS
#  define PENCILBENCH_DCE_ONLY_CODE    if (argc > 42 && ! strcmp(argv[0], ""))
# else
#  define PENCILBENCH_DCE_ONLY_CODE
# endif

#define PENCILBENCH_DUMP_TARGET stderr
#define PENCILBENCH_DUMP_START    fprintf(PENCILBENCH_DUMP_TARGET, "==BEGIN DUMP_ARRAYS==\n")
#define PENCILBENCH_DUMP_FINISH   fprintf(PENCILBENCH_DUMP_TARGET, "==END   DUMP_ARRAYS==\n")
#define PENCILBENCH_DUMP_BEGIN(s) fprintf(PENCILBENCH_DUMP_TARGET, "begin dump: %s", s)
#define PENCILBENCH_DUMP_END(s)   fprintf(PENCILBENCH_DUMP_TARGET, "\nend   dump: %s\n", s)

# define pencilbench_prevent_dce(func)    \
  PENCILBENCH_DCE_ONLY_CODE     \
  func

/* Performance-related instrumentation. See pencilbench.c */
# define pencilbench_start_instruments
# define pencilbench_stop_instruments
# define pencilbench_print_instruments

/* Timing support. */
# if defined(PENCILBENCH_TIME) || defined(PENCILBENCH_GFLOPS)
#  undef pencilbench_start_instruments
#  undef pencilbench_stop_instruments
#  undef pencilbench_print_instruments
#  define pencilbench_start_instruments pencilbench_timer_start();
#  define pencilbench_stop_instruments pencilbench_timer_stop();
#  define pencilbench_print_instruments pencilbench_timer_print();
extern double pencilbench_program_total_flops;
extern void pencilbench_timer_start();
extern void pencilbench_timer_stop();
extern void pencilbench_timer_print();
# endif

/* Function declaration. */
# ifdef PENCILBENCH_TIME
extern void pencilbench_timer_start();
extern void pencilbench_timer_stop();
extern void pencilbench_timer_print();
# endif

/* Function prototypes. */
extern void* pencilbench_alloc_data(unsigned long long int n, int elt_size);

#endif /* !PENCILBENCH_H */