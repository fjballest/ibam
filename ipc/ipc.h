/* ------------------------------
 *
 * File       : @(#) ipc.h
 * Project    : Lbam
 * Date       : Nov-1991
 * Module     : ipc ( Messages ( via shared memory & signals )
 * Programmer : Dylan L. Hoffman & Francisco J. Ballesteros
 *
 * Comments   : Provides a fast message mechanism using shared memory
 *              segments and signals ( Inside the Lbam process group )
 * 
 * ------------------------------ */

# ifndef __IPC_H
#  define __IPC_H 1

extern int ipc_msg;

/* ========== DEPENDENCIES ========== */

# include "ipctype.h"

# include "share.h"

/* ========== END OF DEPENDENCIES ========== */




/* ========== PROTOTYPES ========== */


int ipc_init( /* int son */ );
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

void ipc_terminate( /* void */ );
/* ------------------------------
 * Global     : ipc_msg ipc_buff ipc_son_proc
 * Comments   : Terminates the shared memory segment used by this module.
 *
 * ------------------------------ */


void ipc_snd( /* long type, char *msg */ );
/* ------------------------------
 * Global     : ipc_msg ipc_buff
 * Parameters : type is the message type and msg is the text to be sended.
 * Comments   : Send as many characters from msg as possible.
 *              Do not wait if queue is full.
 *              types for messages should be placed at ipc/share.h
 *
 * ------------------------------ */


long ipc_rcv( /* char *where_to_put_msg */ );
/* ------------------------------
 * Returns    : type of message received.
 * Global     : ipc_msg ipc_buff
 * Parameters : where_to_put_msg is a pointer to a character buffer
 *              there the contents of the message will be placed.
 * Comments   : Receive next message ( waits if none ).
 *              types for messages should be placed at ipc/share.h
 *
 * ------------------------------ */



/* ========== END OF PROTOTYPES ========== */


# endif

