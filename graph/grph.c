/* --------------------------------
 *
 *    File: @(#)grph.c   1.0
 *    Date: 4/22/91
 *    Module:  Graph ( grph )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: lbam Graph .
 *
 *
 * --------------------- */


/*============================== DEPENDENCIES ======================*/

# include <stdio.h>
# include <string.h>

# include "../share/share.h"
# include "../share/stck.h"
# include "../txio/txio.h"
# include "gc.h"
# include "vinb.h"
# include "../share/mem/alloc.h"
# include "grphtype.h"
# include "grphmacr.h"

/*======================= END OF DEPENDENCIES ======================*/

/*========================= TYPES ==================================*/

/*****
 * If you plain to use this module, please, read types at "grphtype.h" 
 */

typedef struct grph_infStruct {
   int max_stck_dump;
   int max_ct_nodes;
   int max_locVars;
   int max_tsk_args;
   int max_fun_args;
   int max_trm_args;
   int max_tsk_stack;
   int flags;         /* the or of the below fields */
} *grph_infType;

struct grph_infStruct grph_inf;

  


/* reuse nodes during the past execution: max sizes unmodified */
/* THE ONLY ONE CURRENTLY USED !! */
# define GRPH_REUSE     0x1 

/* do not do garbage collection: use directly memory allocation */
# define GRPH_NOCOLLECT 0x2

/* Do not assoc. a `view' number to each node: i.e.: no debug.  */
# define GRPH_NOVIEW    0x4


/*========================= END OF TYPES ===========================*/

/*===================== LOCALS =====================================*/

size_t grph_sizes[GRPH_NODE_TYPES]; /* sizes of nodes at malloc time*/
grph_graphType *grph_cts;           /* constants nodes in graph.    */

void grph_initSizes( inf_st )
   grph_infType inf_st;
/*---------------------
 * Comments: Extracts information from inf_st and initializes the 
 *           sizes array: grph_sizes;
 *--------------------------*/
{
   size_t fixed=sizeof(union grph_rcDbgUnion)+sizeof(int);

   grph_sizes[GRPH_CONSTANT]=fixed+sizeof(grph_constNodeType);
   grph_sizes[GRPH_VARIABLE]=fixed+sizeof(grph_varNodeType);
   grph_sizes[GRPH_NUMBER]=fixed+sizeof(grph_numbNodeType);
   grph_sizes[GRPH_TERM] = fixed+sizeof(grph_termNodeType) +
      (size_t)(inf_st->max_trm_args-1)*sizeof(grph_graphType);
   grph_sizes[GRPH_PTERM] = fixed+sizeof(grph_ptermNodeType) +
      (size_t)(inf_st->max_trm_args-1)*sizeof(grph_graphType);
   grph_sizes[GRPH_FUNCTION]=fixed+sizeof(grph_funcNodeType)+
      (size_t)(inf_st->max_fun_args-1)*sizeof(grph_graphType);
   grph_sizes[GRPH_TASK]=fixed+sizeof(grph_taskNodeType)+
      (size_t)inf_st->max_tsk_args*sizeof(grph_graphType)+
      (size_t)inf_st->max_locVars*sizeof(grph_locVarType);
   grph_sizes[GRPH_AE_S]=sizeof(struct a_e_struct);
   grph_sizes[GRPH_STCK]=
      (size_t)inf_st->max_stck_dump * sizeof(grph_graphType);

   if( grph_sizes[GRPH_VARIABLE] > grph_sizes[GRPH_NUMBER] )
     grph_sizes[GRPH_NUMBER]=grph_sizes[GRPH_VARIABLE];
   else grph_sizes[GRPH_VARIABLE]=grph_sizes[GRPH_NUMBER];
   grph_sizes[GRPH_FREE_VAR]=grph_sizes[GRPH_VARIABLE];

   if( grph_sizes[GRPH_FUNCTION] > grph_sizes[GRPH_PTERM] )
      grph_sizes[GRPH_PTERM]=grph_sizes[GRPH_FUNCTION];
   else grph_sizes[GRPH_FUNCTION]=grph_sizes[GRPH_PTERM];
   grph_sizes[GRPH_TERM]=grph_sizes[GRPH_PTERM];


}/*grph_initSizes*/

void grph_initConsts( inf_st )
   grph_infType inf_st;
