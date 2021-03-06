

/*======== CODE GENERATED BY mkgc ========*/

# ifdef DEBUG
# define gc_get_tsk() get_tsk()
# else
# define gc_get_tsk() \
   (gc_mcr_aux=( (!List_IsEmpty(gc_l.tsk))\
        ?( (*gc_f[0])(List_First(gc_l.tsk)),List_ExtFirst(gc_l.tsk) )\
        :(tsk_Malloc())\
   ),Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off))),gc_mcr_aux )
# endif

# ifdef DEBUG
# define gc_get_fun() get_fun()
# else
# define gc_get_fun() \
   (gc_mcr_aux=( (!List_IsEmpty(gc_l.fun))\
        ?( (*gc_f[1])(List_First(gc_l.fun)),List_ExtFirst(gc_l.fun) )\
        :(fun_Malloc())\
   ),Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off))),gc_mcr_aux )
# endif

# ifdef DEBUG
# define gc_get_num() get_num()
# else
# define gc_get_num() \
   (gc_mcr_aux=( (!List_IsEmpty(gc_l.num))\
        ?( (*gc_f[2])(List_First(gc_l.num)),List_ExtFirst(gc_l.num) )\
        :(num_Malloc())\
   ),Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off))),gc_mcr_aux )
# endif


#define gc_put_tsk(e) \
   Gc_Set_In(*((short *)(((char *)p)+gc_off))); \
   Gc_Set_Uncleaned(*((short *)(((char *)p)+gc_off))); \
   List_Insert(gc_l.tsk,(e))

#define gc_put_fun(e) \
   Gc_Set_In(*((short *)(((char *)p)+gc_off))); \
   Gc_Set_Uncleaned(*((short *)(((char *)p)+gc_off))); \
   List_Insert(gc_l.fun,(e))

#define gc_put_num(e) \
   Gc_Set_In(*((short *)(((char *)p)+gc_off))); \
   Gc_Set_Uncleaned(*((short *)(((char *)p)+gc_off))); \
   List_Insert(gc_l.num,(e))

/*******************
 * 
 *    Next comes the dependencies flags macros; their sintax is:
 *        GC_<father>_<son>_SetDep --> Sets the flag ON, indicating that
 *                                     really exists nodes with that dependency.
 *        GC_<father>_<son>_ClrDep --> Sets the flag OFF;
 * 
/*******************





/*===== END OF CODE GENERATED BY mkgc ====*/

