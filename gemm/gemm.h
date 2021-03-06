#ifndef TEMPLATE_H
# define TEMPLATE_H
#define DIV 1
#define alpha 1
#define beta 1
#define ROWB COLA
#define ROWC ROWA
#define COLC COLB
/* Default to STANDARD_DATASET. */
# if !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#  define STANDARD_DATASET
# endif

/* Do not define anything if the user manually defines the size. */
# if !defined(ROWA) && !defined(COLA) && !defined(COLB)
/* Define the possible dataset sizes. */
#  ifdef MINI_DATASET
#   define ROWA 32
#   define COLA 32
#   define COLB 32
#  endif

#  ifdef SMALL_DATASET
#   define ROWA 128
#   define COLA 128
#   define COLB 128
#  endif

#  ifdef STANDARD_DATASET /* Default if unspecified. */
#   define ROWA 1024
#   define COLA 1024
#   define COLB 1024
#  endif

#  ifdef LARGE_DATASET
#   define ROWA 2000
#   define COLA 2000
#   define COLB 2000
#  endif

#  ifdef EXTRALARGE_DATASET
#   define ROWA 4000
#   define COLA 4000
#   define COLB 4000
#  endif
# endif /* !N */

/* Default data type */
# if !defined(DATA_TYPE_IS_INT) && !defined(DATA_TYPE_IS_FLOAT) && !defined(DATA_TYPE_IS_DOUBLE)
#  define DATA_TYPE_IS_DOUBLE
# endif

#ifdef DATA_TYPE_IS_INT
#  define DATA_TYPE int
#  define DATA_PRINTF_MODIFIER "%d "
#endif 

#ifdef DATA_TYPE_IS_FLOAT
#  define DATA_TYPE float
#  define DATA_PRINTF_MODIFIER "%0.2f "
#  define SCALAR_VAL(x) x##f
#  define SQRT_FUN(x) sqrtf(x)
#  define EXP_FUN(x) expf(x)
#  define POW_FUN(x,y) powf(x,y)
# endif

#ifdef DATA_TYPE_IS_DOUBLE
#  define DATA_TYPE double
#  define DATA_PRINTF_MODIFIER "%0.2lf "
#  define SCALAR_VAL(x) x
#  define SQRT_FUN(x) sqrt(x)
#  define EXP_FUN(x) exp(x)
#  define POW_FUN(x,y) pow(x,y)
# endif


#endif /* !GEMM */
