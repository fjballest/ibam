/* --------------------------------
 *
 *    File: @(#)grph.h   1.0
 *    Date: 4/22/91
 *    Module:  Graph ( grph )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: lbam Graph .
 *
 *
 * --------------------- */

# ifndef __GRPH_H
#  define __GRPH_H 1

/*===================== IMPLICIT DEPENDENCIES ======================*/
/*
 * You MUST include std. header string.h : definitions used in macr.
 */
/*================= END OF IMPLICIT DEPENDENCIES ===================*/

/*============================== DEPENDENCIES ======================*/

# include "../share/share.h"
# include "../share/stck.h"
# include "grphtype.h"
# include "grphmacr.h"

/*======================= END OF DEPENDENCIES ======================*/

/*========================= TYPES ==================================*/

/*****
 * If you plain to use this module, please, read types at "grphtype.h" 
 */

typedef struct grph_infStruct {
   int max_stck_dump; /* number of nodes printed by stack dumps */
   int max_ct_nodes;  /* max. nb. of constants */
   int max_locVars;   /* max. nb. of local vars for tasks */
   int max_tsk_args;  /* max. nb. of arguments in tasks */
   int max_fun_args;  /* max. nb. of arguments in functions */
   int max_trm_args;  /* max. nb. of arguments in terms */
   int max_tsk_stack; /* max. stack size in tasks */
   int flags;         /* the or of the below fields */
} *grph_infType;

/* reuse nodes during the past execution: max sizes unmodified */
# define GRPH_REUSE     0x1 

/* do not do garbage collection: use directly memory allocation */
# defile GRPH_NOCOLLECT 0x2


/* Do not assoc. a `view' number to each node: i.e.: no debug.  */
# define GRPH_NOVIEW    0x4

/*========================= END OF TYPES ===========================*/

/*----------- Construction functions -------------------------------*/
/*------------------------------------------------------------------*/

grph_nodeType grph_init( /* grph_infType inf_st   */ );
/*---------------------
 * Return: the root task node of the graph.
 * Comments: Extracts information from inf_st and initializes the graph.
 *           then allocates a Tsk node returning it.
 *--------------------------*/


grph_graphType grph_newConst(/* void */ );
/*--------------------
 * Return: a new Partial Const node.
 * Comment: allocates a new Const node.
 *------------------------*/

grph_graphType grph_newVar(/* void */ );
/*--------------------
 * Return: a new Partial Num node.
 * Comment: allocates a new Var node.
 *------------------------*/

grph_graphType grph_newNum(/* void */ );
/*--------------------
 * Return: a new Partial Num node.
 * Comment: allocates a new Num node.
 *------------------------*/

grph_graphType grph_newPTerm(/* void */ );
/*--------------------
 * Return: a new Partial Term node.
 * Comment: allocates a new Partial term node.
 *------------------------*/

grph_graphType grph_newTerm(/* void */ );
/*--------------------
 * Return: a new Term node.
 * Comment: allocates a new term node.
 *------------------------*/

grph_graphType grph_newFunc(/* void */ );
/*--------------------
 * Return: a new func node.
 * Comment: allocates a new func node.
 *------------------------*/

grph_graphType grph_newTsk( /* void */ );
/*--------------------
 * Return: a new task node.
 * Comment: allocates a new task node.
 *------------------------*/

/*int grph_getType(  node );*/
/*-------------------
 ** MACRO **
 * Return: the type of node. ( GRPH_TASK,... )
 *----------------------*/

/*----------- End of Construction functions ------------------------*/

/*----------- Constant related methods -----------------------------*/
/*------------------------------------------------------------------*/

/*int grph_getConst( nd );*/
/*-------------------
 ** MACRO **
 * Return: The constant in node.
 *----------------------*/


/*grph_graphType grph_getConstNd( ct );*/
/*-------------------
 ** MACRO **
 * Return: The node for constant ct.
 *----------------------*/

/*----------- End of Constant related methods ----------------------*/

/*----------- Variable related methods -----------------------------*/
/*------------------------------------------------------------------*/

/*void grph_deref( node );*/ 
/*-------------------
 ** MACRO **
 * comment: dereferences the node.
 *----------------------*/

int grph_occurCheck( /* node, graph */ );
/*-------------------
 * Return: non-zero if variable node occurs in graph.
 *----------------------*/

/*void grph_bind( vnode, node );*/ 
/*-------------------
 ** MACRO **
 * Comment: Sets vnode reference to node.
 *------------------------*/

/*void grph_free( vnode );*/ 
/*--------------------
 ** MACRO **
 * Comment: Sets vnode as free, releasing the reference contained in it
 *          if there was one.
 *-------------------*/

/*----------- End of Variable related methods ----------------------*/

