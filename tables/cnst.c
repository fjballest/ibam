/* --------------------------------
 *
 *    File: @(#)cnst.c   2.4
 *    Date: 4/22/91
 *    Module: Constants and Constructors ( cnst )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports constants and constructors tables and methods.
 * 
 *
 * --------------------- */ 

/*====================== DEPENDECIES ====================================*/
# include <stdio.h>
# include <ctype.h>

# include "../share/share.h"
# include "../txio/txio.h"
# include "cnsttype.h"
# include "names.h"

/*======================== END OF DEPENDENCIES ==========================*/

cnst_constTableType cnst_constTable;  /* constants table    */
cnst_constrTableType cnst_constrTable;/* constructors table */

/* shorthands to fields... */
# define  cnstr_nm cnst_constrTable.name
# define  cnst_nm cnst_constTable.name
# define  cnstr_top cnst_constrTable.cardinal
# define  cnst_top cnst_constTable.cardinal

void cnst_constructTable( fp, show )
FILE *fp;
int show;
/* --------------------------------
 * Globals: cnst_constTable, cnst_constrTable, nm_*
 * Comments: reads constants and constructors .
 *  
 * --------------------- */
{
   int pos = 0;
   size_t size;

   if ( ! fscanf(fp,"%d",&cnst_top ) )
      txio_fatal(" Fail while reading number of constants. ");
   size = sizeof( cnst_consNameType ) * (size_t) cnst_top;
   if ( (cnst_nm = (cnst_constType)malloc(size)) == NULL )
      txio_fatal("Fail while allocating memory for constants names.");

   if ( show ) txio_printf("Reading constants...\n");
   if ( nm_top + 12 < nm_end ) {/* space enough to "true" & "false"*/
      *(cnst_nm + pos++) = nm_top;
      strcpy(nm_top, "false" ); nm_top += 6;
      *(cnst_nm + pos++) = nm_top;
      strcpy(nm_top, "true" );  nm_top += 5;
      cnst_top += 2;
   } else 
      txio_fatal("Fail while allocating memory for true & false.");
   if ( show ) {
      txio_printf("...[true] predefined as constant.\n");
      txio_printf("...[false] predefined as constant.\n");
   }
   for( ; pos < cnst_top ; pos++ ) {
      if ( (*(cnst_nm + pos ) = nm_install(fp)) == NULL )
         txio_fatal( "Fail allocanting constant in table");
      if( show )
          txio_printf("...[%s] readed as constant.\n",*(cnst_nm + pos ));
   }
  if ( show ) txio_printf("Constants Ok.\n");

   if ( ! fscanf(fp,"%d",&cnstr_top ) )
      txio_fatal(" Fail while reading number of constructors. ");
   size = sizeof( cnst_consNameType ) * (size_t) cnstr_top;
   if ( (cnstr_nm = (cnst_constrType)malloc(size)) == NULL )
      txio_fatal("Fail while allocating memory for constructors names.");

   if ( show ) txio_printf("Reading constructors...\n");

   for( ; pos < cnstr_top ; pos++ ) {
      if ( (*(cnstr_nm + pos ) = nm_install(fp)) == NULL )
         txio_fatal( "Fail allocanting constructor in table");
      if( show )
          txio_printf("...[%s] readed as constructor.\n",*(cnstr_nm + pos ));
   }
  if ( show ) txio_printf("Constructors Ok.\n");

}/*cnst_constructTable*/

void cnst_terminate( ) 
/* --------------------------------
 * Comments: releases memory held on tables.
 *  
 * --------------------- */ 
{
   free( cnst_nm ); free( cnstr_nm );

}/*cnst_terminate*/

int cnst_searchConst( name , index )
cnst_consNameType name;
int * index;
/* --------------------------------
 * Returns: Returns non-zero if not found. 
 * Globals: cnst_constTable 
 * Comments: makes *index to be slot number for `name'.
 *  
 * --------------------- */
{
   int res;

   for( *index=0 ;
       *index < cnst_top && (res = strcmp(name,*(cnst_nm+ *index))) != 0 ;
       ++*index)
      ;
   --*index;
   --*index;
   return res;

}/* cnst_searchConst */

int cnst_searchConstr( name , index )
cnst_consNameType name;
int * index;
/* --------------------------------
 * Returns: non-zero if not found.
 * Globals: cnst_constrTable.
 * Comments: Makes *index to be slot number for `name'
 *  
 * --------------------- */
{

   for( *index=0 ;
       *index < cnstr_top && strcmp(name,*(cnstr_nm + *index));
       ++*index)
      ;

   return strcmp(name,*(cnstr_nm + *index));

}/* cnst_searchConstr */