/*---------------------
 * Comments: Extracts information from inf_st and initializes the 
 *           constant array. The sizes array must be initialized.
 *           Sets GRPH_TRUE and GRPH_FALSE as predefined consts.
 *--------------------------*/
{
   int ind;

   if( (grph_cts = ( grph_graphType *)
      blalloc((size_t)inf_st->max_ct_nodes*sizeof(grph_graphType *)))
      == NULL )
      txio_fatal("No memory for constant nodes");
   for( ind = 2; ind < inf_st->max_ct_nodes+2; ind++ ) {
      if( ( grph_cts[ind]= ( grph_graphType )
            blalloc(grph_sizes[GRPH_CONSTANT]) ) == NULL )
         txio_fatal("No memory for constant nodes");
      grph_cts[ind]->inf.cons=ind;
      grph_cts[ind]->node_RC = GRPH_CT_RC;
   }
   grph_cts[0]= ( grph_graphType)blalloc(grph_sizes[GRPH_CONSTANT]);
   grph_cts[1]= ( grph_graphType)blalloc(grph_sizes[GRPH_CONSTANT]);
   if ( grph_cts[0] == NULL || grph_cts[1] == NULL )
      txio_fatal("No memory for predefined constant nodes");
   grph_cts[0]->inf.cons=GRPH_TRUE;
   grph_cts[1]->inf.cons=GRPH_FALSE;
   grph_cts[0]->node_RC = grph_cts[1]->node_RC = GRPH_CT_RC;

}/*grph_initConsts*/

/*----------- Garbage Collector functions --------------------------*/
/*------------------------------------------------------------------*/

void grph_disposeNd( n )
   grph_graphType n;
/*------------------
 * Comment: gives nd to GC
 *-------------------*/
{
   switch( n->type ) {
   case GRPH_VARIABLE: case GRPH_FREE_VAR: case GRPH_NUMBER:
      gc_put_vn( n );
      break;
   case GRPH_TERM: case GRPH_PTERM: case GRPH_FUNCTION:
      gc_put_tpf(n);
      break;
   case GRPH_TASK:
      gc_put_t(n);
      break;
   case GRPH_AE_S:
      gc_put_ae(n);
      break;
   default:
      txio_fatal("Attempt to dispose an \"eternal\" node");
   }

}/*grph_disposeNd*/
/*----------- End of Garbage Collector functions -------------------*/
void grph_clrTsk( n )
   grph_graphType n;
/*---------------------
 * Comments: Clean n to reuse memory.
 *--------------------------*/
{
  int ind;

  for( ind = 0; ind < grph_getTskNArgs(n); ind++ )
     grph_decRC(grph_getTskArg(n,ind));
  switch( n->tsk_sts ) {
  case GRPH_SEMIDORMANT:
     grph_decRC( (grph_graphType)n->tsk_res );
  break;
  case GRPH_ACTIVE: case GRPH_EVALUATED:
     gc_put_ae( n->inf.task.st_u );
  break;
  }

}/*grph_clrTsk*/

void grph_clrTPF( n )
   grph_graphType n;
/*---------------------
 * Comments: Clean n to reuse memory.( for Term,Pterm,func).
 *--------------------------*/
{
   int ind;
   switch( n->type ) {
   case GRPH_TERM:
      for( ind = 0; ind < grph_getTrmNArgs(n); ind++ )
         grph_decRC( grph_getTrmArg(n,ind) );
   break;
   case GRPH_PTERM:
      for( ind = 0; ind < grph_getPTrmNArgs(n); ind++ )
         grph_decRC( grph_getPTrmArg(n,ind) );
   break;
   case GRPH_FUNCTION:
      for( ind = 0; ind < grph_getFunNArgs(n); ind++ )
         grph_decRC( grph_getFunArg(n,ind) );
   break;
   }

}/*grph_clrTPF*/


void grph_clrae( n )
   struct a_e_struct *n;
/*---------------------
 * Comments: Clean n to reuse memory.
 *--------------------------*/
{
   grph_decRC( n->fpt );
   grph_decRC( n->ldpt );
   grph_decRC( n->bpt );
   blfree( stck_buffpt( n->stack ));
   if( n->evm & GRPH_BDY_EVM ) 
      blfree( stck_buffpt( n->evm_u.bdy_st.sstack ));

}/*grph_clrae*/

/*===================== END OF LOCALS ==============================*/

/*----------- Construction functions -------------------------------*/
/*------------------------------------------------------------------*/

