/* --------------------------------
 *
 *    File: @(#)func.h   2.4
 *     Date: 4/22/91
 *    Module:  Function Names ( func ) 
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Suports function names table and related methods.
 * 
 *
 * --------------------- */ 

# ifndef __FUNC_H
#   define __FUNC_H 1


typedef struct func_infoStruct {
   int nlv; /* Number of loc Vars */
   int narg; /*Number of args.    */
   unsigned cdAddr;   /* start PC */
} func_infoType;

int func_isTraced( /*pc*/ );
/* --------------------------------
 * Returns: non-zero if function with `pc' is traced. 
 * Globals: func_funcTable, func_tableTop
 *  
 * --------------------- */ 

void func_readFunc( /*fp , show , flags*/);
/* --------------------------------
 * Globals: func_funcTable. 
 * Comments: Reads function names from `fp' echoing them if `show' 
 *           (allocates memory for func_funcTable) into func_funcTable.
 *           sets up flags about functions in `(int*)flags', currently only
 *           sets to non-zero if some function(s) are traced.
 *  
 * --------------------- */ 

char * func_funcName( /*pc , rule */);
/* --------------------------------
 * Returns: returns pointer to function name with pc `pc', and
 *          returns rule number in `rule'.
 * Globals: func_funcTable. func_tableTop
 * Req.: func_funcTable readed.
 * Comments:
 *  
 * --------------------- */ 

func_infoType *func_getInfo( /*name */ );
/* --------------------------------
 * Returns: returns pointer to an info struct about function
 *          with provided name.
 * Globals: func_funcTable. func_tableTop
 * Req.: func_funcTable readed.
 * Comments: info struct returned may not be modified:
 *           An assignment to it will alter internal data.
 *  
 * --------------------- */ 
/* THIS function always returns NULL , someday may be
 * needed to allow i.e. graph expresions scanned to have
 * functions.
 */


void func_terminate( /* void */ );
/* --------------------------------
 * Globals: func_funcTable
 * Comments: releases func_funcTable heap memory.
 *  
 * --------------------- */ 


# endif


