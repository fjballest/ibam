/* ------------------------------
 *
 * File       : @(#) vadd.h
 * Project    : Lbam
 * Date       : Oct/91
 * Module     : vadd ( Virtual address manager ) 
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Provides virtual addressing through the graph memory
 *              Manager
 * 
 * ------------------------------ */

# ifndef __VADD_H
#  define __VADD_H 1

/* ========== DEPENDENCIES ========== */

# include "flags.h"

# include "../stck.h"
# include "../list.h"

/* ========== END OF DEPENDENCIES ========== */


/* ========== TYPE DEFINITIONS ========== */

typedef void *vadd_t;
typedef void *radd_t;
typedef struct {
  list_list_tp vadd_pgs;       /* list of pages */
  stck_dstackType vadd_free;   /* free-list     */
  list_elem_ptr vadd_pg;       /* current page  */
  vadd_t *vadd_next;           /* next returned entry */
  vadd_t *vadd_aux;            /* Auxiliar var. */
  unsigned vadd_left;          /* left vadds in page */
  unsigned vapp;               /* `v'irtual `a'ddrs. `p'er `p'age */  
} vadd_dt_tp;

extern vadd_dt_tp v_d;

/* ========== END OF TYPE DEFINITIONS ========== */



/* ========== PROTOTYPES ========== */

int vadd_init();
/* ------------------------------
 * Returns    : non-zero if error.
 * Use        : gmmf_*_addr_ok ( flags );
 * Global     : v_d. 
 * Parameters :
 * Comments   : Sets gmmf_*add_ok to non-zero ( only it's bit ).
 *
 * ------------------------------ */

/* vadd_t get_vadd(void);
 * ------------------------------
 * MACRO !!
 * Returns    : A new virtual address;
 * Global     : v_d.
 * Comments   : maps the returned address to a.
 *
 * ------------------------------ */

/* vadd_t vadd_map(vadd_t v,radd_t r);
 * ------------------------------
 * MACRO !!
 * Global     : v_d.
 * Comments   : maps the virtual address 'v' to the 
 *              real address 'r'.
 *
 * ------------------------------ */

/* void free_vadd(vadd_t a);
 * ------------------------------
 * MACRO !!
 * Global     : v_d.
 * Comments   : unmaps the virtual address  a.
 *
 * ------------------------------ */

/* void swap_vadd(vadd_t v1, vaddt_v2);
 * ------------------------------
 * MACRO !!
 * Global     : v_d.
 * Comments   : Swaps the phisical directions associated with
 *              the given virtual directions..
 *
 * ------------------------------ */


vadd_t vadd_get_vadd(/* void */);
/* ------------------------------
 * Returns    : virtual address; NULL if error.
 * Parameters :
 * Comments   : This function is called when there is no space for
 *              a new virtual address in current page. Then a new
 *              page is allocated, the global variables are reinitialized
 *              and the virtual address returned.
 *              We assume that there is no vadd at free list and no
 *              free space at current page.
 *
 * ------------------------------ */


/* radd_t va2ra( vadd_t a ); 
 * ------------------------------
 * Returns    : The real address for virtual a
 * Use        : (mytype)(va2ra(p)).foo = ....
 *              gnat = (mytype)(va2ra(p)).xxx ...
 * Parameters : a must be a mapped virtual address.
 * Comments   : This macro gives you access to the memory refered by a,
 *              You should use "va2ra(x)" in place of "x" whenever you what
 *              to access data stored via a.
 *
 * ------------------------------ */


void vadd_clear();
/* ------------------------------
 * Global     : v_d
 * Comments   : Frees the entire virtual address space.
 *
 * ------------------------------ */



/* ========== END OF PROTOTYPES ========== */


/* ========== MACRO DEFINITIONS ========== */

extern vadd_t *vadd_aux;

# define get_vadd()                      \
   ( v_d.vadd_free )                     \
     ? ( stck_dtopp(v_d.vadd_free) )     \
     : (( v_d.vadd_left--)               \
          ?( (vadd_t)v_d.vadd_next++ )   \
          : vadd_get_vadd()              \
        )

# define vadd_map(va,ra)  \
     (((*(void **)(va))=((void **)(ra)+1)),(*(void **)(ra)=(va)))

# define free_vadd(a)             \
     stck_dpush(v_d.vadd_free,a)

# define swap_vadd(v1,v2)   \
     vadd_aux = *(v1);      \
     *(v1) = *(v2);         \
     *(v2) = vadd_aux


# define va2ra(p) (*(p))

/* ========== END OF MACRO DEFINITIONS ========== */



# endif


