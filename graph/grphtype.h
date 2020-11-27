/* --------------------------------
 *
 *    File: @(#)grphtype.h   1.0
 *    Date: 4/22/91
 *    Module:  Graph [ Types ] ( grph )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Graph type declarations
 * 
 *
 * --------------------- */ 


#ifndef __GRPHTYPE_H
# define __GRPHTYPE_H

/* ======= IMPLICIT DEPENDENCIES =========================*/
/* 
 *  You MUST include the shared files stck.h & share.h
 *  BEFORE include this one.
 */
/* ======= END OF IMPLICIT DEPENDENCIES ==================*/

/*======== Graph Node Types ==============================*/
# define GRPH_NODE_TYPES 9 

# define GRPH_CONSTANT 0x0
# define GRPH_VARIABLE 0x1
# define GRPH_NUMBER   0x2
# define GRPH_TERM     0x3
# define GRPH_TASK     0x4
# define GRPH_FUNCTION 0x5
# define GRPH_FREE_VAR 0x6
# define GRPH_PTERM    0x7
/* miscellaneous nodes... */
# define GRPH_AE_S     0x8
/* Node is in GC */
# define GRPH_IN_GC      0x10
/* Node is in GC but gc-cleaner-function has been aplied yet */
# define GRPH_GC_CLEANED 0x20
/*======== Graph Task node constants =====================*/


/* Reference Counter value in variable nodes living into task nodes*/
# define GRPH_CT_RC -1

/* Status class */
# define GRPH_DORMANT 0
# define GRPH_ACTIVE 1
# define GRPH_EVALUATED 2
# define GRPH_SEMIDORMANT 3

/* Evaluation class */
# define GRPH_ARG_EVM   0x1
# define GRPH_BDY_EVM   0x2
# define GRPH_HNF_EVM   0x4
# define GRPH_NF_EVM    0x8
# define GRPH_FRET_EVM  0x10
# define GRPH_NFRET_EVM 0x20
# define GRPH_PFC_EVM   0x40
# define GRPH_NPFC_EVM  0x80

/* Header of nodes ... */
/* Usually the alternatives of the following union are of same size, but
 * writting down the union you're sure they are !!
 */
union grph_rcDbgUnion {   
    void *gc_link;  /* used when r.i.p. on  gb. clct. */
    struct { int RC; unsigned v_number; } rcv; /* used when alive */
};
# define node_RC    rd_u.rcv.RC
# define node_vnum  rd_u.rcv.v_number
# define node_gclnk rd_u.gc_link


/* ====== Nodes ==========================================*/

/* GRPH_CONSTANT... */
typedef int grph_constNodeType;

# define GRPH_TRUE -2
# define GRPH_FALSE -1

/* GRPH_VARIABLE, GRPH_FREE_VAR... */

/* The below code seems strange but it is for simplicity:
   When using var nodes living into task nodes...         */

typedef struct grph_varNodeStruct{
    struct grph_nodeStruct *trail_link;
    struct grph_nodeStruct *reference;
}grph_varNodeType;

union grph_locVarUnion{
   grph_varNodeType var;
};

struct grph_locVarStruct{     /* The analog to nodeType */
   union grph_rcDbgUnion rd_u;
   int type;
   union grph_locVarUnion inf;
};

typedef struct grph_locVarStruct grph_locVarType;   

/* GRPH_NUMBER... */
typedef struct grph_numbNodeStruct{
#ifdef LONG
    long int number;
#else
    int number;
#endif
}grph_numbNodeType;

/*GRPH_TERM GRPH_PTERM... */
typedef struct grph_ptermNodeStruct{
    int constructor;
    int numberArgs;
    int actualArgs;
    struct grphNodeStruct *args; /* Only space for the first */
}grph_ptermNodeType;

typedef struct grph_termNodeStruct{
    int constructor;
    int numberArgs;
    struct grphNodeStruct *args; /* Only space for the first */
}grph_termNodeType;

/* GRPH_TASK... Hours of enjoy for your family! */

union evmUnion { /* evaluation mode union */
   unsigned blk_lb; /* Argument mode */
   struct {
      unsigned spc;
      stck_stackType sstack;
   } bdy_st; /* body     */
};


