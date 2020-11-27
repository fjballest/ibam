/* ------------------------------
 *
 * File       : @(#) lbamstd.c ( Lbam statistics daemon )
 * Project    :  Lbam
 * Date       :  Nov/91
 * Module     : stat
 * Programmer : Francisco J. Ballesteros, Dylan L. Hoffman
 *
 * Comments   : A process that does accounting of statistic
 *              messages.
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <stdio.h>

# include <signal.h>

# include "../ipc/ipc.h"

# include "../share/share.h"

# include "../share/err.h"

# include "../share/rgetopts.h"

/* ========== END OF DEPENDENCIES ========== */
/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

 char dfl_acc_fname[10] = "lbam.a";
/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */

/* ========== FUNCTION IMPLEMENTATIONS ========== */

void start_acc( f )
FILE *f;
/* ------------------------------
 * Parameters : file where accounting is done.
 * Comments   : Writes begin of session info in f.
 *
 * ------------------------------ */
{
 fprintf(f,"# **** Begin of accounting ****#\n");

}/*start_acc*/

void end_acc( f )
FILE *f;
/* ------------------------------
 * Parameters : file where accounting is done.
 * Comments   : Writes end of session info in f.
 *
 * ------------------------------ */
{
 fprintf(f,"# ***** End of accounting *****#\n");

}/*end_acc*/

void do_pool_put( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page putted in the pool
 *
 * ------------------------------ */
{
  fprintf(acc_f,"pool:P:\n");
}/*do_pool_put*/

void do_pool_get( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page got from  the pool
 *
 * ------------------------------ */
{
  fprintf(acc_f,"pool:G:\n");
}/*do_pool_get*/

void do_gmm_pg_put( acc_f, buff )
  FILE *acc_f;
  char *buff;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page putted in a list of pages for nodes.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"gmm:P:%c\n",*buff);
}/*do_gmm_pg_put*/

void do_gmm_pg_get( acc_f, buff )
  FILE *acc_f;
  char *buff;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page got from a list of pages for nodes.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"gmm:G:%c\n",*buff);
}/*do_gmm_pg_get*/

void do_vadd_put( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page putted in vaddr list.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"vadd:P:\n");
}/*do_vadd_put*/

void do_vadd_get( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another page got from vaddr list.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"vadd:G:\n");
}/*do_vadd_get*/

void do_compr( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another succesfull compression.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"compr:S:\n");
}/*do_compr*/

void do_compr_fail( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Parameters : accounting file.
 * Comments   : Accounts another fail at compression.
 *
 * ------------------------------ */
{
  fprintf(acc_f,"compr:F:\n");
}/*do_compr_fail*/


void do_account( acc_f )
  FILE *acc_f;
/* ------------------------------
 * Global     : prg_name
 * Parameters : acc_f is the file where accounting is done.
 * Comments   : Receives and process messages.
 *
 * ------------------------------ */
{
    char buff[IPC_BUFF_SIZE+1];
    long msg_t;
    static long last_msg=0;
    static char last_buff[IPC_BUFF_SIZE+1]=NULL;
    static int  last_acc=0;
    
    if ( acc_f == (FILE *)NULL ) return;

    start_acc( acc_f );

    do { /* receive a msg and process it. */
      if ( (msg_t = ipc_rcv( buff ))==last_msg && strcmp(buff,last_buff)==0 ) {
         last_acc++;
      } else {
          if( last_msg )
             fprintf(acc_f,"%d:",last_acc);
	  switch( last_msg ){
              case 0:
                break;
	      case IPC_T_POOL_PUT:
		do_pool_put( acc_f );
		break;
	      case IPC_T_POOL_GET:
		do_pool_get( acc_f );
		break;
	      case IPC_T_GMM_PG_PUT:
		do_gmm_pg_put( acc_f, buff );
		break;
	      case IPC_T_GMM_PG_GET:
		do_gmm_pg_get( acc_f, buff );
		break;
	      case IPC_T_VADD_PUT:
		do_vadd_put( acc_f );
		break;
	      case IPC_T_VADD_GET:
		do_vadd_get( acc_f );
		break;
	      case IPC_T_COMPR:
		do_compr( acc_f );
		break;
	      case IPC_T_COMPR_FAIL:
		do_compr_fail( acc_f );
		break;
	      case IPC_T_END:
		err_show(" Received [End~of~work] message.");
		break;
	      case IPC_T_ERR:
		err_sys_show( );
		break;
	      default:
		err_show(" Message with wrong type.");
	  } /* switch */
          last_msg = msg_t;
          last_acc = 1;
          strncpy(last_buff,buff,IPC_BUFF_SIZE+1);
      } /* if-else */
   } while( msg_t != IPC_T_END && msg_t != IPC_T_ERR );
    if( msg_t == IPC_T_END )
	err_show(" Received [End~of~work] message.");
    end_acc( acc_f );

}/*do_account*/

int main( argc, argv )
  int argc;
  char **argv;
/* ------------------------------
 * Returns    : error condition
 * Comments   : Send a SIGCONT to the father after ipc module
 *              has been initialized.
 *
 * ------------------------------ */
{
 int opt;
 char *optarg;
 ipc_buff_tp buff;       /* Buffer to receive data from Lbam */
 char *acc_fname =  dfl_acc_fname; 
 FILE *acc_f;            /* Accounting file */
 
 /* Work with command line... */
 err_fix_prg_name( *argv );

 opt_init( argv, "f:", OPT_NOPIPE );

 while( ( opt = opt_get( &optarg )) != OPT_ERR && opt )
    switch( opt ) {
    case 'f': /* specify accounting file */
       acc_fname = optarg;
       break;
    } 
    if ( opt == OPT_ERR ) {
       err_show( opt_err_msg[opt_errno] );
       err_fatal( " valid options are [-f file]");
    }
 /* Connect with Lbam... */ 
 if ( ipc_init(TRUE) ) 
    err_fatal( "I can't connect with Lbam.");
 fprintf(stderr,"%s : Message queue id [%d]\n",
         err_prg_name,ipc_msg );


 if ( ( acc_f = fopen( acc_fname, "w" )) == NULL )
    err_show("Can't open accounting file for writting.");
 else
    do_account( acc_f );

 /* terminate IPC system and exit */
 ipc_terminate(TRUE);
 kill(getppid(),SIGCONT);
 err_show("bye.");
 return(0);
}/*main*/




/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
