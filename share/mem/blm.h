/* ------------------------------
 *
 * File       : @(#) blm.h
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : blm (Block Malloc; header)
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Generic memory block allocation
 * 
 * ------------------------------ */

# ifndef __BLM_H
#   define __BLM_H  1

/* ========== DEPENDENCIES ========== */

# include "pgpool.h"
# include "blmtypes.h"

extern blm_malloc_tp blm_malloc_l; /* blmalloc buffers                          */
extern int           blm_flags;    /* WARNING: Internal use ONLY                */
                                   /*   Use: Blm_Allowed() to see flags's value */
                                   /*        Blm_Deny() to reset BLM_ALLOW bit  */

/* ========== END OF DEPENDENCIES ========== */
/* ========== SYMBOL DEFINITIONS ========== */

# define BLM_ALLOW 0x1

/* ========== END OF SYMBOL DEFINITIONS ========== */

/* ========== MACRO DEFINITIONS ========== */

# ifdef malloc
#   undef malloc
# endif
# define malloc(s) ( (blm_malloc_l.next_nd+(s) > blm_malloc_l.pg_end)\
                        ? blm_malloc(s) \
                        : (blm_malloc_l.next_nd+=(s),blm_malloc_l.next_nd-(s)) \
                   )

# define Blm_Allowed() ( blm_flags & BLM_ALLOW)

# define Blm_Deny() (blm_flags &= ~BLM_ALLOW)

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

void blm_init();
/* ------------------------------
 * Global     : blm_malloc_l
 * Comments   : Initializes the generic block allocation list.
 *
 * ------------------------------ */

char *blm_malloc(/* size_t s */);
/* ------------------------------
 * Returns    : Pointer to an allocated memory block; NULL if error.
 * Global     : blm_malloc_l, flags;
 * Parameters : size of block to be allocated;
 * Comments   : Gets a new page and allocates a block of memory in it;
 *              returns NULL if there is no memory or if the "time for
 *              generic allocation" has gone.
 *
 * ------------------------------ */

/*
char *malloc( size_t s );
 * ------------------------------
 * MACRO !!
 * Returns    : pointer to an allocated block of memory; NULL if error.
 * Global     : gmm_blmalloc_l;
 * Parameters : size of block to be allocated;
 *
 * ------------------------------ */

/*
int Blm_Allowed(void);
 * ------------------------------
 * MACRO !!
 * Returns    : Non-zero if block malloc is allowed; zero otherwise.
 * Global     : blm_flags;
 *
 * ------------------------------ */

/*
int Blm_Deny(void);
 * ------------------------------
 * MACRO !!
 * Returns    : Modified blm_flags (BLM_ALLOW bit set to 0).
 * Global     : blm_flags;
 *
 * Comments   : Although block malloc may be denied, the memory requests
 *              are still served, until the actual page becomes full.
 *
 * ------------------------------ */

/* ========== END OF PROTOTYPES ========== */


# endif

