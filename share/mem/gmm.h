/* ------------------------------
 *
 * File       : @(#) gmm.h
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : gmm (header)
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Graph Memory Manager
 * 
 * ------------------------------ */

#ifndef __GMM_H
#  define __GMM_H 1

/* ========== DEPENDENCIES ========== */

# include "../share.h"
# include "../list.h"
# include "gmmtype.h"
# include "gmmdecl.h"
# include "gmmmacr.h"
# include "flags.h"

extern char *gmm_mcr_aux, *gmm_mcr_aux2;           /* aux. var. for macros */

/* ========== END OF DEPENDENCIES ========== */

/* ========== MACRO DEFINITIONS ========== */

# include "gmmmacr.h"

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

void local_init_gmm();
/* ------------------------------
 * Global     : All
 * Comments   : Initializes the gmm, and informs the apging system that
 *              program it's going to manage the memory by itself (see
 *              SunOS Reference Manual pp.877(r.4.1) for details).
 *              It's called by gmm_init.
 *
 * ------------------------------ */

void gmm_set_inGCf( /* int (*f)(void *) */);
/* ------------------------------
 * Use        :  gmm_set_inGC( my_func );
 * Global     :  gmm_in_GC
 * Parameters :  f is a pointer to a function returning int.
 *               *f will be called with a void * as parameter. It must
 *               return non-zero if chunk of memory pointed by the param.
 *               is reusable.
 * Comments   :  If no f is set then gmm assumes that no chunk of
 *               memory is reusable.
 *
 * ------------------------------ */

void gmm_set_cf( /* list_id, int (*f)(void *) */);
/* ------------------------------
 * Use        :  gmm_set_cf( a_list, my_func );
 * Global     :  gmm_cf
 * Parameters :  f is a pointer to a function.
 *               *f will be called with a void * as parameter. It must
 *               clean te node pointed by the parameter ( if not done )   
 * Comments   :  If no f is set then gmm assumes that no free function
 *               exists.
 *
 * ------------------------------ */





void gmm_compress(/* int list */); /* INTERNAL USE ONLY */

/* ========== END OF PROTOTYPES ========== */



# endif



