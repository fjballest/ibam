/* ------------------------------
 *
 * File       : @(#) gmm.c
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : gmm (implementation)
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : Graph Memory Manager
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <stdio.h>
# include <sys/types.h>
# include <sys/vadvise.h>
# include "../defs.h"
# include "../share.h"
# include "../list.h"
# include "pgpool.h"
# include "vadd.h"
# include "flags.h"
# include "blm.h"

# include "gmmdecl.h"   /* Prototypes */

/* ========== END OF DEPENDENCIES ========== */


/* ========== DEBUGGING MACRO DEFINITIONS ========== */
# ifdef DEBUG
#   define DEBUG_Init_Func(func) \
       printf("GMM: Init Function: %s\n",func)

#   define DEBUG_End_Func(func) \
       printf("GMM: End Function: %s\n\n",func)

# else
#   define DEBUG_Init_Func(func)
#   define DEBUG_End_Func(func)

# endif
/* ========== END OF DEBUGGING MACRO DEFINITIONS ========== */


/* ========== TYPE DEFINITIONS ========== */

# include "gmmtype.h"

/* ========== END OF TYPE DEFINITIONS ========== */

/* ========== GLOBAL VARIABLES DEFINITIONS ========== */

char   *gmm_mcr_aux, *gmm_mcr_aux2; /* aux. var. for macros */

int    false_func( p ) void *p; { return(FALSE); }
int    (*gmm_in_GC)() = false_func;              /* function to see if in GC */

/* ========== END OF GLOBAL VARIABLES DEFINITIONS ========== */


/* ========== MACRO DEFINITIONS ========== */

# include "gmmmacr.h"

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */

/* The following prototipes are used by functions generated at gmmimpl.c by
 * mkgmm. By convention we put here prototipes for each function that is not
 * generated.
 */
void local_init_gmm();
void gmm_compress();
void gmm_set_inGCf(  );
void gmm_set_cf( );

#include "gmmimpl.c"


void local_init_gmm()
/* ------------------------------
 * Global     : All
 * Comments   : Initializes the gmm, and informs the apging system that
 *              program it's going to manage the memory by itself (see
 *              SunOS Reference Manual pp.877(r.4.1) for details).
 *              It's called by gmm_init.
 *
 * ------------------------------ */
{
  DEBUG_Init_Func("local_init_gmm");

  vadvise(VA_ANOM);  /* *** ANORMAL USE OF MEMORY PAGES *** */

  vadd_set_exc_f(gmm_compress);  /* *** SET COMPRESSION ROUTINE *** */

  DEBUG_End_Func("local_init_gmm");
}/*local_init_gmm*/


void gmm_compress( l )
  int l;
/* ------------------------------
 * Global     : gmm_listVect, gmm_swapBuff;
 * Parameters : number of the list tha generates the call.
 * Comments   : Compresses the list of pages until some page becomes free.
 *
 * ------------------------------ */
{
/* *** Local Macros *** */
#   define incrGcn          \
      numGc--;              \
      gcn += actL->nd_size

#   define incrNd                              \
    if (numNd-1<0)   {                         \
         secPg=(char *)List_Next(secPg);       \
         nd=secPg+actL->nd_size;               \
         numNd=actL->nds_pg;                   \
    } else     (numNd--, nd+=actL->nd_size)    

#   define swapNds(nd1,nd2,list)                                                \
      swap_vadd((vadd_t *)(*(void**)(nd1)),((vadd_t *)(*(void**)(nd2))));       \
      memcpy(gmm_swapBuff[currPgL],nd1,list->nd_size);                          \
      memcpy(nd1,nd2,list->nd_size);                                            \
      memcpy(nd2,gmm_swapBuff[currPgL],list->nd_size);                          \
      List_Next(List_Prev((list_elem_ptr)((char*)(nd2)+1))) = ((char*)(nd2)+1); \
      List_Prev(List_Next((list_elem_ptr)((char*)(nd2)+1))) = ((char*)(nd2)+1)
         

/* *** End of Local Macros *** */


   static int currPgL  = 0;
          int firstPgL = currPgL;

   gmm_list_tp *actL;
   int         NotGotIt = TRUE; 
   char *gcn;     /* Ptr. to useful node to be swapped with a g.c. node */
   char *nd;      /* Ptr. to g.c. node to be swapped with a useful node */
   char *last;    /* Ptr. to last node in the actual list              */
   char *secPg;   /* Ptr. to page being filled                          */
   int numGc;     /* Number of nodes to be cleaned (swapped to g.c. node) */
   int numNd;     /* Number of nodes left in actual page                  */

   DEBUG_Init_Func("gmm_compress");
 
   /* Compress until there is a reusable page, or fails */
   do {
      if (l==currPgL)
         currPgL = (currPgL+1) % GMM_NUM_LIST;

      actL = gmm_listVect[currPgL];
      if (!List_IsEmpty(actL->data)) {
         gcn = (char *)actL->data + actL->first_off;
         last = actL->next_nd;
         nd = secPg = (char *)List_Next(actL->data) + actL->first_off;
         if (actL->data == actL->pg) { /* JUST ONE PAGE */
            numGc = actL->nds_pg-actL->nodes;
            numNd = 0;
         } else {
            numGc = numNd = actL->nds_pg;
         }

         do {
            while((*gmm_in_GC)(gcn) && !numGc) 
               incrGcn;
            if (!(*gmm_in_GC)(gcn)) {
               while ( !(*gmm_in_GC)(nd) && nd!=last )
                  incrNd;
               if (nd!=last)
                  swapNds(gcn,nd,actL);
            }
            incrGcn;
         } while (!numGc && (*gmm_in_GC)(gcn) && nd!=last);
         NotGotIt = numGc == 0;
         
      } /* if */
      
      if (NotGotIt)
         currPgL = (currPgL+1) % GMM_NUM_LIST;

   } while((currPgL != firstPgL) && NotGotIt );

   if (!NotGotIt) {   /* Cleans the reusable page (pointed by actL)  */
                      /*   and gives it to the pool.                 */
      int ind;
      nd = (char *)actL->data + actL->first_off 
           + sizeof(char *);  /* Takes off the first node ret. pointer */
      for ( ind=0; ind < actL->nds_pg; ind++) {
         (*gmm_cf[currPgL])(nd);
         free_vadd( *((char *)(nd)-1) );
      }
      List_Extract(actL);
      List_Insert(pool,(list_elem_ptr)actL);
   }

   DEBUG_End_Func("gmm_compress");
} /* compress */



void gmm_set_inGCf( f )
  int (*f)(/* void * */);
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
{
   gmm_in_GC = f;

}/*gmm_set_inGCf*/

void gmm_set_cf( l, f)
   int l;
   gmm_cf_tp f;
/* ------------------------------
 * Use        :  gmm_set_cf( a_list, my_func );
 * Global     :  gmm_cf
 * Parameters :  f is a pointer to a function.
 *               *f will be called with a void * as parameter. It must
 *               clean the node pointed by the parameter ( if not done )   
 * Comments   :  If no f is set then gmm assumes that no free function
 *               exists.
 *
 * ------------------------------ */
{
   gmm_cf[l] = f;   

}/*gmm_set_cf*/



/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */



