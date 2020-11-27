/* ------------------------------
 *
 * File       : @(#) pgpool.c
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : Pages pool
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Pool for avalaible memory pages, and functions 
 *              for getting new pages.
 *
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */
# include <stdio.h>
# include <errno.h>

# include "../defs.h"
# include "../list.h"
# include "../share.h"

# ifdef SPARC
#   include <fcntl.h>
#   include <sys/types.h>
#   include <sys/mman.h>
#   include <sys/vadvise.h>
# endif

/* ========== END OF DEPENDENCIES ========== */


/* ========== DEBUGGING MACRO DEFINITIONS ========== */
# ifdef DEBUG
#   define DEBUG_Init_Func(func) \
       printf("PGPOOL: Init Function: %s\n",func)

#   define DEBUG_End_Func(func) \
       printf("PGPOOL: End Function: %s\n\n",func)

# else
#   define DEBUG_Init_Func(func)
#   define DEBUG_End_Func(func)

# endif
/* ========== END OF DEBUGGING MACRO DEFINITIONS ========== */


/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

typedef char *pg_t;
size_t Page_Size;
list_list_tp pool;
char *pg_mcr_aux;

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */

/* ========== FUNCTION IMPLEMENTATIONS ========== */


# ifdef SPARC

void pg_init()
/* ------------------------------
 * Global     : Page_Size
 * Comments   : Initializes pgpool
 *
 * ------------------------------ */
{
  DEBUG_Init_Func("pg_init");

  Page_Size = getpagesize();
# ifdef DEBUG
  printf("\tSystem page size: %d\n",Page_Size);
# endif
  pool = NULL;

  DEBUG_End_Func("pg_init");
} /* pg_init */

pg_t sys_getPage()
/* ------------------------------
 * Returns    : Pointer to allocated page; (caddr_t)-1 if error.
 * Comments   : Ask the system for a memory page.
 *              For more information see SunOS manuals (r.4.1):
 *                - SunOS Reference Manual pp. 778.
 *                - System Services Overview, chapter 2.
 *
 * ------------------------------ */
{
  int  fd;
  pg_t new_page;
# ifdef DEBUG
  static unsigned n_pg=0;  /* Number of pages taken */
# endif

  DEBUG_Init_Func("sys_getPage");

  if ((fd=open("/dev/zero",O_RDWR)) == -1) {
# ifdef DEBUG
     err_show(" Cannot open /dev/zero.");
# endif
     return((pg_t)-1);
   }
  new_page = mmap(0,Page_Size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  (void)close(fd);
# ifdef DEBUG
  printf("\tsys_getPage ->[0x%x] (number %u)\n",(int)new_page,++n_pg);
  printf("\tPage_Size used: %d\n",Page_Size);
  printf("\tError number: %d\n",errno);
  DEBUG_End_Func("sys_getPage");
# endif
  return((pg_t)new_page);

} /* sys_getPage */

# else

void pg_init()
/* ------------------------------
 * Global     : Page_Size
 * Comments   : Initializes pgpool
 *
 * ------------------------------ */
{
  Page_Size = 0;
}

pg_t sys_getPage()
/* ------------------------------
 * Returns    : Pointer to allocated page; (caddr_t)-1 if error.
 * Comments   : Ask the system for a memory page.
 *              For more information see SunOS manuals (r.4.1):
 *                - SunOS Reference Manual pp. 778.
 *                - System Services Overview, chapter 2.
 *
 * ------------------------------ */
{
  return( (pg_t) -1 );
}

# endif

/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */
