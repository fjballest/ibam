/* --------------------------------
 *
 *    File: @(#)ovar.c   2.4
 *    Date: 4/22/91
 *    Module: Objective Variables ( ovar )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports objective variable table and methods.
 * 
 *
 * --------------------- */ 

/*========================= DEPENDENCIES ==============================*/
# include <stdio.h>
# include <ctype.h>
# include <string.h>

# include "../share/share.h"
# include "../txio/txio.h"
# include "names.h"

/*========================= END OF DEPENDENCIES =======================*/

typedef char *ovar_nameType;
ovar_nameType *ovar_varTable;/* internal varible table*/
int ovar_tableTop;           /* number of vars */

void ovar_readVar( fp, show )
FILE *fp;
int show;
/* --------------------------------
 * Globals: ovar_varTable ovar_tableTop
 * Comments: reads from `fp' variable names into ovar_varTable.
 *           if show is non-zero echoes names as readed.
 *  
 * --------------------- */ 
{
   int pos = 0;

   if ( !fscanf(fp,"%d",&ovar_tableTop) )
      txio_fatal("Fail while reading number of vars.");
   if ( (ovar_varTable=
      (ovar_nameType *)malloc(sizeof(ovar_nameType *)*ovar_tableTop))==NULL)
      txio_fatal("Fail while allocating memory for vars. table.");
   if ( show ) txio_printf("Reading objective variables...\n");
   for( ; pos < ovar_tableTop ; pos++ ) {
      if ( (*(ovar_varTable + pos ) = nm_install(fp)) == NULL )
         txio_fatal( "Fail allocanting variable in table");
      if( show ) 
          txio_printf("...[%s] readed as variable.\n",*(ovar_varTable+pos));
              
   }
  if ( show ) txio_printf("Objective variables Ok.\n");
     
}/* ovar_readVar */


void ovar_terminate( ) 
/* --------------------------------
 * Comments: releases memory held on tables.
 *  
 * --------------------- */ 
{
    free( ovar_varTable );

}/*ovar_terminate*/


int ovar_searchVar( name , ind )
char * name;
int * ind;
/* --------------------------------
 * Returns: error status ( non-zero if not found ).
 * Globals: ovar_varTable ovar_tableTop
 * Comments: sets ind to position for `name' variable.
 *  
 * --------------------- */ 
{
   for( *ind = 0 ; *ind < ovar_tableTop && 
          ! strcmp(*(ovar_varTable + *ind), name ) ; ind++ )
      ;
   if ( *ind >= ovar_tableTop )
      return( TRUE );
   else return( FALSE );

}/* ovar_searchVar */





