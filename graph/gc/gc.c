/* --------------------------------
 *
 *    File: @(#)gc.c   1.0
 *    Date: 4/22/91
 *    Module:  Garbage collector ( gc )
 *    Programmer: Franc. J.B. Camara, Dylan Hoffman
 *
 *    Comments: Garbage collector for lbam Graph nodes.
 *
 *
 * --------------------- */

/*===================== DEPENDENCIES ===========================*/

# include "../../share/share.h"
# include "../../share/list.h"
# include "../../share/err.h"
# include "gctype.h"
# include "gcmacr.h"

/*===================== END OF DEPENDENCIES ====================*/

/* ========== DEBUGGING MACRO DEFINITIONS ========== */
# ifdef DEBUG
#   define DEBUG_Init_Func(func) \
       printf("GC: Init Function: %s\n",func)

#   define DEBUG_End_Func(func) \
       printf("GC: End Function: %s\n\n",func)

# else
#   define DEBUG_Init_Func(func)
#   define DEBUG_End_Func(func)

# endif
/* ========== END OF DEBUGGING MACRO DEFINITIONS ========== */


# define GC_IN_LIST 0x1
# define GC_CLEANED 0x2

# define Gc_Set_Cleaned(d) ((d)|=0x2)
# define Gc_Set_Uncleaned(d) ((d)&=~0x2)

# define Gc_Set_In(d) ((d)|=0x1)
# define Gc_Set_Out(d) ((d)&=~0x1)

typedef void (*gc_f_type)(/* void * */);
gc_type gc_l; /* gc lists */
char *gc_mcr_aux;
size_t gc_off = 2 *sizeof(void *);

int gc_inGC( p )
   void *p;
{
   DEBUG_Init_Func("gc_inGC");
   DEBUG_End_Func("gc_inGC");

   return(  *((short *)(((char *)p)+gc_off)) & GC_IN_LIST  );

}/*gc_inGC*/

void gc_null(p)
  void *p;
{
  p=p;
  return;
} /* gc_null */


# include "gcimpl.c"

void gc_install_func( f, l )
   void (*f)();
   int l;
/*-----------------
 * Globals : gc_l, gc_f
 * Comments: Sets a pointer to function f over g.c. list `l': When a 
 *           node in a gc list is about to be reused, if the pointer 
 *           is non-NULL the function ( pointed by )is called with the
 *           (void*) node as argument, the funcion can then clean the 
 *           node so that someone else can use it.
 *------------------------*/
{
   DEBUG_Init_Func("gc_install_func");

   gc_f[l] = f;

   DEBUG_End_Func("gc_install_func");
}/*gc_install_func*/