grph_graphType grph_init( inf_st   )
   grph_infType inf_st;
/*---------------------
 * Return: the root task node of the graph.
 * Comments: Extracts information from inf_st and initializes the graph.
 *           then allocates a Tsk node returning it.
 *--------------------------*/
{
   grph_graphType mtsk;
   int ind;
   grph_graphType grph_newTsk();

   grph_inf.max_stck_dump=inf_st->max_stck_dump;
   grph_inf.max_ct_nodes = inf_st->max_ct_nodes; 
   grph_inf.max_locVars  =inf_st->max_locVars;  
   grph_inf.max_tsk_args =inf_st->max_tsk_args; 
   grph_inf.max_fun_args =inf_st->max_fun_args; 
   grph_inf.max_trm_args =inf_st->max_trm_args; 
   grph_inf.max_tsk_stack=inf_st->max_tsk_stack;
   grph_inf.flags        =inf_st->flags;

   grph_initSizes( inf_st ); 

   /* Start Garb. Collector... */
   if( !inf_st ||  !(inf_st->flags & GRPH_REUSE)) { 
      gc_start();
      gc_install_func(grph_clrTsk,GC_T);
      gc_install_func(grph_clrTPF,GC_TPF);
      gc_install_func(grph_clrae,GC_AE);
   }
   /* Build a new graph: Constants and root-task... */
   grph_initConsts( inf_st );
   if( (mtsk = grph_newTsk()) == NULL )
      txio_fatal("No memory for root node");
   return( mtsk );

}/*grph_init*/

grph_graphType grph_newVar()
/*--------------------
 * Return: a new Partial Num node.
 * Comment: allocates a new Var node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_vn(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_VARIABLE]))
        == NULL )
      txio_fatal("No more memory when allocating var node");
   nd->type = GRPH_FREE_VAR;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();
   nd->inf.var.trail_link = NULL;

  return( nd );

}/*grph_newVar*/

grph_graphType grph_newNum( )
/*--------------------
 * Return: a new Partial Num node.
 * Comment: allocates a new Num node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_vn(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_NUMBER]))
        == NULL )
      txio_fatal("No more memory when allocating number node");
   nd->type = GRPH_NUMBER;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();
   return( nd );

}/*grph_newNum*/

grph_graphType grph_newPTerm()
/*--------------------
 * Return: a new Partial Term node.
 * Comment: allocates a new Partial term node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_tpf(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_PTERM]))
        == NULL )
      txio_fatal("No more memory when allocating term node");
   nd->type = GRPH_PTERM;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();

   return( nd );

}/*grph_newPTerm*/

grph_graphType grph_newTerm()
/*--------------------
 * Return: a new Term node.
 * Comment: allocates a new term node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_tpf(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_TERM]))
        == NULL )
      txio_fatal("No more memory when allocating term node");
   nd->type = GRPH_TERM;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();
   return( nd );
}/*grph_newTerm*/

grph_graphType grph_newFunc()
/*--------------------
 * Return: a new func node.
 * Comment: allocates a new func node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_tpf(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_FUNCTION]))
        == NULL )
      txio_fatal("No more memory when allocating function node");
   nd->type = GRPH_FUNCTION;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();
   return( nd );

}/*grph_newFunc*/

grph_graphType grph_newTsk()
/*--------------------
 * Return: a new task node.
 * Comment: allocates a new task node.
 *------------------------*/
{
   grph_graphType nd;

   gc_get_t(nd);
   if( nd == NULL  &&
       (nd = (grph_graphType) blalloc(grph_sizes[GRPH_TASK]))
        == NULL )
      txio_fatal("No more memory when allocating task node");
   nd->type = GRPH_TASK;
   nd->node_RC = 1; /* The one of who ask for this node */
   nd->node_vnum = vinb_getNb();
   nd->tsk_arg =( struct grph_nodeType **) 
      (( grph_locVarType **)&(nd->tsk_var) + 1 );
   nd->tsk_var = ( grph_locVarType *)
      ( nd->tsk_arg + grph_inf.max_tsk_args );
   return( nd );

}/*grph_newTsk*/

