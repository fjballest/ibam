/* --------------------------------
 *
 *    File: @(#)names.h 1.0
 *    Date: 4/22/91
 *    Module: Names (nm )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Buffers and methods for names. 
 * 
 *
 * --------------------- */ 
# ifndef __NAMES_H
#   define __NAMES_H 1

/*======================== DEPENDENCIES ==============================*/

# include <stdio.h>
# include <ctype.h>

/*======================== END OF DEPENDENCIES =======================*/
# define NAMES_BUFF_SIZE 2048

extern char nm_buff[];
extern char *nm_top;
extern char *nm_end;

char *nm_install( /*fp*/ );
/*------------------------------
 * Returns: Pointer to allocated space for a new name. NULL if error.
 * Globals: all of this module.
 * Comments: Read a name from fp and installs it in nm_buff.
 *------------------------------*/
# endif


