/* --------------------------------
 *
 *    File: @(#)cnst.h   2.4
 *    Date: 4/22/91
 *    Module: Constants and Constructors ( cnst )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports constants and constructors tables and methods.
 * 
 *
 * --------------------- */ 

#ifndef _CNSTTYPES_
#  define _CNSTTYPES_

/*=============== DEPENDENCIES ========================================*/

#include "cnsttype.h"  
/* cnst internal use only */

/*=============== END OF DEPENDENCIES =================================*/



/*char *cnst_constName(index);*/
/* --------------------------------
 * Returns:   Name for constant in slot index. 
 *         ( NULL if not found ).
 * Globals:  cnst_constTable.
 * Comments: ( macro )
 *  
 * --------------------- */ 

/*char *cnst_constrName( int index);*/
/* --------------------------------
 * Returns:   Name for constructor in slot index. 
 *         ( NULL if not found ).
 * Globals:  cnst_constrTable.
 * Comments: ( macro )
 *  
 * --------------------- */ 

void cnst_constructTable( /*fp, show*/ );
/* --------------------------------
 * Globals: cnst_constTable, cnst_constrTable, nm_*
 * Comments: reads constants and constructors .
 *  
 * --------------------- */

void cnst_terminate( /*void*/  );
/* --------------------------------
 * Comments: releases memory held on tables.
 *  
 * --------------------- */ 

/*int cnst_numberConstants( void );*/
/* --------------------------------
 * Returns: Number of constants in table.
 * Globals: cnst_constTable.
 * Comments: ( Macro )
 * --------------------- */ 

/*int cnst_numberConstructors( void );*/
/* --------------------------------
 * Returns: Number of constructors in table.
 * Globals: cnst_constrTable.
 * Comments: ( Macro )
 * --------------------- */ 

int cnst_searchConst( /*name , index */);
/* --------------------------------
 * Returns: Returns non-zero if not found. 
 * Globals: cnst_constTable 
 * Comments: makes *index to be slot number for `name'.
 *  
 * --------------------- */

int cnst_searchConstr( /*name , index */);

/* --------------------------------
 * Returns: non-zero if not found.
 * Globals: cnst_constrTable.
 * Comments: Makes *index to be slot number for `name'
 *  
 * --------------------- */

/* internal definitions needed here. */



   extern cnst_constTableType cnst_constTable;/*in cnst.c */
   extern cnst_constrTableType cnst_constrTable;

#  define cnst_numberConstants()  (cnst_constTable.cardinal-2)
#  define cnst_numberConstructors()  cnst_constrTable.cardinal

#  define cnst_constrName(index)  \
   ((cnst_constrTable.cardinal<=(index))?NULL:\
   (char*)cnst_constrTable.name[(index)])

#  define cnst_constName(index)   \
   ((cnst_constTable.cardinal<=(index))?NULL:\
   (char*)cnst_constTable.name[(index)])

#endif