struct a_e_struct *grph_newAE()
/*--------------------
 * Return: a new a_e_struct node.
 * Comment: allocates a new a_e_struct node.
 *------------------------*/
{
   struct a_e_struct *nd;
   void *buff = (void *)blalloc( grph_sizes[ GRPH_STCK] );

   gc_get_ae(nd);
   if( buff == NULL || ( 
       nd == NULL  &&
       (nd = (struct a_e_struct *) blalloc(grph_sizes[GRPH_AE_S]))
        == NULL) )
      txio_fatal("No more memory when expanding task node");
   stck_create(nd->stack,buff);
   return( nd );

}/*grph_newAE*/


/*----------- End of Construction functions ------------------------*/

/*----------- Variable related methods -----------------------------*/
/*------------------------------------------------------------------*/


int grph_occurCheck( nd, gr )
   grph_graphType nd;
   grph_graphType gr;
/*-------------------
 * Return: non-zero if variable node occurs in graph.
 *----------------------*/
{
   int ind;

   switch( gr->type ){
   case GRPH_VARIABLE: case GRPH_FREE_VAR:
      return( nd == gr );
   case GRPH_TERM:
      for( ind = 0; ind < grph_getTrmNArgs(gr); ind++ )
         if( grph_occurCheck( nd, grph_getTrmArg(gr,ind)) )
            return( TRUE );
      break;
   case GRPH_PTERM:
      for( ind = 0; ind < grph_getPTrmAArgs(gr); ind++ )
         if( grph_occurCheck( nd, grph_getPTrmArg(gr,ind)) )
            return( TRUE );
      break;
   case GRPH_FUNCTION:
      for( ind = 0; ind < grph_getFunAArgs(gr); ind++ )
         if( grph_occurCheck( nd, grph_getFunArg(gr,ind)) )
            return( TRUE );
      break;
   case GRPH_TASK:
         return( grph_occurCheck(nd, grph_getTskVal(gr)) );
   }

   return( FALSE );

}/*grph_occurCheck*/



/*----------- End of Variable related methods ----------------------*/


/*----------- Task related methods ---------------------------------*/
/*------------------------------------------------------------------*/

/*** EVM ***/


void grph_setupBdy(T)
   struct a_e_struct *T;
/*------------------
 * Comment: Give T all it need to become a 
 *          body evaluated task node.
 *-------------------*/
{
   void *buff = (void *)blalloc( grph_sizes[GRPH_STCK] );
   if ( buff == NULL )
      txio_fatal("No memory for stacks" );
   stck_create( T->ae_sstk, buff );

}/*grph_setupBdy*/


/*** TRAIL ***/

void grph_undoTrl ( T )
   struct a_e_struct *T;
/*-----------------
 * comments: Frees variables in T's trail as releasing it.
 *--------------------*/
{
   grph_graphType trl;
   
   while( T->trail != NULL ){
      trl=T->trail;
      grph_free(trl);
      T->trail=trl->inf.var.trail_link;
      grph_decRC(trl);
   }

}/*grph_undoTrl*/

/*----------- End of Task related methods --------------------------*/

/*----------- I/O Related methods ----------------------------------*/
/*------------------------------------------------------------------*/

static grph_graphType grph_sco;
static FILE *grph_scfp;
static int grph_scan_noBuild;

grph_graphType grph_scanRec()
/*------------------
 * Returns: a readed node.
 * Comment: reads a node from grph_scfp with grph_sco vars.
 *-------------------*/
{
   return( NULL );

}/*grph_scanRec*/

grph_graphType grph_scan( fp, obj )
   FILE *fp;
   grph_graphType obj;
/*------------------
 * Returns: a readed node.
 * Comment: reads a node from fp with obj vars.
 *-------------------*/
{
  grph_scfp = fp;
  grph_sco= obj;
  grph_scan_noBuild = TRUE;
  if ( grph_scanRec( ) == NULL) 
     return( grph_getConstNd( GRPH_FALSE ));
  /* Sintax OK: Build expression */
  grph_scan_noBuild = FALSE;
  return( grph_scanRec() );

}/*grph_scan*/


/*** COMMENT: 
  The below functions ( most of them ) have a `fp' as parameter
  if it's non-NULL the data is dumped to this fp, whenever it's
  NULL txio standar functions are used.
 *******************/

void grph_print( fp, nd, obj )
   FILE *fp;
   grph_graphType nd;
   grph_graphType obj;
