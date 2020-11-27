/* ------------------------------
 *
 * File       : @(#) blm.c
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : blm (Block Malloc; implementation)
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Generic memory block allocation
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include "pgpool.h"
# include "blmtypes.h"

/* ========== END OF DEPENDENCIES ========== */


/* ========== DEBUGGING MACRO DEFINITIONS ========== */
# ifdef DEBUG
#   define DEBUG_Init_Func(func) \
       printf("BLM: Init Function: %s\n",func)

#   define DEBUG_End_Func(func) \
       printf("BLM: End Function: %s\n\n",func)

# else
#   define DEBUG_Init_Func(func)
#   define DEBUG_End_Func(func)

# endif
/* ========== END OF DEBUGGING MACRO DEFINITIONS ========== */


/* ========== SYMBOL DEFINITIONS ========== */

# define BLM_ALLOW    0x1

/* ========== END OF SYMBOL DEFINITIONS ========== */


/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

blm_malloc_tp blm_malloc_l;       /* blmalloc buffers */
int           blm_flags = BLM_ALLOW;  /* allow blm_malloc to return memory */


/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */

void blm_init()
/* ------------------------------
 * Global     : blm_malloc_l
 * Comments   : Initializes the generic block allocation list.
 *
 * ------------------------------ */
{
  DEBUG_Init_Func("blm_init");

  blm_malloc_l.pg = blm_malloc_l.next_nd = blm_malloc_l.pg_end = NULL;

  DEBUG_End_Func("blm_init");
} /* blm_init */


char *blm_malloc(s)
  size_t s;
/* ------------------------------
 * Returns    : Pointer to an allocated memory block; NULL if error.
 * Global     : blm_malloc_l, flags;
 * Parameters : size of block to be allocated;
 * Comments   : Gets a new page and allocates a block of memory in it;
 *              returns NULL if there is no memory or if the "time for
 *              generic allocation" has gone.
 *
 * ------------------------------ */
{
   char *page_ptr = NULL;

   DEBUG_Init_Func("blm_malloc");

   if ((blm_flags & BLM_ALLOW) && (page_ptr = Pg_Get_Page())) {
      blm_malloc_l.pg      = page_ptr;
      blm_malloc_l.pg_end  = page_ptr + Page_Size;
      blm_malloc_l.next_nd = page_ptr + s;
   }

   DEBUG_End_Func("blm_malloc");

   return(page_ptr);
} /* blm_malloc */


/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