struct a_e_struct { /* active / evaluated info */
    struct grph_nodeStruct *trail;
    struct grph_nodeStruct *trl_bottom;
    unsigned pc;
    unsigned bt_ad;
    int nae; /* number of args evltd.*/
    stck_stackType stack;
    struct grph_nodeStruct *fpt;
    struct grph_nodeStruct *bpt;
    struct grph_nodeStruct *ldpt;
    int evm;
    union evmUnion evm_u;
};

/* Shorthands to a_e_struct node fields... */

# define ae_spc  evm_u.bdy_st.spc
# define ae_sstk evm_u.bdy_st.sstack
# define ae_blb  evm_u.blk_lb

/* Shorthands to task node fields ... */

# define tsk_cdAddr inf.task.code_ad
# define tsk_nargs  inf.task.numberArgs
# define tsk_sts    inf.task.status
# define tsk_arg    inf.task.arg
# define tsk_nlv    inf.task.numberLocVars
# define tsk_nae    inf.task.st_u->nae
# define tsk_pc     inf.task.st_u->pc
# define tsk_stk    inf.task.st_u->stack
# define tsk_fpt    inf.task.st_u->fpt
# define tsk_trl    inf.task.st_u->trail
# define tsk_trl_b  ind.task.st_u->trl_bottom
# define tsk_bpt    inf.task.st_u->bpt
# define tsk_ldpt   inf.task.st_u->ldpt
# define tsk_btAddr inf.task.st_u->bt_ad
# define tsk_evm    inf.task.st_u->evm
# define tsk_spc    inf.task.st_u->evm_u.bdy_st.spc
# define tsk_sstk   inf.task.st_u->evm_u.bdy_st.sstack
# define tsk_blb    inf.task.st_u->evm_u.blk_lb
# define tsk_res    inf.task.st_u
# define tsk_ae     inf.task.st_u
# define tsk_arg    inf.task.arg
# define tsk_var    inf.task.var

/* ---- NOTE : IMPORTANT TO USE TASK NODES
 *   st_u in an active/evaluated mode points to a_e_struct, in
 *   a dormant/semidormant mode points to result: A dormant task
 *   node can be expanded without time loss just giving an
 *   a_e_struct to this pointer.
 *
 *   the evm_u has information about body evaluated tasks in
 *   bdy_st, the arg. evaluated tasks have blk_lb instead.
 */

typedef struct grph_taskNodeStruct{
    unsigned code_ad;
    int numberArgs;
    int numberLocVars;
    int status;
    struct a_e_struct *st_u;   
    struct grph_nodeType **arg;
    grph_locVarType *var; 
}grph_taskNodeType;            
/* After this node, space MUST be allocated to hold arguments 
 * ( struct grph_nodeStruct *), locVars ( The node, not the pointers ).
 */

/* GRPH_FUNCTION... */

/* Shorthands to task node fields ... */
# define fun_nargs inf.func.numberArgs
# define fun_aargs inf.func.actualArgs
# define fun_nlv   inf.func.numberLocVars
# define fun_cdAddr inf.func.codeAddress
# define fun_args   inf.func.arg

typedef struct grph_funcNodeStruct{
    int numberArgs;
    int actualArgs;
    int numberLocVars;
    int codeAddress;
    struct grph_nodeStruct *arg; /* first arg. */
}grph_funcNodeType;
/* After this node, space MUST be allocated to hold arguments */


/* ========= Here comes the node ... =========================*/

/* NOTE : It's suggested that vars & numbers nodes have the same
 *        size ( external (& internal) fragmentation ), the same
 *        note applies to term & pterm nodes, 
 *        and to task & func nodes.
 *        The structs a_e_struct's needed for task nodes can be
 *        taken with size of term nodes.
 *        You allocate constants once at all and have only three 
 *        possible sizes for nodes: Feel better ? 
 */
union grph_nodeUnion{
    grph_funcNodeType func;
    grph_constNodeType cons;
    grph_varNodeType var;
    grph_numbNodeType numb;
    grph_termNodeType term;
    grph_ptermNodeType pterm;
    grph_taskNodeType task;
};


struct grph_nodeStruct{
    union grph_rcDbgUnion rd_u;
    char  type;
    union grph_nodeUnion inf;
};

typedef struct grph_nodeStruct *grph_graphType;



#endif




