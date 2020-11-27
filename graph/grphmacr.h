

# ifndef __GRPHMACR_H
#  define __GRPHMACR_H 1


/*=================== DEPENDENCIES ===============================*/

/* YOU MUST include the file <string.h>, it's not included here
 * to avoid multiple inclusion.
 */

# include "grphtype.h"

/*=================== END OF DEPENDENCIES ========================*/

# define grph_getType(n) \
  (n)->type

# define grph_getConst(n) \
   (n)->inf.const

# define grph_getConstNd(v) \
   grph_cts[v+2]

# define grph_deref(n) \
   while((n)->type==GRPH_VARIABLE|| \
         ((n)->type==GRPH_TASK&&   \
          ((n)->tsk_sts==GRPH_SEMIDORMANT|| \
           (n)->tsk_sts==GRPH_EVALUATED)) )\
      if((n)->type==GRPH_VARIABLE) \
         (n)=(n)->inf.var.reference; \
      else if((n)->tsk_sts==GRPH_EVALUATED&&!stck_isEmpty((n)->tsk_stk)) \
         (n)=stck_top((n)->tsk_stk); \
      else (n)=(grph_graphType)(n)->tsk_res

# define grph_bind(v,n) \
   (v)->type=GRPH_VARIABLE; \
   (v)->inf.var.reference=(n); \
   grph_incRC(n)

   

# define grph_free(v) \
   grph_decRC((v)->inf.var.reference); \
   (v)->type=GRPH_FREE_VAR

# define grph_setNum(nd,n) \
   (nd)->inf.num.number=(n)


# define grph_getNum(n) \
   (n)->inf.num.number

# define grph_setPConstr(n,c) \
   (n)->inf.pterm.constructor=(c)

# define grph_setConstr(n,c) \
  (n)->inf.term.constructor=(c)

# define grph_getPConstr(n) \
  (n)->inf.pterm.constructor

# define grph_getConstr(n) \
  (n)->inf.term.constructor

# define grph_setPTrmNArgs(nd,n) \
  (nd)->inf.pterm.numberArgs=(n)

# define grph_setTrmNArgs(nd,n) \
  (nd)->inf.term.numberArgs=(n)

# define grph_getPTrmNArgs(n) \
  (n)->inf.pterm.numberArgs

# define grph_getTrmNArgs(n) \
  (n)->inf.term.numberArgs

# define grph_setPTrmArg(t,i,a) \
  *(&((t)->inf.pterm.args)+(i))=(a)

# define grph_getPTrmAArgs(n) \
   (n)->inf.pterm.actualArgs

# define grph_setTrmArg(t,i,a) \
  *((grph_graphType *)&((t)->inf.term.args)+(i))=(a)

# define grph_getPTrmArg(t,i) \
  *((grph_graphType *)&((t)->inf.pterm.args)+(i))
  
# define grph_getTrmArg(t,i) \
  *((grph_graphType *)&((t)->inf.term.args)+(i))

# define grph_cpTrmArgs(s,d,n) \
  memcpy((void **)&(d)->inf.term.args,s,(size_t)(n))

# define grph_cpPTrmArgs(s,d,n) \
  memcpy((void **)&(d)->inf.pterm.args,s,(size_t)(n))

# define grph_setTskNArgs(nd,n) \
  (nd)->tsk_nargs=(n)

# define grph_getTskNArgs(nd) \
  (nd)->tsk_nargs

# define grph_cpTskArgs(s,d,n) \
   memcpy((void **)(d)->tsk_arg,s,(size_t)(n))

# define grph_getTskArg(t,i) \
  *((grph_graphType *)((t)->tsk_arg)+(i))

# define grph_downTsk(t)  \
  (t)->tsk_sts=GRPH_SEMIDORMANT;\
  gc_put_ae((t)->inf.task.st_u)

# define grph_activeTsk(t)  \
  (t)->tsk_sts=GRPH_ACTIVE;\
  (t)->inf.task.st_u=grph_newAE()

# define grph_setTskSts(t,c) \
  (t)->tsk_sts=(c)

# define grph_getTskSts(t) \
  (t)->tsk_sts

