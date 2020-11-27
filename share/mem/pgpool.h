/* ------------------------------
 *
 * File       : @(#) pgpool.h
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : Pages pool (header).
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Pool for avalaible memory pages.
 *
 * ------------------------------ */

# ifndef __PGPOOL_H
#   define __PGPOOL_H 1



/* ========== DEPENDENCIES ========== */

# include "../share.h"
# include "../list.h"

typedef char *pg_t;

extern list_list_tp pool;
extern size_t Page_Size;
extern char *pg_mcr_aux;

/* ========== END OF DEPENDENCIES ========== */

/* ========== MACRO DEFINITIONS ========== */

# define Pg_Get_Page()                \
    (  (List_IsEmpty(pool))           \
         ? (sys_getPage())            \
         : ((pg_t)List_ExtFirst(pool))) 

# define Pg_Put_Page(pg) \
    List_Insert(pool,pg)

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

void pg_init();
/* ------------------------------
 * Global     : Page_Size
 * Comments   : Initializes pgpool
 *
 * ------------------------------ */

/*
caddr_t Pg_Get_Page();
 * ------------------------------
 * MACRO !! 
 * Returns    : Pointer to page; -1 if error;
 * Global     : pgpool::pool
 * Comments   : Asks for a new page. -1 if error (usually, no mem. avalaible).
 *
 * ------------------------------ */

/*
void Pg_Put_Page( caddr_t pg );
 * ------------------------------
 * MACRO !! 
 * Global     : pgpool::pool
 * Comments   : Frees a page. 
 *
 * ------------------------------ */


pg_t sys_getPage();
/* ------------------------------
 * Returns    : Pointer to allocated page; (caddr_t)-1 if error.
 * Comments   : Ask the system for a memory page.
 *              For more information see SunOS manuals (r.4.1):
 *                - SunOS Reference Manual pp. 778.
 *                - System Services Overview, chapter 2.
 *
 * ------------------------------ */


/* ========== END OF PROTOTYPES ========== */



# endif

