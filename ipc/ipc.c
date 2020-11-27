/* ------------------------------
 *
 * File       : @(#) ipc.c
 * Project    : Lbam
 * Date       : Nov-1991
 * Module     : ipc ( Messages ( via shared memory & signals )
 * Programmer : Dylan L. Hoffman & Francisco J. Ballesteros
 *
 * Comments   : Provides a fast message mechanism using shared memory
 *              segments and signals ( Inside the Lbam process group )
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include "../share/defs.h"

# ifdef SPARC

#   include <sys/types.h>

#   include <sys/ipc.h>

#   include <sys/msg.h>

# endif

# include <string.h>

# include "../share/share.h"

# include "ipctype.h"

# include "share.h"

/* ========== END OF DEPENDENCIES ========== */


/* ========== MACRO DEFINITIONS ========== */

# define Ipc_Get_Buff_Size() 5

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

# ifdef SPARC

key_t ipc_msg_key; /* Key for this process shared memory... */
int   ipc_msg;     /* Shared memory segment descriptor      */
int   ipc_son_proc;/* Non-zero after ipc_init if this process is son */
ipc_buff_tp ipc_m; /* message  */

# endif

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */


key_t ipc_get_key( iamson )
  int iamson; /* I */
/* ------------------------------
 * Returns    : An unique? key for the current process.
 * Parameters : iamson is non-zero if this is the son of the main Lbam
 *              process
 *
 * ------------------------------ */
{ 
  return( (iamson) ? (key_t)getppid() : (key_t)getpid() );

}/*ipc_get_key*/


int ipc_init( son )
   int son;
/* ------------------------------
 * Returns    : non-zero if error occurs.
 * Global     : ipc_msg ipc_msg_key ipc_buff ipc_son_proc
 * Parameters : son must be non-zero if current process is the a son of the
 *              one that got the msg queue.
 * Comments   : This function is called once from the father of the processes
 *              that will be using the messages and later must be called 
 *              by each process that wants to use the message system.
 *
 * ------------------------------ */
{
# ifdef SPARC

   /* Get shared memory */
   ipc_msg_key = ipc_get_key( (ipc_son_proc = son) );
   if ( ipc_msg_key < 0 ) return(TRUE);
   ipc_msg = msgget( ipc_msg_key, 0770 | IPC_CREAT );
   if ( ipc_msg < 0 ) return( TRUE );
   return( FALSE );
# endif

}/*ipc_init*/


void ipc_terminate( /* void */ )
/* ------------------------------
 * Global     : ipc_msg ipc_buff ipc_son_proc
 * Comments   : Terminates the shared memory segment used by this module.
 *              Should be called after sons calls to ipc_init()
 *
 * ------------------------------ */
{
# ifdef SPARC

  if (! ipc_son_proc )
     msgctl( ipc_msg, IPC_RMID, NULL );
# endif

}/*ipc_terminate*/


void ipc_snd( tp, msg )
  long tp; /* I */
  char *msg; /* I */
/* ------------------------------
 * Global     : ipc_msg ipc_buff ipc_m
 * Parameters : type is the message type and msg is the text to be sended.
 * Comments   : Send as many characters from msg as possible.
 *              Do not wait if queue is full.
 *              types for messages should be placed at ipc/share.h
 *
 * ------------------------------ */
{
# ifdef SPARC

   ipc_m.mtype = tp;
   if ( msg != (char *)NULL )
       strncpy( ipc_m.mtext, msg, IPC_BUFF_SIZE );
   msgsnd(ipc_msg, &ipc_m, IPC_BUFF_SIZE, 0 );
# endif
}/*ipc_snd*/

long ipc_rcv( buff )
  char *buff; /* I-O */
/* ------------------------------
 * Returns    : type of message received. ( IPC_T_ERR on error )
 * Global     : ipc_msg ipc_buff ipc_m
 * Parameters : where_to_put_msg is a pointer to a character buffer
 *              there the contents of the message will be placed.
 * Comments   : Receive next message ( waits if none ).
 *              types for messages should be placed at ipc/share.h
 *
 * ------------------------------ */
{
# ifdef SPARC

   if ( msgrcv( ipc_msg, &ipc_m, IPC_BUFF_SIZE, 0L, 0 ) == -1 )
      return( IPC_T_ERR );
   if ( buff != (char*)NULL )
      strncpy(buff, ipc_m.mtext, IPC_BUFF_SIZE);
   return( ipc_m.mtype ); 
# endif
}/*ipc_rcv*/

/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