/*------------------
 * Comment: prints nd with obj. vars to fp.
 *-------------------*/
{
   int ind,rule;

   grph_deref(nd);
   switch( nd->type ) {
   case GRPH_CONSTANT:
      if ( fp != NULL )
         fprintf(fp,"%s",cnst_constName(nd->inf.cons));
      else
         txio_printf("%s",cnst_constName(nd->inf.cons));
   break;
   case GRPH_NUMBER:
      if ( fp != NULL )
         fprintf(fp,"%d",nd->inf.numb.number);
      else
         txio_printf("%d",nd->inf.numb.number);
   break;
   case GRPH_FREE_VAR:
      for ( ind = 0; 
            ind < grph_getTskNVars(obj) &&
            (nd != grph_getTskVar(obj,ind))    ; ind++)
         ;
      if( nd == grph_getTskVar(obj,ind) ) /* Has a name... */
         if ( fp != NULL )
            fprintf(fp,"X%d",ovar_varName(ind) );
         else txio_printf("X%d",ovar_varName(ind) );
      else
         if ( fp != NULL )
            fprintf(fp,"X%d",nd->node_vnum );
         else txio_printf("X%d",nd->node_vnum );
   break;
   case GRPH_TERM:
      if ( fp != NULL )
         fprintf(fp,"%s(",cnst_constrName(nd->inf.term.constructor));
      else
         txio_printf("%s(",cnst_constrName(nd->inf.term.constructor));
      for( ind = 0; ind < grph_getTrmNArgs(nd); ind++ ){
         if( ind != 0 && fp != NULL )
            fprintf(fp,", ");
         else if ( ind != 0 ) txio_printf(", ");
         grph_print(fp,grph_getTrmArg(nd,ind),obj);
      }
      if( fp != NULL )
         fprintf(fp,")");
      else if ( ind != 0 ) txio_printf(")");
      break;
   case GRPH_PTERM:
      if ( fp != NULL )
         fprintf(fp,"%s(",cnst_constrName(nd->inf.pterm.constructor));
      else
         txio_printf("%s(",cnst_constrName(nd->inf.pterm.constructor));
      for( ind = 0; ind < grph_getPTrmAArgs(nd); ind++ ){
         if( ind != 0 && fp != NULL )
            fprintf(fp,", ");
         else if ( ind != 0 ) txio_printf(", ");
         grph_print(fp,grph_getPTrmArg(nd,ind),obj);
      }
      if( fp != NULL )
         fprintf(fp,")");
      else if ( ind != 0 ) txio_printf(")");
      break;
   case GRPH_FUNCTION:
      if ( fp != NULL )
         fprintf(fp,"%s(",fun_funcName(grph_getFunCA(nd),&rule));
      else
         txio_printf("%s(",fun_funcName(grph_getFunCA(nd),&rule));
      for( ind = 0; ind < grph_getFunAArgs(nd); ind++ ){
         if( ind != 0 && fp != NULL )
            fprintf(fp,", ");
         else if ( ind != 0 ) txio_printf(", ");
         grph_print(fp,grph_getFunArg(nd,ind),obj);
      }
      if( fp != NULL )
         fprintf(fp,")");
      else txio_printf(")");
      break;
   default:
      txio_fatal("grph_print: call with wrong node type");
   }

}/*grph_print*/

void dumpRC( fp, rc )
   FILE *fp;
   int rc;
/*------------------
 * Comment: dumps rc to fp.
 *-------------------*/
{
   if ( fp != NULL )
      fprinf(fp,"<%2d> ",rc);
   else txio_printf("<%2d> ",rc);
}/*dumpRC*/


int grph_dumpArgsNb( fp, a, n )
   FILE *fp;
   grph_graphType *a;
   int n;
/*------------------
 * Returns: Number of lines printed.
 * Comment: dumps n view-numbers of args a.
 *-------------------*/
{
   while( n-- > 0 ) 
      if( fp == NULL )
        txio_printf("[%3d]",(*a++)->node_vnum);
      else fprintf(fp,"[%3d]",(*a++)->node_vnum);
   
}/*grph_dumpArgsNb*/

char *grph_stsstr( sts )
   int sts;
/*------------------
 * Returns: A string with name of status s
 *-------------------*/
{
  static char d[] = "Dormant";
  static char s[] = "Semidormant";
  static char a[] = "Active";
  static char e[] = "Evaluated";
  static char u[] = "Unknown!!";

  switch( sts ) {
  case GRPH_DORMANT: return( d );
  case GRPH_SEMIDORMANT: return( s );
  case GRPH_ACTIVE: return( a );
  case GRPH_EVALUATED: return( e );
  default: return( u );
  }

}/*grph_stsstr*/

