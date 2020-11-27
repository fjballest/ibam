/* --------------------------------
 *
 *    File: @(#)names.c 1.0
 *    Date: 4/22/91
 *    Module: Names (nm )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Buffers and methods for names. 
 * 
 *
 * --------------------- */ 

/*======================== DEPENDENCIES ==============================*/

# include <stdio.h>
# include <ctype.h>

/*======================== END OF DEPENDENCIES =======================*/
# define NAMES_BUFF_SIZE 2048

static char nm_buff[NAMES_BUFF_SIZE];
char *nm_top = &nm_buff[0];
char *nm_end = &nm_buff[NAMES_BUFF_SIZE];

char *nm_install( fp )
FILE *fp;
/*------------------------------
 * Returns: Pointer to allocated space for a new name. NULL if error.
 * Globals: all of this module.
 * Comments: Read a name from fp and installs it in nm_buff.
 *------------------------------*/
{
   int c;
   char *res = nm_top;

   while ( isspace( c=getc(fp)) && c != EOF )
      ;
   if ( c == EOF ) 
      return( NULL );
   else ungetc(fp);
   
   while( nm_top < nm_end && !isspace(*nm_top = getc(fp)) &&
          *nm_top != EOF )
      nm_top++;
   *nm_top = (char)0;
   if ( nm_top = nm_end ) {/* ovf error */
      nm_top = res;
      return( NULL );
   } else 
      return( res );

}/*nm_install*/



