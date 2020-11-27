/* ------------------------------
 *
 * File       : @(#) vadd.c
 * Project    : Lbam
 * Date       : Oct/91
 * Module     : vadd ( Virtual address manager; implementation ) 
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Provides virtual addressing through the Graph Memory
 *              Manager
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include "../share.h"
# include "../err.h"
# include "../list.h"
# include "../stck.h"
# include "pgpool.h"
# include "flags.h"

/* ========== END OF DEPENDENCIES ========== */


/* ========== DEBUGGING MACRO DEFINITIONS ========== */
# ifdef DEBUG
#   define DEBUG_Init_Func(func) \
       printf("VADD: Init Function: %s\n",func)

#   define DEBUG_End_Func(func) \
       printf("VADD: End Function: %s\n\n",func)

# else
#   define DEBUG_Init_Func(func)
#   define DEBUG_End_Func(func)

# endif
/* ========== END OF DEBUGGING MACRO DEFINITIONS ========== */


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

/* ========== END OF TYPE DEFINITIONS ========== */



/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

vadd_dt_tp v_d;
void (*vadd_exc_f)(); /* vadd exception function: called when no more pages*/ 
vadd_t *vadd_aux;

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */


void vadd_set_exc_f( f )
   void (*f)();
/* ------------------------------
 * Global     : vadd_exc_f;
 * Parameters : f is a function that is guaranteed to be called when no
 *              vaddresses are available.
 * Comments   :
 *
 * ------------------------------ */
{
   vadd_exc_f = f;
} /* vadd_set_exc_f */



void vadd_clear()
/* ------------------------------
 * Global     : v_d
 * Comments   : Frees the entire virtual address space.
 *
 * ------------------------------ */
{
   DEBUG_Init_Func("Clear");

   List_Join(pool,v_d.vadd_pgs);
   vadd_init();

   DEBUG_End_Func("Clear");
}/*vadd_clear*/

int vadd_init()
/* ------------------------------
 * Returns    : non-zero if error.
 * Use        : gmmf_*_addr_ok ( flags );
 * Global     : every one  in vadd module. 
 * Parameters :
 * Comments   : Sets gmmf_*add_ok to non-zero ( only it's bit ).
 *
 * ------------------------------ */
{
  DEBUG_Init_Func("vadd_init");

  v_d.vadd_pgs = v_d.vadd_free = v_d.vadd_pg  
             = v_d.vadd_next =(vadd_t)(v_d.vadd_left = 0);
  v_d.vapp = (size_t)(Page_Size - 2 * sizeof(list_elem_ptr) ) /
             sizeof( vadd_t );

  DEBUG_End_Func("vadd_init");

}/*vadd_init*/



vadd_t vadd_get_vadd()
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
{
   pg_t pg = Pg_Get_Page();

   DEBUG_Init_Func("Get_vadd");

   if( pg == (pg_t)-1 ){  /* no pgs. aval. */
      (*vadd_exc_f)(0);   /*  compress  */
      if (v_d.vadd_free)  /* new slots in vadd. table */
         return( stck_dtopp(v_d.vadd_free) );
      else 
         if( (pg = Pg_Get_Page()) == (pg_t)-1 ) 
	   err_fatal("No memory at vadd_get_vadd.");
   }

   List_Insert(v_d.vadd_pgs,(list_elem_ptr)pg);
   v_d.vadd_pg  = pg;
   v_d.vadd_next = (vadd_t *)(pg + 2 * sizeof( list_elem_ptr ));
   v_d.vadd_left = v_d.vapp;

   DEBUG_End_Func("Get_vadd");

   return( v_d.vadd_next++ );

}/*vadd_get_vadd*/


/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */

