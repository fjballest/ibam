/* ------------------------------
 *
 * File       : @(#) ipctype.c
 * Project    : Lbam
 * Date       : Nov-1991
 * Module     : ipc ( Messages ( via shared memory & signals )
 * Programmer : Dylan L. Hoffman & Francisco J. Ballesteros
 *
 * Comments   : Provides a fast message mechanism using shared memory
 *              segments and signals ( Inside the Lbam process group )
 * 
 * ------------------------------ */

# ifndef __IPCTYPE_H
#  define __IPCTYPE_H 1

/* ========== SYMBOL DEFINITIONS ========== */

# define IPC_BUFF_SIZE  5

/* ========== END OF SYMBOL DEFINITIONS ========== */

/* ========== TYPE DEFINITIONS ========== */


typedef struct {
   long mtype;
   char mtext[IPC_BUFF_SIZE];
} ipc_buff_tp;

/* ========== END OF TYPE DEFINITIONS ========== */

# endif


