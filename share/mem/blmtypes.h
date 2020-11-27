/* ------------------------------
 *
 * File       : @(#) blmtypes.h
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : blm (Block Malloc; type definitions)
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Generic memory block allocation
 * 
 * ------------------------------ */

# ifndef __BLMTYPES_H
#   define __BLMTYPES_H  1

typedef struct {
		char *pg;      /* Current page */
		char *next_nd; /* next returned pointer */
		char *pg_end;  /* end of page */
} blm_malloc_tp; /* Structure for list of allocated blocks */


# endif

