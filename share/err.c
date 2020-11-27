/* ------------------------------
 *
 * File       : @(#) err.c
 * Project    : Lbam
 * Date       : OCt/91
 * Module     : err (error )
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Gives a little error management
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <stdio.h>

# include <errno.h>

# include "share.h"

/* ========== END OF DEPENDENCIES ========== */

/* ========== GLOBAL VARIABLES DEFINITIONS ========== */
 

 char *err_prg_name = NULL;

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */



void err_fix_prg_name( n  )
   char *n; /* I */
/* ------------------------------
 * Global     : err_prg_name;
 * Parameters : the name for a program.
 * Comments   : Fix the program name to be used in future err msgs.
 *              The string IS NOT copied.
 *
 * ------------------------------ */
{

   err_prg_name = n;

}/*err_fix_prg_name*/


void err_show( msg )
  char *msg; /* I */
/* ------------------------------
 * Global     : err_prg_name
 * Parameters : the message to be said.
 * Comments   : dumps "<name_of_program> : <msg>" to stderr.
 *              If program name has not been fixed then only msg is dumped.
 *
 * ------------------------------ */
{
   if ( err_prg_name != (char *)NULL )
     fprintf(stderr,"%s : %s\n",err_prg_name,msg);
   else
     fprintf(stderr,"%s \n",msg);

}/*err_show*/


void err_fatal( msg )
  char *msg; /* I */
/* ------------------------------
 * Returns    : Do you really think it returns ?
 * Global     : err_prg_name
 * Parameters : the message to be said.
 * Comments   : dumps "<name_of_program> : <msg>" to stderr.
 *              If program name has not been fixed then only msg is dumped.
 *              Exits after message is dumped.
 * ------------------------------ */
{
   err_show( msg );
   exit(1);

}/*err_fatal*/


void err_sys_show(  /* void */  )
/* ------------------------------
 * Comments   : dumps  the message for last system call errno
 *
 * ------------------------------ */

{
  extern void perror();
  extern int sys_nerr;
  extern char **sys_errlist;
  extern int errno;

  if( errno >=0 && errno < sys_nerr )
     perror( err_prg_name );

}/*err_sys_show*/


/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */


