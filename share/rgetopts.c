/* ------------------------------
 *
 * File       : @(#)  rgetopts.c
 * Date       : Nov/91
 * Module     :  get_opt
 * Programmer : Francisco J. Ballesteros
 *
 * Comments   :  Provides a function opt_get that works like getopts but
 *               accepts "ab:[d:]" formats.
 * 
 * ------------------------------ */

/* ========== SYMBOL DEFINITIONS ========== */

# define NULL 0

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
# define OPT_NOPIPE 0x1

/* internal simbols */
# define OPT_STCK_LEN 5

/* ========== END OF SYMBOL DEFINITIONS ========== */

/* ========== GLOBAL VARIABLES DEFINITIONS ========== */


int    opt_nopipe; /* " - " Not allowed */
int    opt_errno;
char  *opt_fmt;                 /* format of options          */
char  *opt_stck[OPT_STCK_LEN];  /* stack of to-be-scanned fmts*/
int    opt_stck_top;
int    opt_argc;      /* argc                       */
char **opt_argv;      /* argv                       */
char  *opt_arg;       /* not scanned *argv          */
char  opt_err_msg[3][25] = {
   "  needs an argument.",
   "  is not an option. ",
   "  internal fault.   "
};
/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */

/* ========== FUNCTION IMPLEMENTATIONS ========== */

char *opt_pars( str )
  char *str;
/* ------------------------------
 * Returns    : pointer to next option letter.
 * Parameters : str is a pointer to a format string i.e.:"ab[d:]"
 * Comments   : if str is "ab" | "a:b" | "a:[...]" returns "b" 
 *
 * ------------------------------ */
{
  int  open_b = 0; /* number of open brackets */

  if ( str == NULL || *str == (char)0 || *str == '[' ||
                      *str == ']'     || *str == ':'    )
     return( NULL );


  str++;

  if ( *str == ':' ) {
     str++;
     if ( *str == (char) 0 )
        return( NULL );
  }

  if ( *str == '[' ) {
     for( open_b = 1, str++; open_b && *str != (char)0 ; str++ )
	switch( *str ){
	case '[':
	   open_b++;  
	   break;
	case ']':
	   open_b--;
	   break;
	}
     if( open_b || *str == (char) 0 )
	 return( NULL );

  }

  return( str );

}/*opt_pars*/

void opt_init( v, fmt, flags )
   char **v;
   char *fmt;
/* ------------------------------
 * Global     : opt_fmt opt_argc opt_argv opt_arg opt_stck opt_stck_top
 *              opt_nopipe opt_errno
 * Parameters : v is argv ( with program name ) fmt is a format.
 * Comments   : initializes get_opt()
 *
 * ------------------------------ */
{
  int ind;

  opt_fmt = fmt; /*  "d[fg[h:j]]g:" */
  opt_argc= 1;
  opt_argv= v+1;
  opt_arg = NULL;
  opt_stck_top = 0;
  opt_nopipe = flags & OPT_NOPIPE;
  opt_errno = 0;

  for ( ind = 0 ; ind < OPT_STCK_LEN ; ind++ )
     opt_stck[ind] = NULL;

}/*opt_init*/

int opt_get(  the_arg )
   char **the_arg;
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
{
   int result = 0;
   char *fmt = opt_fmt;

   /* Find next candidate */
   if ( opt_arg == NULL  && *opt_argv != NULL &&
        **opt_argv == '-' ) {
      opt_arg = (*opt_argv++)+1;
      opt_argc++;
   }

   if ( opt_arg != NULL )         /* I have candidate */
      if ( *opt_arg == (char)0 ){ /* option " - " */
         result = ((opt_nopipe) ? OPT_ERR : '-');
         opt_arg = NULL;
      } else if ( *opt_arg != '-' ) { /* Not "--" option */
         if ( opt_stck_top )          /* Format from stack */
            fmt = opt_stck[opt_stck_top];
         while ( !result && fmt != NULL && *fmt != (char)0 && *fmt != ']' )
            if ( *fmt == *opt_arg ) {
               result = *fmt++;
               if ( *++opt_arg == (char)0 )
                  opt_arg = NULL;
               if ( *fmt == ':' ) { /* take argument */
                  fmt++;
                  if ( opt_arg != NULL || *opt_argv == NULL){ /*err*/
                     if( the_arg != NULL ) *the_arg = NULL;
                     opt_errno = OPT_ENOARG;
                     *(opt_err_msg[opt_errno]) = (char)result;
                     result = OPT_ERR;
                  } else if ( the_arg != NULL )
                     *the_arg = *opt_argv++;
               }
               if ( *fmt == '[' ) /* next time: suboptions */
                 if ( ++opt_stck_top == OPT_STCK_LEN ) {
                    result = OPT_ERR;
                    opt_errno = OPT_ESTCKFLT;
                 } else
                   opt_stck[opt_stck_top] = fmt+1;

            } else /* Try with next option */
               fmt = opt_pars( fmt );

         if ( fmt && *fmt == ']' )
            opt_stck_top--;
         else if ( !result ) { /* false option */
            if ( the_arg != NULL )
               *the_arg = NULL;
            opt_errno = OPT_ENOPT;
            *(opt_err_msg[opt_errno]) = *opt_arg;
            result = OPT_ERR;
         }

      }



   return( result );

}/*opt_get*/

/* ========== FUNCTION IMPLEMENTATIONS ========== */
