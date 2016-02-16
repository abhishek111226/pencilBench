/**
 * This version is stamped on Fed 13, 2016
 *
 * Contact:
 *   Ramakrishna upadrasta <ramakrishna@iith.ac.in>
 *   Indian Institute of Technology Hyderabad
 */
/* 2mm.c: this file is part of PencilBench/C */

#ifndef _2MM_H
# define _2MM_H

/* Default to LARGE_DATASET. */

# if !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(MEDIUM_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#  define LARGE_DATASET
# endif

# if !defined(NI) && !defined(NJ) && !defined(NK) && !defined(NL)
/* Define sample dataset sizes. */
#  ifdef MINI_DATASET
#   define NI 16
#   define NJ 18
#   define NK 22
#   define NL 24
#  endif 

#  ifdef SMALL_DATASET
#   define NI 40
#   define NJ 50
#   define NK 70
#   define NL 80
#  endif 

#  ifdef MEDIUM_DATASET
#   define NI 180
#   define NJ 190
#   define NK 210
#   define NL 220
#  endif 

#  ifdef LARGE_DATASET
#   define NI 800
#   define NJ 900
#   define NK 1100
#   define NL 1200
#  endif 

#  ifdef EXTRALARGE_DATASET
#   define NI 1600
#   define NJ 1800
#   define NK 2200
#   define NL 2400
#  endif 


#endif /* !(NI NJ NK NL) */

# ifndef DATATYPE
#  define DATATYPE int
#  define DATA_PRINTF_MODIFIER "%d"
# endif

#endif /* 2MM_H  */