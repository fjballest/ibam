/* ------------------------------
 *
 * File       : @(#) boot.c
 * Project    : Lbam
 * Date       : Nov/91
 * Module     : Lbam booting
 * Programmer : Dylan L. Hoffman, Francisco J. Ballesteros
 *
 * Comments   :  Makes the Lbam work.
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <signal.h>

# include <stdio.h>

# include "share/share.h"

# include "share/err.h"

# include "ipc/ipc.h"

/* ========== END OF DEPENDENCIES ========== */

/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

int son_init_done = 0;

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */
/* ========== FUNCTION IMPLEMENTATIONS ========== */


void get_CONT()
/* ------------------------------
 * Global     : son_init_done
 * Comments   : sets son_init_done to TRUE value.
 *
 * ------------------------------ */
{ 
  extern int son_init_done;
  son_init_done = TRUE;
  
}/*get_CONT*/

int launch_stat()
/* ------------------------------
 * Returns    : non-zero if error.
 * Comments   : forks and launch statistics daemon.
 *
 * ------------------------------ */
{
   
   switch( fork() ){
   case 0:  
      signal(SIGCONT, SIG_DFL );
      execl( "stat/lbamstd", "lbamstd",NULL);
      err_sys_show();
      err_fatal("Fail while executing lbamstd.");
      break;
   case -1: return(TRUE);
   default: return(FALSE);
   }
}/*launch_stat*/

int launch_bam()
/* ------------------------------
 * Returns    : non-zero if error.
 * Comments   : forks and launch statistics daemon.
 *
 * ------------------------------ */
{
   
   switch( fork() ){
   case 0:  
      signal(SIGCONT, SIG_DFL );
      execl( "bam", "bam",NULL);
      err_sys_show();
      err_fatal("Fail while executing lbam.");
      break;
   case -1: return(TRUE);
   default: return(FALSE);
   }
}/*launch_bam*/

int main( argc, argv, envp ) 
  int argc;
  char **argv;
  char **envp;
{

 err_fix_prg_name( *argv );

 /* Set up IPC */
 if ( ipc_init(FALSE) ) {
    err_sys_show();
    err_fatal(" Initialization error - Bye.");
 }
 printf("%s : message id [%d]\n",err_prg_name,ipc_msg );

 /* Process launching */
 signal( SIGCONT, get_CONT );
 if ( launch_stat() || launch_bam() ) 
    err_show("Fail at booting");

 if ( !son_init_done ) 
   pause();
 ipc_terminate(FALSE);
 signal( SIGCONT, SIG_DFL );
 printf("%s : Bye.\n",err_prg_name);
 return(0);
}/* main */

/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
