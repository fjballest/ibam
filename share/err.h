/* ------------------------------
 *
 * File       : @(#) err.h
 * Project    : Lbam
 * Date       : OCt/91
 * Module     : err (error )
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Gives a little error management
 * 
 * ------------------------------ */


# ifndef __ERR_H
#   define __ERR_H 1

extern char *err_prg_name;

/* ========== PROTOTYPES ========== */


void err_fix_prg_name( /* char *n */ );
/* ------------------------------
 * Global     : err_prg_name;
 * Parameters : the name for a program.
 * Comments   : Fix the program name to be used in future err msgs.
 *              The string IS NOT copied.
 *
 * ------------------------------ */

void err_show( /* char *m */ );
/* ------------------------------
 * Global     : err_prg_name
 * Parameters : the message to be said.
 * Comments   : dumps "<name_of_program> : <msg>" to stderr.
 *              If program name has not been fixed then only msg is dumped.
 *
 * ------------------------------ */

void err_fatal( /* char *msg */ );
/* ------------------------------
 * Returns    : Do you really think it returns ?
 * Global     : err_prg_name
 * Parameters : the message to be said.
 * Comments   : dumps "<name_of_program> : <msg>" to stderr.
 *              If program name has not been fixed then only msg is dumped.
 *              Exits after message is dumped.
 * ------------------------------ */

void err_sys_show( /* void */ );
/* ------------------------------
 * Comments   : dumps  the message for last system call errno
 *
 * ------------------------------ */

/* ========== END OF PROTOTYPES ========== */


# endif


