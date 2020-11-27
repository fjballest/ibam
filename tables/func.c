/* --------------------------------
 *
 *    File: @(#)func.c   2.4
 *    Date: 4/22/91
 *    Module:  Function Names ( func ) 
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Suports function names table and related methods.
 * 
 *
 * --------------------- */ 

/*============================= DEPENDENCIES =========================*/

# include <stdio.h>
# include <ctype.h>
# include <string.h>

# include "../share/share.h"
# include "../txio/txio.h"
# include "names.h"

/*====================== END OF DEPENDENCIES =========================*/


typedef struct func_infoStruct {
   int nlv; /* Number of loc Vars */
   int narg; /*Number of args.    */
   unsigned cdAddr;   /* start PC */
} func_infoType;

typedef struct func_funcStruct{
   char *name;
   int pcend;
   int flags;
   func_infoType inf;
}func_funcType;

func_funcType *func_funcTable;/* internal function names
                                                table           */
int func_tableTop;


void func_readFunc( fp, show, flags )
FILE *fp;
int show;
int *flags;
/* --------------------------------
 * Globals: func_funcTable. 
 * Comments: Reads function names from `fp' echoing them if `show' 
 *           (allocates memory for func_funcTable) into func_funcTable.
 *           sets up flags about functions in `(int*)flags', currently only
 *           sets to non-zero if some function(s) are traced.
 *  
 * --------------------- */ 
{
   int pos= 0;
   int c;

   if ( ! fscanf(fp,"%d",&func_tableTop) )
      txio_fatal(" Fail while reading number of functions.");
   if ( ( func_funcTable = 
      (func_funcType *)
      calloc( func_tableTop,sizeof(func_funcType)) )  == NULL )
      txio_fatal(" Fail while allocating memory for functions.");
   if (show )
      txio_printstr(" Reading functions . . . \n");

   for( ; pos < func_tableTop ; pos++ ) {
      if ( (func_funcTable[pos].name = nm_install(fp)) == NULL )
         txio_fatal( "Fail allocanting function in table");
      if( show ) 
          txio_printf("...[%s] readed as function ",func_funcTable[pos].name);
      if ( ! fscanf(fp,"%d",&(func_funcTable[pos].pcend) ) )
         txio_fatal(" Fail while reading pc-end.");
      if( show ) txio_printf(",last PC [%d]", func_funcTable[pos].pcend);
      while( ( c = getc(fp)) != EOF && c != '\n' && c != '*' )
         ;
      if ( (func_funcTable[pos].flags = ( c == '*' )) && show )
         txio_printf(",will be traced");
      if( show) txio_printf( ".\n");
   }
  if ( show ) txio_printf("Functions Ok.\n");
     
}/* func_readFunc */


char * func_funcName( pc, rule )
int pc;
int *rule;
/* --------------------------------
 * Returns: returns pointer to function name with pc `pc', and
 *          returns rule number in `rule'.
 * Globals: func_funcTable. CONF_PRG_BEGIN. func_tableTop
 * Req.: func_funcTable readed.
 * Comments:
 *  
 * --------------------- */ 

{
   static char *mtsk = "mtsk";
   static char *objv = "objv";
   int index;

   if (pc < CONF_PRG_BEGIN)
      return ( *rule = 1 , mtsk);

   for( index = 0,*rule=1;
       index < func_tableTop && func_funcTable[index].pcend < pc;
       index++)
      if ( !index || 
          strcmp(func_funcTable[index].name,func_funcTable[index-1].name) )
         *rule = 1;
      else 
         (*rule)++;

   if ( index < func_tableTop ){
      if ( !index || 
          strcmp(func_funcTable[index].name,func_funcTable[index-1].name) )
         *rule = 1;
      else 
         (*rule)++;
      return func_funcTable[index].name;
   }
   else
      return ( *rule = 1 , objv);

}



int func_isTraced( pc )
int pc;
/* --------------------------------
 * Returns: non-zero if function with `pc' is traced. 
 * Globals: func_funcTable, func_tableTop
 * Req.:
 * Comments:
 *  
 * --------------------- */ 
{
   int index;
   for( index = 0;
       index < func_tableTop && func_funcTable[index].pcend < pc;
       index++)
      ;
   if ( index < func_tableTop )
      return func_funcTable[index].flags;
   else
      return TRUE;

}/*func_isTraced*/

func_infoType *func_getInfo( n  )
   char *n;
/* --------------------------------
 * Returns: returns pointer to an info struct about function
 *          with provided name.
 * Globals: func_funcTable. func_tableTop
 * Req.: func_funcTable readed.
 * Comments: info struct returned is static: values are 
 *           modified after a second call.
 *  
 * --------------------- */ 
{
  return( NULL );

}/*func_getInfo*/

void func_terminate( /* void */ )
/* --------------------------------
 * Returns: --
 * Globals: func_funcTable
 * Comments: releases func_funcTable heap memory.
 *  
 * --------------------- */ 
{
   free( func_funcTable );
}