/*----------- Number related methods -------------------------------*/
/*------------------------------------------------------------------*/

/*void grph_setNum( node, value );*/ 
/*------------------
 ** MACRO **
 * Comment: Sets value of a Number node.
 *---------------------*/

/*(long ) int grph_getNum(  node  );*/
/*-----------------
 ** MACRO **
 * Returns: The value of a number node.
 *---------------------*/

/*----------- End of Number related methods ------------------------*/

/*----------- Term related methods ---------------------------------*/
/*------------------------------------------------------------------*/

/*void grph_setPConstr( node, c );*/ 
/*-----------------
 ** MACRO **
 * Comment: Sets c as constructor for the partial term node.
 *------------------*/

/*void grph_setConstr( node, c );*/ 
/*-----------------
 ** MACRO **
 * Comment: Sets c as constructor for the node.
 *------------------*/

/*int grph_getPConstr( node );*/ 
/*------------------
 ** MACRO **
 * Returns: The constructor of the partial term node
 *-------------------*/

/*int grph_getConstr( node );*/ 
/*------------------
 ** MACRO **
 * Returns: The constructor of the node
 *-------------------*/

/*void grph_setPTrmNArgs( node, n );*/ 
/*----------------
 ** MACRO **
 * Comment: Sets the number of args for the ( partial term ) node
 *-------------------*/

/*void grph_setTrmNArgs( node, n );*/ 
/*----------------
 ** MACRO **
 * Comment: Sets the number of args for the ( term ) node
 *-------------------*/

/*int grph_getPTrmAArgs( n );*/ 
/*------------------
 ** MACRO **
 * Returns: The number of actual args. of the parc. term. node.
 *-------------------*/

/*int grph_getPTrmNArgs( n );*/ 
/*------------------
 ** MACRO **
 * Returns: The number of args of the parc. term. node.
 *-------------------*/

/*int grph_getTrmNArgs( n );*/ 
/*------------------
 ** MACRO **
 * Returns: The number of args of the term. node.
 *-------------------*/

/*void grph_setPTrmArg( t, i, a );*/ 
/*------------------
 ** MACRO **
 * Comment: Fix the i-th arg of the parc. term t to a.
 *-----------------------*/

/*void grph_setTrmArg( t, i, a );*/ 
/*------------------
 ** MACRO **
 * Comment: Fix the i-th arg of the term t to a.
 *-----------------------*/

/*grph_graphType grph_getPTrmArg( t, i );*/ 
/*------------------
 ** MACRO **
 * Returns: the i-th arg of parc. term t.
 *-------------------*/

/*grph_graphType grph_getTrmArg( t, i );*/ 
/*------------------
 ** MACRO **
 * Returns: the i-th arg of term t.
 *-------------------*/

/*void grph_cpTrmArgs( src, dst, n );*/ 
/*------------------
 ** MACRO **
 * Comments: copies n-args from the ( arg * / void ** ) src to the term
 *           dst.
 *---------------------*/

/*void grph_cpPTrmArgs( src, dst, n );*/ 
/*------------------
 ** MACRO **
 * Comments: copies n-args from the ( arg * / void ** ) src to the pterm
 *           dst.
 *---------------------*/

/*----------- End of Term related methods --------------------------*/

/*----------- Task related methods ---------------------------------*/
/*------------------------------------------------------------------*/

/**** IMPORTANT:
 * Those methods related in part / exclusively to fields of an 
 * a_e_struct ( inside a Task ( active/... ) node ) have T as
 * parameter ( not t ) : With this notation we mean an a_e_struct
 * pointer rather than a grph_graphType paramenter.
 * The OUTPUT methods ( dump... print... ) use a task node, not
 * an a_e_struct.
 * All these is done to achieve time eficiency.
 *******************************/

/*** ARGS ***/
/*int grph_getTskNArgs( node );*/ 
/*------------------
 ** MACRO **
 * Returns: the number of args of the (tsk ) node.
 *-------------------*/

/*void grph_setTskNArgs( node, n );*/ 
/*------------------
 ** MACRO **
 * Comments: sets the number of args of the (tsk ) node to n.
 *-------------------*/

/*void grph_cpTskArgs( src, dst, n );*/ 
/*------------------
 ** MACRO **
 * Comments: copies n-args from the ( arg * / void ** ) src to the task 
 *           dst.
 *---------------------*/

/*grph_graphType grph_getTskArg( t, i );*/ 
/*------------------
 ** MACRO **
 * Returns: the i-th arg of task t.
 *-------------------*/

/*** CODE ADDR ***/
/*void grph_setTskCA( t, a );*/ 
/*------------------
 ** MACRO **
 * Comment: sets the code adr. of t to a.
 *-------------------*/

