/* --------------------------------
 *
 *    File: @(#)ovar.h   2.4
 *     Date: 4/22/91
 *    Module: Objective Variables ( ovar )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports objective variable table and methods.
 * 
 *
 * --------------------- */ 

#ifndef _OVARTYPES_
#  define _OVARTYPES_

typedef char ovar_nameType[CONF_LONG_VNAME];

extern ovar_nameType ovar_varTable[];

/* internal defines needed here */
#define ovar_varName(ind)    ((char *)(ovar_varTable[(ind)]))

/* char *ovar_varName(  index );*/
/* --------------------------------
 * Returns: name of index-th variable.
 * Globals: ovar_varTable ovar_tableTop
 * Comments: ( macro )
 * --------------------- */ 

void ovar_readVar( /*fp , show */);
/* --------------------------------
 * Globals: ovar_varTable ovar_tableTop 
 * Comments: reads from `fp' variable names into ovar_varTable.
 *           if show is non-zero echoes names as readed.
 *  
 * --------------------- */ 

void ovar_terminate( /* void */ );
/* --------------------------------
 * Comments: releases memory held on tables.
 *  
 * --------------------- */ 

int ovar_searchVar( /*name , ind */);
/* --------------------------------
 * Returns: error status ( non-zero if not found ).
 * Globals: ovar_varTable ovar_tableTop
 * Comments: sets ind to position for `name' variable.
 *  
 * --------------------- */ 


#endif



