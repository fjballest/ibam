/* --------------------------------
 *
 *    File: @(#)stckmacr.h   2.4
 *    Date: 4/22/91
 *    Module:  Stacks [ Macros ] ( stck)
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Provides macros for both an static and a dinamic 
 *              implementation of stacks.
 * 
 *
 * --------------------- */

# ifndef __STCKMACR_H
#  define __STCKMACR_H 1

extern void **stck__pt; /* auxiliar ptr used as local variable for macros */

 
#  define stck_top(st)          (grph_graphType)*((st).top-1)
#  define stck_pop(st)          (st).top--
#  define stck_isEmpty(st)      ((st).top==(st).dat)
#  define stck_move(st)         (st).top--
#  define stck_empty(st)        (st).top=(st).dat
#  define stck_push(st,el)      *((st).top++)=(void *)(el)

#  define stck_create(st,bf)  \
   (st).top=(st).dat=(void **)(bf)

# define stck_buffpt(st) \
   (st).dat

#  define stck_stackCpy(dst,src) \
   for((dst).top=(dst).dat,stck__pt=(src).dat;\
       stck__pt!=(src).top; \
       *((dst).top++)=*(stck__pt++)) \
     (*stck_copy_func)(*stck__pt)

#  define stck_stackInstall(dst,src)  \
   for((dst).top=(dst).dat,stck__pt=(src).dat;\
       stck__pt!=(src).top; \
       *((dst).top++)=*(stck__pt++))


#  define stck_stackApp(dst,src) \
   for(stck__pt=(src).dat; \
       stck__pt!=(src).top; \
       *((dst).top++)=*(stck__pt++)); \
       )\
     ;\
   (src).top=(src).dat

#  define stck_dtop( st )         (st)
#  define stck_disEmpty( st )     ((st)==NULL)
#  define stck_dcreate            NULL
#  define stck_dmove( st )        \
   ((st)=(void*)(*(void **)(st)))
#  define stck_dpop( st )         \
   ((st)=(void*)(*(void **)(st)))
# define stck_dtopp(st) \
   (stck__pt=(void**)(st),((st)=(void*)(*(void **)(st))),(void *)stck__pt)
#  define  stck_dempty( st )      (st)=NULL

# define stck_dpush(st,elem)\
         *((void **)elem)=(st);\
         (st)=(void *)(elem)
# endif


