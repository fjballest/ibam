/* ------------------------------
 *
 * File       : @(#)  rgetopts.h
 * Date       : Nov/91
 * Module     :  get_opt
 * Programmer : Francisco J. Ballesteros
 *
 * Comments   :  Provides a function opt_get that works like getopts but
 *               accepts "ab:[d:]" formats.
 * 
 * ------------------------------ */

# ifndef __RGETOPTS_H
#  define __RGETOPTS_H 1

/* ========== SYMBOL DEFINITIONS ========== */

/* The ERROR option */
# define OPT_ERR      -1

/* error codes...       */
/* There is no argument */
# define OPT_ENOARG   0x0
/* Not an option */
# define OPT_ENOPT    0x1
/* Internal Stack fault */
# define OPT_ESTCKFLT  0x2


/* flags to opt_init() */
/* Do not allow " - " as an option. */
# define OPT_NOPIPE 0x1


extern int opt_errno;
extern int opt_argc;
extern char opt_err_msg[3][25];

/* ========== END OF SYMBOL DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

void opt_init( /* char **v, char *fmt, int flags */ );
/* ------------------------------
 * Global     : opt_fmt opt_argc opt_argv opt_arg opt_stck opt_stck_top
 *              opt_nopipe opt_errno
 * Parameters : v is argv ( with program name ) fmt is a format.
 * Comments   : initializes get_opt()
 *
 * ------------------------------ */

int opt_get(  /* char **the_arg */ );
/* ------------------------------
 * Returns    : The next (sub)option , OPT_ERR if error 0 if no more opts.
 *              if the_arg is non-null makes *the_arg to point to opt arg.  
 * Use        : while( ( opt = opt_get( &myarg)) != OPT_ERR && opt != 0 )
 *                  switch( opt ) ...
 * Global     : opt_fmt opt_argc opt_argv opt_arg opt_stck opt_stck_top
 *              opt_nopipe opt_errno
 * Comments   : When it has returned an option that has suboptions
 *              i.e. 'b' in "b[x]" the next time it will only scan for
 *              'b' suboptions ( returning 0 if no one ).
 *
 * ------------------------------ */


/* ========== END OF PROTOTYPES ========== */




# endif


