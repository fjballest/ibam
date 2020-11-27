/* --------------------------------
 *
 *    File: @(#)gc.h   1.0
 *    Date: 4/22/91
 *    Module:  Garbage collector ( gc )
 *    Programmer: Franc. J.B. Camara, Dylan Hoffman
 *
 *    Comments: Garbage collector for lbam Graph nodes.
 *
 *
 * --------------------- */

# ifndef __GC_H
#  define __GC_H 1

/*==================== EXTERNAL DEPENDENCIES ====================*/

# include "../../share/share.h"
# include "../../share/list.h"
# include "../../share/err.h"


/*==================== END OF EXTERNAL DEPENDENCIES =============*/

/*==================== TYPES ====================================*/

# include "gctype.h"


/* DO NOT USE this declarations : are for macros only */
extern gc_type gc_l; /* gc lists */
typedef void (*gc_f_type)(/* void * */);
extern gc_f_type *gc_f;  /* Array of gc_f_type functions */
extern char *gc_mcr_aux;
extern size_t gc_off;

/*==================== END OF TYPES ===============================*/

/*==================== INTERNAL DEPENDENCIES ======================*/
# define GC_IN_LIST 0x1
# define GC_CLEANED 0x2

# define Gc_Set_Cleaned(d) ((d)|=0x2)
# define Gc_Set_Uncleaned(d) ((d)&=~0x2)

# define Gc_Set_In(d) ((d)|=0x1)
# define Gc_Set_Out(d) ((d)&=~0x3)


# include "gcdecl.h"

# include "gcmacr.h"

/*==================== END OF INTERNAL DEPENDENCIES ===============*/

/* void gc_start( void );*/
/*-----------------
 * MACRO !!
 * Globals : gc_l,gc_f
 * Comments: empties lists.
 *------------------------*/




void gc_install_func( /* f, l */ );
/*-----------------
 * Globals : gc_l, gc_f
 * Comments: Sets a pointer to function f over g.c. list `l': When a 
 *           node in a gc list is about to be reused, if the pointer 
 *           is non-NULL the function ( pointed by it ) is called 
 *           with the (void *) node as argument, the funcion 
 *           can then clean the node so that someone else can use it.
 *           ADVISE: function f MAY be called twice or more times : It must
 *              be written consecuently.
 *------------------------*/

void gc_init(  );
/* ------------------------------
 * Global     : gc_l.
 * Comments   : Initializes GC 
 *
 * ------------------------------ */

# endif


