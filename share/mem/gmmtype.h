/* ------------------------------
 *
 * File       : @(#) gmmtype.h
 * Project    : Lbam
 * Date       : Oct-91
 * Module     : Gmm
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Graph memory manager type definitions.
 *
 * ------------------------------ */


# ifndef __GMMTYPE_H_
#  define __GMMTYPE_H_ 1


typedef struct {
   /* list vars */
   list_list_tp data; /* page list */
   list_elem_ptr pg;  /* current page */
   /* current pg. vars */
   char *next_nd;     /* next returned pointer */
   size_t nodes;      /* how many nodes left */
   char *first;       /* pointer to the first node */
   /* size vars */
   size_t nd_size;    /* size of a node + ptr. to virtual addr.*/
   size_t nds_pg;     /* how many nodes per page */
   size_t first_off;  /* offset for first node  */
} gmm_list_tp;

typedef void (*gmm_cf_tp)();

#endif