# define grph_setTskCA(t,c) \
  (t)->tsk_cdAddr=(c)

# define grph_getTskCA(t) \
  (t)->tsk_cdAddr

# define grph_getTskNVars(t) \
  (t)->tsk_nlv

# define grph_setTskNVars(t,n) \
  (t)->tsk_nlv=(n)

# define grph_getTskVar(t,i) \
  (grph_graphType)((t)->tsk_var+i)

# define grph_clrStck(t) \
  stck_empty((t)->stack)

# define grph_isEmptyStck(t) \
  stck_isEmpty((t)->stack)

# define grph_pushStck(t,n) \
  stck_push((t)->stack),(n))

# define grph_topStck(t) \
  stck_top((t)->stack)

# define grph_popStck(t) \
  stck_pop((t)->stack)

# define grph_clrTrl(t) \
  (t)->trail=(t)->trl_bottom=NULL

# define grph_isEmptyTrl(t) \
  ((t)->trail==NULL)

# define grph_pushTrl(t,n) \
  if((t)->trl_bottom==NULL) \
    (t)->trl_bottom=(n); \
  (n)->inf.var.trail_link=(t)->trail; \
  (t)->trail=(n)

# define grph_appTrl(d,s) \
  if((d)->trl_bottom!=NULL) \
    (d)->trl_bottom->inf.var.trail_link=(s)->trail; \
  else (d)->trail=(s)->trail; \
 (d)->trl_bottom=(s)->trl_bottom; \
 (s)->trail=(s)->trl_bottom=NULL

# define grph_setPC(t,n)  \
  (t)->pc=(n)

# define grph_getPC(t) \
  (t)->pc

# define grph_incPC(t) \
  (t)->pc++

# define grph_decNAE(t) \
  (t)->nae--

# define grph_incNAE(t) \
  (t)->nae++

# define grph_isZeroNAE(t) \
  ((t)->nae==0)


# define grph_setEvm(n,m) \
  (n)->evm=(m)

# define grph_getEvm(n)  \
  (n)->evm

# define grph_isArg(n)  \
  (n)->evm & GRPH_ARG_EVM

# define grph_isBdy(n)  \
  (n)->evm & GRPH_BDY_EVM

# define grph_setBlb(n,l) \
  (n)->ae_blb=(l)

# define grph_getBlb(n)  \
  (n)->ae_blb

# define grph_getSPC(n)  \
  (n)->ae_spc

# define grph_setBtAd(n,a) \
  (n)->bt_ad=(a)

# define grph_getBtAd(n) \
  (n)->bt_ad

# define grph_setLdptr(n,p) \
  (n)->ldpt=(p)

# define grph_getLdptr(n) \
  (n)->ldpt

# define grph_setBptr(n,p) \
  (n)->bpt=(p)

# define grph_getBptr(n) \
  (n)->bpt

# define grph_setFptr(n,p) \
  (n)->fpt=(p)

# define grph_getFptr(n) \
  (n)->fpt

# define grph_decRC(n) \
  if((n)->node_RC!=GRPH_CT_RC)(n)->node_RC++; \
  if( !(n)->node_RC ) grph_disposeNd(n)

# define grph_incRC(n) \
  if((n)->node_RC!=GRPH_CT_RC)(n)->node_RC++

# define grph_getTskVal(n) \
   (((n)->tsk_sts==GRPH_SEMIDORMANT)?((grph_graphType)(n)->tsk_res):\
     ((grph_graphType)stck_top((n)->tsk_stk)))

# define grph_getFunCA(n) \
  (n)->fun_cdAddr

# define grph_getFunAArgs(n) \
  (n)->fun_aargs

# define grph_getFunMArgs(n) \
  (n)->fun_nargs-(n)->fun_aargs

# define grph_cpFunArgs(s,d,n) \
  memcpy((void **)&(d)->fun_args,s,(size_t)(n))

# define grph_getFunArg(n,a) \
  *((grph_graphType *)(&(n)->fun_args)+(a))

# define grph_addFunArg(n,a) \
  *((grph_graphType *)(&(n)->fun_args)+((n)->fun_aargs++))=(a)

# define grph_getFunNVars(n) \
  (n)->fun_nlv



# endif