/*unsigned grph_getTskCA( t );*/ 
/*------------------
 ** MACRO **
 * Returns: the code. adr. of t.
 *-------------------*/

/*** LOC VARS ***/
/*void grph_setTskNVars( t, n );*/ 
/*------------------
 ** MACRO **
 * Comment: sets the number of loc. vars of t to n.
 *-------------------*/

/*int grph_getTskNVars( t );*/ 
/*------------------
 ** MACRO **
 * Returns: the number of loc. vars of t .
 *-------------------*/

/*grph_graphType grph_getTskVar( t, i );*/ 
/*------------------
 ** MACRO **
 * Returns: the i-th loc. var. of t.
 *-------------------*/

/*** STCK ***/

/*void grph_clrStck( T );*/ 
/*-----------------
 ** MACRO **
 * Comments: Clears the `ae' local stack.
 *-------------------*/

/*int grph_isEmptyStck( T );*/ 
/*-----------------
 ** MACRO **
 * Returns: non-zero if stck of t is empty.
 *-------------------*/

/*void grph_pushStck( T, nd );*/ 
/*-----------------
 ** MACRO **
 * Comments: Pushes nd onto t loc stack.
 *--------------------*/

/*grph_graphType grph_topStck( T );*/ 
/*-----------------
 ** MACRO **
 * Returns: task t top of local stck.
 *--------------------*/

/*void grph_popStck( T );*/ 
/*----------------
 ** MACRO **
 * Comments: Pops t local stack.
 *--------------------*/

/*** TRAIL ***/

/*void grph_clrTrl ( T );*/ 
/*-----------------
 ** MACRO **
 * Comments: Clears the `t' local trail.
 *-------------------*/

/*int grph_isEmptyTrl ( T );*/ 
/*-----------------
 ** MACRO **
 * Returns: non-zero if trail of t is empty.
 *-------------------*/

/*void grph_pushTrl ( T, nd );*/ 
/*-----------------
 ** MACRO **
 * Comments: Pushes nd onto t loc trail.
 *--------------------*/

void grph_undoTrl ( /* T*/ );
/*-----------------
 * comments: Frees variables in t's trail as releasing it.
 *--------------------*/

/*void grph_appTrl ( dst_T, src_T );*/ 
/*----------------
 ** MACRO **
 * Comments: Appends src loc trail to dst loc trail, leaves src trail as
 *           empty.
 *--------------------*/

/*** PC ***/

/*void grph_setPC( T, a );*/ 
/*------------------
 ** MACRO **
 * Comment: sets the pc of t to a.
 *-------------------*/

/*unsigned grph_getPC( T );*/ 
/*------------------
 ** MACRO **
 * Returns: the pc of t.
 *-------------------*/

/*void grph_incPC( T );*/ 
/*------------------
 ** MACRO **
 * Comment: incs. the pc of t .
 *-------------------*/

/*** NAE ***/

/*void grph_decNAE( T );*/ 
/*------------------
 ** MACRO **
 * Comment: decs. the nae of t .
 *-------------------*/

/*void grph_incNAE( T );*/ 
/*------------------
 ** MACRO **
 * Comment: incs. the nae of t .
 *-------------------*/

/*int grph_isZeroNAE( T );*/ 
/*------------------
 ** MACRO **
 * Returns: non-zero if NAE is zero.
 *-------------------*/

/*** EVAL. MODE ***/

/*int grph_isArg( T ); */
/*------------------
 ** MACRO **
 * Returns: non-zero if T is Arg. eval.
 *-------------------*/

/*int grph_isBdy( T ); */
/*------------------
 ** MACRO **
 * Returns: non-zero if T is Bdy. eval.
 *-------------------*/

void grph_setEvm( /* T, mode */ );
/*------------------
 ** MACRO **
 * Comment: sets the mode of T.
 *-------------------*/

/*int grph_getEvm( T );*/ 
/*------------------
 ** MACRO **
 * Returns: the mode of T.
 *-------------------*/

/*void grph_setupBdy(T)*/
/*------------------
 ** MACRO **
 * Comment: Give T all it need to become a 
 *          body evaluated task node.
 *-------------------*/

/*** STATUS ***/

/*void grph_activeTsk( nd );*/
/*------------------
 ** MACRO **
 * Comment: Set nd status as ACTIVE providing an 
 *          a_e_struct to it.
 *-------------------*/

/*void grph_downTsk( nd );*/
/*------------------
 ** MACRO **
 * Comment: Releases a_e_struct from task node. setting
 *          status as SEMIDORMANT
 *-------------------*/

/*void grph_setSts( nd, st );*/
/*------------------
 ** MACRO **
 * Comment: sets nd. status.
 *-------------------*/

