/* ------------------------------
 *
 * File       : @(#)mkgc: Make Garbage Collector. ( G.C. generator ).
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : mkgc
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : This program generates the g.c. auxiliar source C files.
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <stdio.h>
# include <ctype.h>

/* ========== END OF DEPENDENCIES ========== */


/* ========== SYMBOL DEFINITIONS ========== */

# define FALSE 0
# define TRUE 1

# define BUFF_LEN 100    /* lenght for dependencies literals buffer */

/* ========== SYMBOL DEFINITIONS ========== */


/* ========== MACRO DEFINITIONS ========== */
 
# define toNum(c)  ((c)-'0')

/* ========== END OF MACRO DEFINITIONS ========== */


/* ========== PROTOTYPES ========== */

int extract_names(/* char **args,char **nms */ );
int extract_deps(/* int num_p, char **args, int num_nd, short **dpm */);

/* ========== END OF PROTOTYPES ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */

int extract_names( args, nms )
    char  **args;       /*I-O*/
    char  **nms;        /* O */
/* ------------------------------
 * Returns    : non-zero if no error.
 * Use        : 
 * Global     :
 * Parameters : args is a string array with dependencies formatted as
 *              -dn1,n2-n3,n4 -n5,n6. deps is a string array which contains
 *              names information ( the args. that are not deps. ) that
 *              was found in args.
 * Comments   :
 *
 * ------------------------------ */
{
   int ind,ind_nms;

   for ( ind = ind_nms = 0; args[ind]!=NULL; ind++ )
      if (args[ind][0]=='-') {
         if (args[ind][1]!='d')
            return(0);
      } else {
         nms[ind_nms] = args[ind];
         printf(" %s taken as name.\n",nms[ind_nms++]);
         args[ind] = NULL;
      }
   nms[ind_nms]=NULL;
   return(1);
} /* extract_names */


int extract_deps( num_p, args, num_nd, dpm, nms )
    int   num_p;   /* I */
    char  **args;  /* I */
    int   num_nd;  /* I */
    short **dpm;   /* O */
    char **nms;    /* I */
{
   int ind1, ind2;
   char  buff[BUFF_LEN];    /* buffer for reading individual dependencies */
   int   father, son;       /* dependence relations */

   for( ind1=0; ind1<num_p; ind1++)  {
      while (args[ind1]==NULL && ind1<num_p)
          ind1++;  /* skip NULL pointers */
      if ( ind1 < num_p ) {
	  strcpy(buff,args[ind1]+2);
    
	  for (ind2 = 0; buff[ind2]!=(char)0;  ) {
	      if(!isdigit(buff[ind2]))  {
		 if (buff[ind2]=='-')
		    ind2++;
		 else
		    return(0);
	      }
	      father=0;
	      while (isdigit(buff[ind2]))
		 father=father*10 + toNum(buff[ind2++]);
	      if (buff[ind2]!=',')
		  return(0);
	      else ind2++;
	      if (father>num_nd || father<1)
		 return(0);
    
	      do {
		 if (!isdigit(buff[ind2]))  {
		    if (buff[ind2]==':')
		       ind2++;
		    else
		       return(0);
		 }
		 son=0;
		 while(isdigit(buff[ind2]))
		    son=son*10+toNum(buff[ind2++]);
		 if (son>num_nd || son<1)
		    return(0);
		 else {
		    dpm[father-1][son-1] = 1;
		    printf(" Dep.: Father [%s]\tSon [%s]\n",
                       nms[father-1],nms[son-1]);
		 }
	      } while (buff[ind2]!='-' && buff[ind2]!=(char)0);
	   } /* for */
       } /* if */
   } /* for */

}/* extract_deps */


