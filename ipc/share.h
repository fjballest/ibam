/* ------------------------------
 *
 * File       : @(#) share.h
 * Project    : Lbam
 * Date       : Nov-1991
 * Module     : ipc ( Messages ( via shared memory & signals )
 * Programmer : Dylan L. Hoffman & Francisco J. Ballesteros
 *
 * Comments   : The shared definitions about IPC go here.
 * 
 * ------------------------------ */

# ifndef __IPC_SHARE_H
#  define __IPC_SHARE_H 1

/* ========== SYMBOL DEFINITIONS ========== */

/**** Tags for message types along Lbam processes ****/

/* THIS IS A RESERVED TAG */
# define IPC_T_ERR ((long)(-1))

/* End of execution */
# define IPC_T_END        666L

# define IPC_MAX_TAG 8

/* A page of memory to the pool */
# define IPC_T_POOL_PUT   1L  
/* A page of memory from the pool */
# define IPC_T_POOL_GET   2L
/* A page to/from the vadd list */
# define IPC_T_VADD_PUT   3L
# define IPC_T_VADD_GET   4L
/* A compression performed/failed */
# define IPC_T_COMPR      5L
# define IPC_T_COMPR_FAIL 6L

/* A page is attached ( detached ) from a list of gmm */
# define IPC_T_GMM_PG_PUT 7L
# define IPC_T_GMM_PG_GET 8L


/**** End of Tags for message types  ****/


/* ========== END OF SYMBOL DEFINITIONS ========== */


# endif


