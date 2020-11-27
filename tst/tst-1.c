/* ------------------------------
 *
 * File       : @(#)  tst-1.c
 * Project    :  Lbam.
 * Date       :  Nov-91
 * Programmer : Dylan L. Hoffman & Francisco J. Ballesteros
 *
 * Comments   :  test 1 for gmm.
 * 
 * ------------------------------ */


/* ========== DEPENDENCIES ========== */

# include <stdio.h>
# include "../share/share.h"
# include "../share/mem/vadd.h"
# include "../share/mem/gmm.h"
# include "../share/mem/blm.h"
# include "../graph/gc/gc.h"

/* ========== END OF DEPENDENCIES ========== */

/* ========== SYMBOL DEFINITIONS ========== */

/* Sizes for nodes ... */
# define T_SIZE 100
# define F_SIZE 50
# define N_SIZE 25

/* Test Magnitude ... */

# define RQ_T 10
# define RQ_F 10
# define RQ_N 10


/* ========== END OF SYMBOL DEFINITIONS ========== */


do_test()
{
  void *tsks[RQ_T];
  void *funs[RQ_F];
  void *nums[RQ_N];

  int i;

  Blm_Deny();

  for ( i = 0; i < RQ_T ; i++ )
    tsks[i] = gc_get_tsk();
  for ( i = 0; i < RQ_F ; i++ )
    funs[i] = gc_get_fun();
  for ( i = 0; i < RQ_N ; i++ )
    nums[i] = gc_get_num();

}/*do_test*/

int main() 
{

  gmm_init( T_SIZE, F_SIZE, N_SIZE );
  gc_init();

  do_test();

  return( FALSE );

}/*main*/


