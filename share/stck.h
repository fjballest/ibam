/* --------------------------------
 *
 *    File: @(#)stck.h   2.4
 *    Date: 4/22/91
 *    Module:  Stacks ( stck)
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Provides both an static and a dinamic 
 *              implementation of stacks.
 * 
 *
 * --------------------- */ 


#ifndef __STCK_H
#  define __STCK_H 1

/*================== DEPENDENCIES ===============================*/

# include "stckmacr.h"

/*================== END OF DEPENDENCIES ========================*/

/* The static stack has no vector of elements built into it. Instead,
 * you must give a pointer to  `stck_elemType' as buffer. 
 * stack UNDERFLOW is NOT checked currently, you can check for it 
 * making the first element of the vector to be a known value and
 * creating the stack giving it the second one as the first.
 * when a stck_top returns this value, underflow it there.
 * OVERFLOW is NOT CHECKED.
 */

/* Both static and dinamic stacks can be asigned, the duplicate stack
 * will point to the same storage area pointed by the source one.
 * The only requeriment is that no pop and no push can be done with
 * the duplicate.
 */

   typedef void *stck_elemType;
	 typedef void *stck_dstackType;


   extern void (*stck_copy_func)();
   typedef struct stck_stackNode{
       void **top;
       void **dat;
       } stck_stackType;



   extern void *aux_d_stack_1; /* <- Local variable for macros*/

/********* IMPORTANT NOTE ***
 * The below functions are static stack methods, the bottom ones
 * ( `stck_d...' ) are dinamic stack methods.
 **********************/

/* void stck_move( st ); */
/* --------------------------------
 * Comments: ( macro ) 
 * Makes a pop in the stack without remove top element.
 * --------------------- */ 

/* void stck_buffpt( st ); */
/* --------------------------------
 * Returns: a pointer to the stack buffer.
 * Coments: ( macro )
 * --------------------- */ 

/*void stck_pop( st );*/
/* void stck_create( st, buff ); */
/* --------------------------------
 * Returns: A new empty stack.
 * Coments: ( macro )
 * --------------------- */ 

/*void stck_pop( st );*/
/* --------------------------------
 * Req.: st is non-empty
 * Comments: ( macro )
 * --------------------- */ 

/*void *stck_top (  st );*/
/* --------------------------------
 * Returns: st's top
 * Req.: st is non-empty
 * Comments: ( macro )
 * --------------------- */ 

/*void stck_stackCpy( dest , src );*/
/* --------------------------------
 * Req.: dest initialized.
 * Comments: Copies src into dest ( calling stck_copy_func for each 
 *           element ). Disposes parts of dest if needed.
 *           ( macro )
 *  
 * --------------------- */ 

/*void stck_stackInstall( dest , src );*/
/* --------------------------------
 * Req.: dest initialized.
 * Comments: Copies src into dest ( do not call stck_copy_func for each 
 *           element ). Disposes parts of dest if needed.
 *           ( macro )
 * --------------------- */ 

void stck_installCpyFunc( /* f*/ );
/* --------------------------------
 * Returns: --
 * Globals: stck_copy_func
 * Req.:    
 * Comments: Install `f' in stck_copy_func : function to be called
 *           in stack-copying.f is void (*f)( void *p )
 *  
 * --------------------- */ 

/*void stck_empty(st );*/
/* --------------------------------
 * Comments: Empties st ( macro )
 *  
 * --------------------- */ 

/*int stck_isEmpty(  st);*/
/* --------------------------------
 * Returns: non-zero if st is empty 
 * Comments: ( Macro )
 * --------------------- */ 

/*void stck_stackApp( dst, src );*/
/* --------------------------------
 * Comments: appends src to dst and empties src ( macro )
 *  
 * --------------------- */ 

/*void  stck_push( st , element );*/
/* --------------------------------
 * Req.: element is pointer to xxx
 * Comments: push element in st
 * --------------------- */ 

/* void stck_dmove( st ); */
/* --------------------------------
 * Comments: ( macro ) 
 * Makes a pop in the stack without remove top element.
 * --------------------- */ 

/*stck_dstackType stck_dcreate(void);*/
/* --------------------------------
 * Returns: A new empty stack.
 * Coments: ( macro )
 * --------------------- */ 

/* void stck_dpop( st ); */
/* --------------------------------
 * Req.: st is non-empty
 * Comments: ( macro )
 * --------------------- */ 


/*void *stck_dtop ( st );*/
/* --------------------------------
 * Returns: st's top
 * Req.: st is non-empty
 * Comments: ( macro )
 * --------------------- */ 

/*void *stck_dtopp ( st );*/
/* --------------------------------
 * Returns: st's top
 * Req.: st is non-empty
 * Comments: ( macro ) POPS the stack too.
 * --------------------- */ 

/* void  stck_dempty( st ); */
/* --------------------------------
 * Comments: Empties st ( macro )
 *  
 * --------------------- */ 

/*int stck_disEmpty( st);*/
/* --------------------------------
 * Returns: non-zero if st is empty 
 * Comments: ( Macro )
 * --------------------- */ 

/* void stck_dpush( st , element ); */
/* --------------------------------
 * Req.: element is pointer to xxx
 * Comments: push element in st
 * --------------------- */ 

#endif