/*void grph_getSts( nd, st );*/
/*------------------
 ** MACRO **
 * Returns: nd status.
 *-------------------*/


/*** BACKTRACK.***/

/*void grph_setBlb( nd_T, lb );*/
/*------------------
 ** MACRO **
 * Comment: sets nd block label.
 *-------------------*/

/*void grph_getBlb( nd_T, lb );*/
/*------------------
 ** MACRO **
 * Returns: nd block label.
 *-------------------*/

/*unsigned grph_getSPC( T );*/ 
/*------------------
 ** MACRO **
 * Returns: T secure PC.
 *-------------------*/

/*void grph_setBtAd( T, btad ); */
/*------------------
 ** MACRO **
 * Comment: sets T backtr. addr.
 *-------------------*/

/*unsigned grph_getBtAd( T );*/ 
/*------------------
 ** MACRO **
 * Returns: T backtr. addr.
 *-------------------*/

/*void grph_setLdptr( T, ldptr );*/
/*------------------
 ** MACRO **
 * Comment: sets T last desc. ptr.
 *-------------------*/

/*grph_graphType  grph_getLdptr( T );*/ 
/*------------------
 ** MACRO **
 * Returns: T last desc. ptr.
 *-------------------*/

/*void grph_setBptr( T, bptr );*/
/*------------------
 ** MACRO **
 * Comment: sets T backtracking ptr.
 *-------------------*/

/*grph_graphType  grph_getBptr( T );*/ 
/*------------------
 ** MACRO **
 * Returns: T backtr. ptr.
 *-------------------*/

/*void grph_setFptr( T, fptr );*/
/*------------------
 ** MACRO **
 * Comment: sets T father ptr.
 *-------------------*/

/*grph_graphType  grph_getFptr( T );*/ 
/*------------------
 ** MACRO **
 * Returns: T father ptr.
 *-------------------*/

/*** GC ***/

/*void grph_incRC( n );*/ 
/*------------------
 ** MACRO **
 * Comment: incs. n RC
 *-------------------*/

/*void grph_decRC( n );*/ 
/*------------------
 ** MACRO **
 * Comment: decs. n RC
 *-------------------*/

void grph_disposeNd( /* n */ );
/*------------------
 * Comment: gives nd to GC
 *-------------------*/

/*grph_graphType grph_getTskVal( n );*/
/*------------------
 ** MACRO **
 * Returns: Value of task. ( top of stack if has no value ).
 *-------------------*/

/*----------- Function related methods -----------------------------*/
/*------------------------------------------------------------------*/

/*unsigned grph_getFunCA( n );*/ 
/*------------------
 ** MACRO **
 * Returns: Function n Code address.
 *-------------------*/

/*int grph_getFunAArgs( n );*/ 
/*------------------
 ** MACRO **
 * Returns: n number of actual args.
 *-------------------*/

/*int grph_getFunArg( nd, n );*/ 
/*------------------
 ** MACRO **
 * Returns: n-th arg. of nd.
 *-------------------*/

/*int grph_getFunMArgs( n );*/ 
/*------------------
 ** MACRO **
 * Returns: n number of missing args.
 *-------------------*/

/*void grph_cpFunArgs( src, dst, n );*/ 
/*------------------
 ** MACRO **
 * Comment: copies n args. from ( void **)src to Func. node dst.
 *-------------------*/

/*void grph_addFunArg( n, arg );*/ 
/*------------------
 ** MACRO **
 * Comment: Adds arg to node n.
 *-------------------*/

/* int grph_getFunNVars( n );*/ 
/*------------------
 ** MACRO **
 * Returns: number of loc. vars. for n.
 *-------------------*/

/*----------- End of Function related methods ----------------------*/

/*----------- I/O related Functions --------------------------------*/

grph_graphType grph_scan( /* fp, obj */ );
/*------------------
 * Returns: FALSE ( node with const. ) if error, or a graph.
 * Comment: reads a node from fp with obj vars.
 *-------------------*/
/* This function always returns FALSE, but can be implemented
 * to allow input ( moreover, functions can be readed just
 * rewritting func_getInfo in "../tables/func.[ch]"
 */

void grph_print( /* fp, nd, obj */ );
/*------------------
 * Comment: prints nd with obj. vars to fp.
 *-------------------*/

# define GRPH_LINE_DMP 0x1
# define GRPH_FULL_DMP 0x2

int grph_dump( /* fp, nd, mode */ );
/*------------------
 * Returns: Number of lines used.
 * Comment: dumps node info to fp.mode is an or of definitions
 *          above.( mode is currently not used.)
 *-------------------*/

/*----------- End of I/O related Functions -------------------------*/


struct a_e_struct *grph_newAE();
/* A local funcion used by macro-definitions... */

# endif


