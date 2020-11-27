/* --------------------------------
 *
 *    File: @(#)stck.c   2.4
 *     Date: 4/22/91
 *    Module:  Stacks ( stck)
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Provides both an static and a dinamic 
 *              implementation of stacks.
 * 
 *
 * --------------------- */ 

/*=============== DEPENDENCIES ==================================*/

#include <stdio.h>

#include "share.h"


/*=============== END OF DEPENDENCIES ===========================*/

void null_func( e )
void *e;
/* --------------------------------
 * Comments: The identity function: Default for stck_copy_func.
 * --------------------- */ 

{
   e = e;

} /* null_func */

void **stck__pt;

void (*stck_copy_func)() = null_func;

void *aux_d_stack_1;

void stck_installCpyFunc( f )
void (*f) ();
/* --------------------------------
 * Returns: --
 * Globals: stck_copy_func
 * Req.:    
 * Comments: Install `f' in stck_copy_func : function to be called
 *           in stack-copying.
 *  
 * --------------------- */ 
{
   stck_copy_func = f;

}
