void do_gctype(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates a type declaration for gc_tp with a
 *              list for each name in fp.
 *
 * ------------------------------ */

{
   fprintf(fp,"typedef struct {\n");
     for( ; *nms != NULL; nms++ )
       fprintf(fp,"   list_list_tp %s; /* %s list */ \n",*nms,*nms);
   fprintf(fp,"} gc_type;\n\n");

}/*do_gctype*/

void do_gcfuncdefs(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates definitions for each name.
 *
 * ------------------------------ */

{
   int ind;
   char buff[BUFF_LEN];
   char *aux;

     for( ind = 0; *nms != NULL; ind++, nms++ ) {
       strcpy(buff,*nms);
       for( aux = buff; *aux != (char)0; aux++ )
          if(islower(*aux))  *aux = toupper(*aux);
       fprintf(fp,"\n# define GC_%s %d\n",buff,ind);
     }

}/*do_gcfuncdefs*/

void do_gcfuncs(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates gc functions array.
 *
 * ------------------------------ */
{

   fprintf(fp,"gc_f_type gc_f[] = {");
     for( ; *nms != NULL;  nms++ ) 
       fprintf(fp,(*(nms+1)==NULL)?"NULL":"NULL,");
   fprintf(fp,"};\n\n\n");

}/*do_gcfuncs*/

void do_gets(fp,nms,deps,nd )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
  short**deps;/* I */
  int  nd;    /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates gc_get_.... macros.
 *
 * ------------------------------ */
{
 int c,ind;
 int d;

 for( c =0; *nms != NULL;  c++, nms++ ) {
   fprintf(fp,"# ifdef DEBUG\n");
   fprintf(fp,"# define gc_get_%s() get_%s()\n",*nms,*nms);
   fprintf(fp,"# else\n");
   fprintf(fp,"# define gc_get_%s() \\\n",*nms);
   fprintf(fp,"   (gc_mcr_aux=( (!List_IsEmpty(gc_l.%s))\\\n",*nms);
   fprintf(fp,"        ?( (*gc_f[%d])(List_First(gc_l.%s)),List_ExtFirst(gc_l.%s) )\\\n",c,*nms,*nms);
   for(ind=0,d=FALSE; ind<nd && !d; ind++)
      d |= deps[c][ind];
   if (d) {   /* With dependencies */
      fprintf(fp,"        :( (%s_is_full()) \\\n",*nms);
      fprintf(fp,"           ?( gc_%s_freeFL())\\\n",*nms);
      fprintf(fp,"           :(%s_Malloc()) )\\\n",*nms);
      fprintf(fp,"   ),Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off))),gc_mcr_aux )\n\n");
   } else {  /* Without dependencies */
      fprintf(fp,"        :(%s_Malloc())\\\n",*nms);
      fprintf(fp,"   ),Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off))),gc_mcr_aux )\n");
   }
   fprintf(fp,"# endif\n\n");

 }
}/*do_gets*/


void do_getsDBG(fp,nms,deps,nd )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
  short**deps;/* I */
  int  nd;    /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates get_.... macros.
 *
 * ------------------------------ */
{
 int c,ind;
 int d;

 for( c =0; *nms != NULL;  c++, nms++ ) {
   fprintf(fp,"# ifdef DEBUG\n");
   fprintf(fp,"get_%s() \n",*nms);
   fprintf(fp,"{\n");
   fprintf(fp,"   if(!List_IsEmpty(gc_l.%s)) {\n",*nms);
   fprintf(fp,"       (*gc_f[%d])(List_First(gc_l.%s));\n",c,*nms);
   fprintf(fp,"       gc_mcr_aux=List_ExtFirst(gc_l.%s);\n",*nms);
   for(ind=0,d=FALSE; ind<nd && !d; ind++)
      d |= deps[c][ind];
   if (d) {   /* With dependencies */
      fprintf(fp,"   } else if(%s_is_full()) {\n",*nms);
      fprintf(fp,"        gc_mcr_aux=gc_%s_freeFL();\n",*nms);
      fprintf(fp,"   } else {\n");
      fprintf(fp,"        gc_mcr_aux=%s_Malloc();\n",*nms);
      fprintf(fp,"   }\n");
      fprintf(fp,"   Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off)));\\n");
      fprintf(fp,"   return ( gc_mcr_aux )\n");
   } else {  /* Without dependencies */
      fprintf(fp,"   } else {\n");
      fprintf(fp,"        gc_mcr_aux=%s_Malloc();\n",*nms);
      fprintf(fp,"   }\n");
      fprintf(fp,"   Gc_Set_Out(*((short *)(((char *)gc_mcr_aux)+gc_off)));\n");
      fprintf(fp,"   return ( gc_mcr_aux );\n");
   }
   fprintf(fp,"} /* get_%s */\n",*nms);
   fprintf(fp,"# endif\n\n");

 }
}/*do_getsDBG*/


void do_getsdecl(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Returns    :
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates gc_get_.... macro declarations.
 *
 * ------------------------------ */
{
 for( ; *nms != NULL; nms++ ) {
  fprintf(fp, "/*\n");
  fprintf(fp, " void *gc_get_%s();\n",*nms);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    : Pointer to an allocated %s node.\n",*nms);
  fprintf(fp, " * Global     : gc_l.\n");
  fprintf(fp, " * Comments   : takes a node of %s type from gc.\n",*nms);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  fprintf(fp, "# ifdef DEBUG\n");
  fprintf(fp, "void *get_%s();\n",*nms);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * Returns    : Pointer to an allocated %s node.\n",*nms);
  fprintf(fp, " * Global     : gc_l.\n");
  fprintf(fp, " * Comments   : takes a node of %s type from gc. NOT A MACRO: only for debugging.\n",*nms);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n");
  fprintf(fp, "# endif \n\n");
 }
}/*do_getsdecl*/


void do_puts(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates gc_put_... macros.
 *
 * ------------------------------ */

{
   for( ; *nms != NULL; nms++ ) {
     fprintf(fp,"\n#define gc_put_%s(e) \\\n",*nms);
     fprintf(fp,"   Gc_Set_In(*((short *)(((char *)p)+gc_off))); \\\n");  
     fprintf(fp,"   Gc_Set_Uncleaned(*((short *)(((char *)p)+gc_off))); \\\n");  
     fprintf(fp,"   List_Insert(gc_l.%s,(e))\n");
 }

}/*do_puts*/

void do_putsdecl(fp, nms )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
/* ------------------------------
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates gc_put_... macro declarations.
 *
 * ------------------------------ */

{
 for( ; *nms != NULL; nms++ ) {
  fprintf(fp, "/*\n");
  fprintf(fp, " void gc_put_%s( void *el );\n",*nms);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    :\n");
  fprintf(fp, " * Global     : gc_l.\n");
  fprintf(fp, " * Comments   : inserts a node of %s type into gc.\n",*nms);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");
 }
}/*do_putsdecl*/

void do_depvars(fp, nms,deps,nd, is_impl )
  FILE *fp;   /*I-O*/
  char **nms; /* I */
  short**deps;/* I */
  int  nd;    /* I */
  int  is_impl;/*I */
/* ------------------------------
 * Parameters : nms is a (null terminated)  array of names.
 *              deps is the matrix with dependencies.
 * Comments   : Generates  variables that hold flags to (de)activate
 *              the dependencies. Declares them as extern if is_impl
 *              hold '0'
 *
 * ------------------------------ */
{
  int ind1,ind2;

  fprintf(fp, "\n/*******************\n");
  fprintf(fp, " * \n");
  fprintf(fp, " *    Next comes the dependencies flags; their sintax is:\n");
  fprintf(fp, " *        gc_<father>_<son>_dep\n");
  fprintf(fp, " * \n");
  fprintf(fp, " *******************/\n");

  for(ind1=0; ind1<nd; ind1++) {
     for(ind2=0; ind2<nd; ind2++)
        if (deps[ind1][ind2])
           fprintf(fp, "   %s gc_%s_%s_dep%s;\n",(is_impl)?"":"extern",nms[ind1],nms[ind2],
                                                 (is_impl)?"=FALSE":"");
     fprintf(fp,"\n");
  }

}/*do_depvars*/

void do_depvarsmacr(fp,nms,deps,nd)
  FILE  *fp;   /*I-O*/
  char  **nms; /* I */
  short **deps;/* I */
  int   nd;    /* I */
/* ------------------------------
 * Parameters : nms is a (null terminated)  array of names.
 *              deps is the matrix with dependencies.
 * Comments   : Generates  macros to modify 
 *              variables that hold flags to (de)activate
 *              the dependencies.
 *
 * ------------------------------ */

{
  int ind1,ind2;

  fprintf(fp, "\n/*******************\n");
  fprintf(fp, " * \n");
  fprintf(fp, " *    Next comes the dependencies flags macros; their sintax is:\n");
  fprintf(fp, " *        GC_<father>_<son>_SetDep --> Sets the flag ON, indicating that\n");
  fprintf(fp, " *                                     really exists nodes with that dependency.\n");
  fprintf(fp, " *        GC_<father>_<son>_ClrDep --> Sets the flag OFF;\n");
  fprintf(fp, " * \n");
  fprintf(fp, "/*******************\n");

  for(ind1=0; ind1<nd; ind1++) {
     for(ind2=0; ind2<nd; ind2++)
        if (deps[ind1][ind2]) {
           fprintf(fp, "#define GC_%s_%s_SetDep  (gc_%s_%s_dep=TRUE)\n",
                       nms[ind1],nms[ind2],nms[ind1],nms[ind2]);
           fprintf(fp, "#define GC_%s_%s_ClrDep  (gc_%s_%s_dep=FALSE)\n",
                       nms[ind1],nms[ind2],nms[ind1],nms[ind2]);
        }
     fprintf(fp,"\n");
  }
}/*do_depvarsmacr*/

do_cleanfs( fp, nms )
  FILE *fp;
  char **nms;
/* ------------------------------
 * Parameters : nms is a  (null terminated)  array of names.
 * Comments   : Generates functions to clear nodes ( for gmm )
 *
 * ------------------------------ */

{
   int ind = 0;

   while( *nms != NULL ) do_cleanf(fp,*(nms++),ind++);

}/*do_cleanfs*/

do_cleanf( fp, nm, ind )
  FILE *fp;
  char *nm;
/* ------------------------------
 * Parameters : nm is a  name.
 * Comments   : Generates functions to clear nodes ( for gmm )
 *
 * ------------------------------ */

{
  fprintf(fp, "void gc_%s_cf( p )\n",nm);
  fprintf(fp, "  void *p;\n");
  fprintf(fp, "/* ------------------------------\n");
  fprintf(fp, " * Global     : gc_l.\n");
  fprintf(fp, " * Comments   : Releases p from GC and cleans p \n");
  fprintf(fp, " *\n");
  fprintf(fp, " * ------------------------------ */\n\n");
  fprintf(fp, "{\n ");
  fprintf(fp, " DEBUG_Init_Func(\"gc_%s_cf\");\n\n",nm);
  fprintf(fp, " if (gc_f[%d] != NULL && !(*((short*)(((char*)p)+gc_off)) & GC_CLEANED)) \n",ind);
  fprintf(fp, "    (*gc_f[%d])(p); \n", ind );
  fprintf(fp, " List_Extract(p);\n");
  fprintf(fp, "\n DEBUG_End_Func(\"gc_%s_cf\");\n",nm);
  fprintf(fp, "} /*gc_%s_cf*/\n\n",nm);

}/*do_cleanf*/


void do_freeFL(fp,nms,deps,nd,is_impl)
  FILE  *fp;    /*I-O*/
  char  **nms;  /* I */
  short **deps; /* I */
  int   nd;     /* I */
  int   is_impl;/* I */
/* ------------------------------
 * Parameters : 
 * Comments   : Generates the "clear father list" functions
 *
 * ------------------------------ */
{
   int num_deps;
   int father,son;

   for (son=0; son<nd; son++) {
      for(father=0,num_deps=0; father<nd && !num_deps; father++)
         num_deps = deps[father][son];
      if(num_deps) {   /* There is dependencies */
         fprintf(fp,"vadd_t gc_%s_freeFL()",nms[son]);
         if (!is_impl) {          /* Prototype */
            fprintf(fp,";\n");
            fprintf(fp,"/* ------------------------------\n");
            fprintf(fp," * Returns    : Virtual address for a %s node\n",nms[son]);
            fprintf(fp," * Global     : gc_l, gc_f\n");
            fprintf(fp," * Comments   : Frees up the father nodes gc lists until\n");
            fprintf(fp," *              there is at least one %s node in its gc list\n",nms[son]);
            fprintf(fp," *\n");
            fprintf(fp," * ------------------------------ */\n\n");
         } else {                 /* Implementation */
            fprintf(fp,"\n{\n");
            fprintf(fp,"   list_elem_ptr xn;\n\n");
            fprintf(fp,"   DEBUG_Init_Func(\"gc_%s_freeFL\");\n\n",nms[son]);
            for(father=0,num_deps=0; father<nd; father++) {
               if(deps[father][son]) {
                  num_deps++;
                  if (num_deps!=1) fprintf(fp,"\n   if (List_IsEmpty(gc_l.%s)) {\n",nms[son]);
                  fprintf(fp,"      xn = List_First(gc_l.%s);\n",nms[father]);
                  fprintf(fp,"      while(xn!=NULL && List_IsEmpty(gc_l.%s)) {\n",nms[son]);
                  fprintf(fp,"         gc_f[%d];\n",father);
                  fprintf(fp,"         xn = List_Next(xn);\n");
                  fprintf(fp,"      }\n");
                  if (num_deps!=1) fprintf(fp,"   }\n");
               }
            }
            fprintf(fp,"\n   DEBUG_End_Func(\"gc_%s_freeFL\");\n",nms[son]);
            fprintf(fp,"} /* gc_%s_freeFL */\n\n",nms[son]);
         }
      } /* if(num_deps) */
   } /* for */



} /* do_freeFL */


do_init( fp, nms )
  FILE *fp;
  char **nms;
/* ------------------------------
 * Parameters : nms is a (null terminated)  array of names.
 * Comments   : Generates the initialization function 
 *
 * ------------------------------ */
{
  int ind;

  fprintf(fp, "void gc_init(  )\n");
  fprintf(fp, "/* ------------------------------\n");
  fprintf(fp, " * Global     : gc_l.\n");
  fprintf(fp, " * Comments   : Initializes GC \n");
  fprintf(fp, " *\n");
  fprintf(fp, " * ------------------------------ */\n\n");
  fprintf(fp, "{\n");
  fprintf(fp, " DEBUG_Init_Func(\"gc_init\");\n\n");
  fprintf(fp, " gmm_set_inGCf(gc_inGC);\n\n");
  for ( ind=0 ; *nms != NULL ; ind++, nms++ ) {
    fprintf(fp, " gmm_set_cf(%d,gc_%s_cf);\n",ind,*nms);
    fprintf(fp, " gc_f[%d]=gc_null;\n\n",ind);
  }
  fprintf(fp, "\n DEBUG_End_Func(\"gc_init\");\n\n");
  fprintf(fp, "} /*gc_init*/\n\n");
 
}/*do_init*/



int main( argc, argv )
   int argc;
   char **argv;
{
  int  ind, ind2, ind3;
  char *prgName=*argv;

  FILE *impl = fopen("gcimpl.c","w");
  FILE *decl = fopen("gcdecl.h","w");
  FILE *macr = fopen("gcmacr.h","w");
  FILE *type = fopen("gctype.h","w");


  unsigned num_nodes = 0;  /* number of different nodes */
  char     **names;        /* names for nodes */
  short    **dep_matrix;    /* matrix of dependencies between nodes */
  char     *deps;          /* parameter that gives the dependencies */


  /* ****** Take arguments ... */
  argc--; argv++; /* take out who am i */
  for(ind=0; ind<argc; ind++)
      if (argv[ind][0]!='-') num_nodes++;
  if ( (names = (char **)calloc(num_nodes+1,sizeof(char*))) == NULL ||
  (dep_matrix = (short **)calloc(num_nodes , sizeof(short *))) == NULL){
    fprintf(stderr," %s: Not enough memory\n",prgName); exit(1);
  }
  for ( ind = 0; ind < num_nodes ; ind++ )
    if ( (dep_matrix[ind] = 
          (short *)calloc(num_nodes , sizeof(short ))) == NULL  ) {
       fprintf(stderr," %s: Not enough memory\n",prgName); exit(1);
    }

  if (  decl == NULL || impl == NULL || macr == NULL ) {
    fprintf(stderr," %s: Fail while opening file...\n",prgName); exit(1);
  } else if ( argc == 0 ||   ! extract_names( argv,names)  ){ 
    fprintf(stderr," Usage: %s [-dN1-N2,...] name1 [name2 ... ]\n",prgName); exit(1);
  } else if (! extract_deps( argc,argv, num_nodes, dep_matrix,names ) )
    exit(1);
 

  /* ***** ... and generate the gc files */

  /* Type declarations */

  fprintf(type,"\n\n/*======== CODE GENERATED BY mkgc ========*/\n\n");
  do_gctype(type,names);
  do_gcfuncdefs(type,names);
  fprintf(type,"\n# define GC_NLISTS %d\n",num_nodes); 
  fprintf(type,"\n\n/*===== END OF CODE GENERATED BY mkgc ====*/\n\n");
  fclose(type);

  /* C code */

  fprintf(impl,"\n\n/*======== CODE GENERATED BY mkgc ========*/\n\n");
  do_depvars(impl,names,dep_matrix,num_nodes,TRUE);
  do_gcfuncs(impl,names);
  do_getsDBG(impl,names);
  do_cleanfs(impl,names);
  do_freeFL(impl,names,dep_matrix,num_nodes,TRUE);
  do_init(impl,names);
  fprintf(impl,"\n\n/*===== END OF CODE GENERATED BY mkgc ====*/\n\n");
  fclose(impl);

  /* Function declarations and constants */

  fprintf(decl,"\n\n/*======== CODE GENERATED BY mkgc ========*/\n\n");
  do_depvars(decl,names,dep_matrix,num_nodes,FALSE);
  do_getsdecl(decl,names);
  do_putsdecl(decl,names);
  do_freeFL(decl,names,dep_matrix,num_nodes,FALSE);
  fprintf(decl,"\n\n/*===== END OF CODE GENERATED BY mkgc ====*/\n\n");
  fclose(decl);

  /* Macros */
  fprintf(macr,"\n\n/*======== CODE GENERATED BY mkgc ========*/\n\n");
  do_gets(macr,names);
  do_puts(macr,names);
  do_depvarsmacr(macr,names,dep_matrix,num_nodes);
  fprintf(macr,"\n\n/*===== END OF CODE GENERATED BY mkgc ====*/\n\n");
  fclose(macr);
  return( 0 );
} /* main */

/* ========== END OF FUNCTION IMPLEMENTATIONS ========*/
 