void grph_dumpStck( fp, st )
   FILE *fp;
   stck_stackType st;
/*------------------
 * Comment: dumps trail to fp.
 *-------------------*/
{
  int nds = grph_inf.max_stck_dump;
  if ( fp != NULL )
     fprintf(fp,"Stack: |");
  else txio_printf("Stack: |");
  for( ; ! stck_isEmpty(st) && nds-- > 0 ; stck_move(st) )
     if( fp != NULL )
       fprintf(fp,"<%3d]",((grph_graphType)(stck_top(st)))->node_vnum);
     else 
       txio_printf("<%3d]",((grph_graphType)(stck_top(st)))->node_vnum);
  if ( ! stck_isEmpty( st ) )
     if( fp != NULL ) fprintf(fp,"...");
     else txio_printf("...");
  else
     if( fp != NULL ) fprintf(fp,"<|");
     else txio_printf("<|");
     
}/*grph_dumpStck*/

void grph_dumpTrail( fp, trl )
   FILE *fp;
   grph_graphType trl;
/*------------------
 * Comment: dumps trail to fp.
 *-------------------*/
{
  int nds = grph_inf.max_stck_dump;
  if ( fp != NULL )
     fprintf(fp,"Trail: |");
  else txio_printf("Trail: |");
  for( ; trl != NULL && nds-- > 0 ; trl=trl->inf.var.trail_link)
     if( fp != NULL )
       fprintf(fp,"<%3d]",trl->node_vnum);
     else txio_printf("<%3d]",trl->node_vnum);
  if ( trl != NULL )
     if( fp != NULL ) fprintf(fp,"...");
     else txio_printf("...");
  else
     if( fp != NULL ) fprintf(fp,"<|");
     else txio_printf("<|");

}/*grph_dumpTrail*/

void grph_dumpEvm( fp, evm )
   FILE *fp;
   int evm;
/*------------------
 * Comment: dumps evm to fp.
 *-------------------*/
{
  if ( fp != NULL ) 
    if ( evm & GRPH_ARG_EVM ) {
      fprintf(fp,"Arg. ev. ");
      if ( evm & GRPH_FRET_EVM ) fprintf(fp,"( Func. Ret.)");
      else fprintf(fp,"( Non Fnc.Ret.)");
    } else { 
      fprintf(fp,"Bdy. ev. ");
      if ( evm & GRPH_HNF_EVM ) fprintf(fp,"to Hd.Norm.Form");
      else fprintf(fp,"to Norm. Form");
    }
  else
    if ( evm & GRPH_ARG_EVM ) {
      txio_printf("Arg. ev. ");
      if ( evm & GRPH_FRET_EVM ) txio_printf("( Func. Ret.)");
      else txio_printf("( Non Fnc.Ret.)");
    } else { 
      txio_printf("Bdy. ev. ");
      if ( evm & GRPH_HNF_EVM ) txio_printf("to Hd.Norm.Form");
      else txio_printf("to Norm. Form");
    }

}/*grph_dumpEvm*/

int grph_dump( fp, nd, mode )
   FILE *fp;
   grph_graphType nd;
   int mode;
