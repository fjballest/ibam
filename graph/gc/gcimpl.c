

/*======== CODE GENERATED BY mkgc ========*/


/*******************
 * 
 *    Next comes the dependencies flags; their sintax is:
 *        gc_<father>_<son>_dep
 * 
 *******************/



gc_f_type gc_f[] = {NULL,NULL,NULL};


# ifdef DEBUG
get_tsk() 
{
   if(!List_IsEmpty(gc_l.tsk)) {
       (*gc_f[0])(List_First(gc_l.tsk));
       gc_mcr_aux=List_ExtFirst(gc_l.tsk);
   } else {
        gc_mcr_aux=tsk_Malloc();
   }
   Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off)));
   return ( gc_mcr_aux );
} /* get_tsk */
# endif

# ifdef DEBUG
get_fun() 
{
   if(!List_IsEmpty(gc_l.fun)) {
       (*gc_f[1])(List_First(gc_l.fun));
       gc_mcr_aux=List_ExtFirst(gc_l.fun);
   } else {
        gc_mcr_aux=fun_Malloc();
   }
   Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off)));
   return ( gc_mcr_aux );
} /* get_fun */
# endif

# ifdef DEBUG
get_num() 
{
   if(!List_IsEmpty(gc_l.num)) {
       (*gc_f[2])(List_First(gc_l.num));
       gc_mcr_aux=List_ExtFirst(gc_l.num);
   } else {
        gc_mcr_aux=num_Malloc();
   }
   Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off)));
   return ( gc_mcr_aux );
} /* get_num */
# endif

void gc_tsk_cf( p )
  void *p;
/* ------------------------------
 * Global     : gc_l.
 * Comments   : Releases p from GC and cleans p 
 *
 * ------------------------------ */

{
  DEBUG_Init_Func("gc_tsk_cf");

 if (gc_f[0] != NULL && !(*((short*)(((char*)p)+gc_off)) & GC_CLEANED)) 
    (*gc_f[0])(p); 
 List_Extract(p);

 DEBUG_End_Func("gc_tsk_cf");
} /*gc_tsk_cf*/

void gc_fun_cf( p )
  void *p;
/* ------------------------------
 * Global     : gc_l.
 * Comments   : Releases p from GC and cleans p 
 *
 * ------------------------------ */

{
  DEBUG_Init_Func("gc_fun_cf");

 if (gc_f[1] != NULL && !(*((short*)(((char*)p)+gc_off)) & GC_CLEANED)) 
    (*gc_f[1])(p); 
 List_Extract(p);

 DEBUG_End_Func("gc_fun_cf");
} /*gc_fun_cf*/

void gc_num_cf( p )
  void *p;
/* ------------------------------
 * Global     : gc_l.
 * Comments   : Releases p from GC and cleans p 
 *
 * ------------------------------ */

{
  DEBUG_Init_Func("gc_num_cf");

 if (gc_f[2] != NULL && !(*((short*)(((char*)p)+gc_off)) & GC_CLEANED)) 
    (*gc_f[2])(p); 
 List_Extract(p);

 DEBUG_End_Func("gc_num_cf");
} /*gc_num_cf*/

void gc_init(  )
/* ------------------------------
 * Global     : gc_l.
 * Comments   : Initializes GC 
 *
 * ------------------------------ */

{
 DEBUG_Init_Func("gc_init");

 gmm_set_inGCf(gc_inGC);

 gmm_set_cf(0,gc_tsk_cf);
 gc_f[0]=gc_null;

 gmm_set_cf(1,gc_fun_cf);
 gc_f[1]=gc_null;

 gmm_set_cf(2,gc_num_cf);
 gc_f[2]=gc_null;


 DEBUG_End_Func("gc_init");

} /*gc_init*/



/*===== END OF CODE GENERATED BY mkgc ====*/