/*------------------
 * Returns: The number of lines used.
 * Comment: dumps node info to fp.
 *-------------------*/
{
   int rule;

   switch( nd->type ){
   case GRPH_CONSTANT:
      if( fp != NULL )
         fprintf(fp,"Const: %s",cnst_consName(nd->inf.cons));
      else txio_printf("Const: %s",cnst_consName(nd->inf.cons));
      return( 1 );
   case GRPH_VARIABLE:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Var: %3d",nd->inf.var.reference->node_vnum);
      else txio_printf("Var: %3d",nd->inf.var.reference->node_vnum);
      return( 1 );
   case GRPH_FREE_VAR:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Var: free");
      else txio_printf("Var: free");
      return( 1 );
   case GRPH_NUMBER:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Numb: %5d",nd->inf.numb.number);
      else txio_printf("Numb: %5d",nd->inf.numb.number);
      return( 1 );
   case GRPH_TERM:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Term: %s of \n     ", 
            cnst_constrName(nd->inf.term.constructor));
      else txio_printf("Term: %s of \n     ", 
               cnst_constrName(nd->inf.term.constructor));
      grph_dumpArgs( fp, &nd->inf.term.args, nd->inf.term.numberArgs);
      return( 2 );
   case GRPH_PTERM:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Parcial Term: %s of \n     ", 
            cnst_constrName(nd->inf.pterm.constructor));
      else txio_printf("Parcial Term: %s of \n     ", 
               cnst_constrName(nd->inf.pterm.constructor));
      grph_dumpArgs( fp, &nd->inf.pterm.args, nd->inf.pterm.actualArgs);
      return( 2 );
   case GRPH_FUNCTION:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,
           "Parcial application: %s starting at %3d ( %3d vars ) of \n     ", 
            func_funName(nd->inf.func.codeAddress, &rule),
            nd->inf.func.codeAddress, nd->inf.func.numberLocVars);
      else txio_printf(
            "Parcial application: %s starting at %3d ( %3d vars ) of \n     ", 
            func_funName(nd->inf.func.codeAddress, &rule),
            nd->inf.func.codeAddress, nd->inf.func.numberLocVars);
      grph_dumpArgs( fp, &nd->fun_args, nd->inf.func.actualArgs);
      return( 2 );
   case GRPH_TASK:
      dumpRC( fp, nd->node_RC );
      if( fp != NULL )
         fprintf(fp,"Task: %s with rule %3d starting at %3d",
            func_funName(nd->tsk_cdAddr,&rule), rule, 
            nd->tsk_cdAddr );
      else
         txio_printf("Task: %s with rule %3d starting at %3d",
            func_funName(nd->tsk_cdAddr,&rule), rule, 
            nd->tsk_cdAddr );
      if( fp != NULL )
         fprintf(fp," is %s\n     has %3d vars.\n     Args:",
           grph_stsstr(nd->tsk_sts),nd->tsk_nlv );
      else txio_printf(" is %s\n     has %3d vars.\n     Args:",
           grph_stsstr(nd->tsk_sts),nd->tsk_nlv );
      grph_dumpArgs(fp,nd->tsk_arg,nd->tsk_nargs);
      switch( nd->tsk_sts ) {
      case GRPH_DORMANT: 
         return( 3 );
      case GRPH_SEMIDORMANT:
         if ( fp != NULL )
           fprintf(fp,"\n     Result was: [%3d]",nd->tsk_res);
         else txio_printf("\n     Result was: [%3d]",nd->tsk_res);
         return( 4 );
      case GRPH_ACTIVE: case GRPH_EVALUATED:
         if( fp != NULL ){
           fprintf(fp, "\n     %2d arg.evtd. %3d-PC %3d-Bt.Ad.",
              nd->tsk_nae, nd->tsk_pc, nd->tsk_btAddr);
           fprintf(fp, "\n     ftr.[%3d], lst.dsc.[%3d], backt.[%3d]\n     ",
              nd->tsk_fpt->node_vnum,nd->tsk_ldpt->node_vnum,
              nd->tsk_bpt->node_vnum );
         }else {
           txio_printf( "\n     %2d arg.evtd. %3d-PC %3d-Bt.Ad.",
              nd->tsk_nae, nd->tsk_pc, nd->tsk_btAddr);
           txio_printf( "\n     ftr.[%3d], lst.dsc.[%3d], backt.[%3d]\n     ",
              nd->tsk_fpt->node_vnum,nd->tsk_ldpt->node_vnum,
              nd->tsk_bpt->node_vnum );
         }
         grph_dumpStck(fp, nd->tsk_stk );
         if((fp)==NULL)txio_printf("\n     ");
         else fprintf((fp),"\n     ");
         grph_dumpTrail(fp, nd->tsk_trl ); 
         if((fp)==NULL)txio_printf("\n     ");
         else fprintf((fp),"\n     ");
         grph_dumpEvm(fp,nd->tsk_evm);
         if( grph_isArg( nd->inf.task.st_u ) ) {
           if( fp != NULL )
             fprintf(fp," with block lb. %3d",nd->tsk_blb);
           else txio_printf(" with block lb. %3d",nd->tsk_blb);
           return( 8 );
         }
         if( fp != NULL )
           fprintf(fp," with secure PC %3d\n     Sec.");
         else txio_printf(" with secure PC %3d\n     Sec.");
         grph_dumpStck(fp, nd->tsk_sstk );
         return( 9 );
      }
      break;
   default:
     txio_fatal("grph_dump: Call with wrong node type");
   }
   
}/*grph_dump*/

/*----------- End of I/O Related methods ---------------------------*/



