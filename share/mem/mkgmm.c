/* ------------------------------
 *
 * File       : @(#)mkgmm: Make graph Memory Manager. ( M.M. generator ).
 * Project    : Lbam-1.0
 * Date       : Oct-91
 * Module     : mkgmm
 * Programmer : Dylan L. Hoffman  / Franc. J. Ballesteros
 *
 * Comments   : This program generates a m.m. source C files.
 * 
 * ------------------------------ */

/* ========== DEPENDENCIES ========== */

# include <stdio.h>
# include <ctype.h>

/* ========== END OF DEPENDENCIES ========== */


/* ========== SYMBOL DEFINITIONS ========== */

# define FALSE 0
# define TRUE 1

/* ========== SYMBOL DEFINITIONS ========== */


/* ========== FUNCTION IMPLEMENTATIONS ========== */

init_b_impl( c, v, fp , hdr)
   int c;     /* I */
   char **v;  /* I */
   FILE *fp;  /*I-O*/
   int hdr;   /* I */
/* ------------------------------
 * Parameters : fp is the file where begin of gmm_init must be dumped on.
 *              c is the number of strings at v. ( names for lists ).
 *              If hdr is non-zero the declaration is dumped for
 *              a prototipe, otherwise is dumped for a function 
 *              implementation ( '{' included ).
 * Comments   : writes the init function header at fp, 
 *              if hdr writes a prototipe.
 *
 * ------------------------------ */
{ 
  int ind;

  fprintf(fp,"void gmm_init( ");
  if ( hdr ) fprintf(fp,"/*");
  fprintf(fp," %s_size",*v);
  for( ind =1; ind < c; ind++ )
    fprintf(fp,", %s_size",v[ind]);
  if ( hdr ) {
      fprintf(fp,"*/);\n");
      fprintf(fp,"/* ------------------------------ \n");
      fprintf(fp," * Use        : lists \n");
      fprintf(fp," * Global     : list structs\n");
      fprintf(fp," * Parameters : the sizes for each list.\n");
      fprintf(fp," * Comments   : Initializes the lists.\n");
      fprintf(fp," *\n");
      fprintf(fp," * ------------------------------ */\n");
  } else {
    fprintf(fp,")\n");
    for( ind =0; ind < c; ind++ )
      fprintf(fp,"   size_t %s_size; \n",v[ind]);
    fprintf(fp,"/* ------------------------------ \n");
    fprintf(fp," * Returns    :\n");
    fprintf(fp," * Use        : lists \n");
    fprintf(fp," * Global     : list structs\n");
    fprintf(fp," * Parameters : the sizes for each list.\n");
    fprintf(fp," * Comments   : Initializes the lists.\n");
    fprintf(fp," *\n");
    fprintf(fp," * ------------------------------ */\n");
    fprintf(fp,"{\n");
  }
}/*init_b_impl*/

void do_listVect(c, v, fp)
  int c;  /* I */
  char **v; /* I */
  FILE *fp;
{
  int ind;

  fprintf(fp, "gmm_list_tp *gmm_listVect[GMM_NUM_LIST] = {\n");
  fprintf(fp, "     &gmm_%s_l",v[0]);
  for( ind =1; ind < c; ind++ )
    fprintf(fp,",\n     &gmm_%s_l",v[ind]);
  fprintf(fp, "\n};\n\n");

  fprintf(fp, "char *gmm_swapBuff[GMM_NUM_LIST];\n\n");

  fprintf(fp, "gmm_cf_tp gmm_cf[GMM_NUM_LIST] = { \n       NULL");
  for( ind =1; ind < c; ind++ )
    fprintf(fp,",NULL");
  fprintf(fp, "};\n\n");


} /* do_listVect */

void do_listenums(c, v, fp)
  int c;  /* I */
  char **v; /* I */
  FILE *fp;
{
  int ind;

  for( ind =0; ind < c; ind++ )
    fprintf(fp,"\n# define GMM_%s_L  %d\n",v[ind],ind);


} /* do_listenums */



init_e_impl(fp )
  FILE *fp; /*I-O*/
/* ------------------------------
 * Parameters : fp is the file where end of gmm_init must be dumped on.
 * Comments   : dumps end of gmm_init at fp.
 *
 * ------------------------------ */
{ 
   fprintf(fp,"local_init_gmm(); \n");
   fprintf( fp,"DEBUG_End_Func(\"gmmimpl->gmm_init\");\n\n");
   fprintf(fp,"\n}/*gmm_init*/\n\n"); 
}/*init_e_impl*/

data_impl( l, fp)
  char *l; /* I */
  FILE *fp;/*I-O*/
/* ------------------------------
 * Parameters : l is the list whose declarations must be dumped to fp.
 * Comments   : Dumps declaration of struct for list l.
 *
 * ------------------------------ */
{
 fprintf(fp,
    "gmm_list_tp gmm_%s_l ; /* list for %s */\n\n",
    l,l );

}/*data_impl*/

data_decl( l, fp)
  char *l; /* I */
  FILE *fp;/*I-O*/
/* ------------------------------
 * Parameters : l is the list whose declarations must be dumped to fp.
 * Comments   : Dumps extern declaration of struct for list l.
 *
 * ------------------------------ */
{
 fprintf(fp,
    "extern gmm_list_tp gmm_%s_l ; /* list for %s */\n\n",
    l,l );

}/*data_decl*/

init_impl( c, v, fp )
   int  c;  /* I */
   char **v;/* I */
   FILE *fp;/*I-O*/
/* ------------------------------
 * Parameters :
 * Comments   : Dumps declaration of `inline' constructor for lists.
 *
 * ------------------------------ */
/* write macro definition for l constructor in fp */
{
  int ind;
  fprintf( fp,"DEBUG_Init_Func(\"gmmimpl->gmm_init\");\n\n");
  fprintf( fp,"pg_init();\n");
  fprintf( fp,"vadd_init();\n");
  fprintf( fp,"blm_init();\n\n");
  for( ind = 0; ind < c ; ind++ ) {
      fprintf( fp,"gmm_%s_l.data = gmm_%s_l.pg  \n",v[ind],v[ind]);
      fprintf( fp,"   = gmm_%s_l.next_nd = gmm_%s_l.first = (void *)0;  \n",v[ind],v[ind]);
      fprintf( fp,"gmm_%s_l.nd_size = %s_size + sizeof(void *); \n",v[ind],v[ind]);
      fprintf( fp,"gmm_%s_l.nodes \n",v[ind]);
      fprintf( fp,"  = gmm_%s_l.nds_pg = \n",v[ind]);
      fprintf( fp,"        (Page_Size - 2 * sizeof( void *)) /\n");
      fprintf( fp,"        gmm_%s_l.nd_size;\n",v[ind]);
      fprintf( fp,"gmm_%s_l.first_off = 2 * sizeof( void *);\n",v[ind]);

      fprintf( fp,"if (!(gmm_swapBuff[%d] = (char *)malloc(gmm_%s_l.nd_size))) \n",ind,v[ind]);
      fprintf( fp,"   err_fatal(\"Generic memory allocation error.\\n\"); \n\n");

  }
    
}/*init_impl*/

void macro_decl(l,fp)
  char *l;
  FILE *fp;
/* ------------------------------
 * Parameters : l is the list whose declarations must be dumped to fp.
 * Comments   : Dumps declaration of macros for list l.
 *
 * ------------------------------ */
{
  fprintf(fp, "/*\n * ********** MACROS FOR %s NODES **********\n */\n",l);

  /* Macro for malloc */
  fprintf(fp, "/*\n");
  fprintf(fp, " char *%s_Malloc(size_t %s_size);\n",l,l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    : Pointer to an allocated %s node.\n",l);
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " * Parameters : size of a %s node.\n",l);
  fprintf(fp, " * Comments   : allocates a node of %s type.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  /* Macro for is_full */
  fprintf(fp, "/*\n");
  fprintf(fp, " int %s_is_full();\n",l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    : Non zero if there is no room for  %s node.\n",l);
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");


} /* macro_decl */

void macro_impl(l,fp)
  char *l;  /* I */
  FILE *fp; /*I-O*/
/* ------------------------------
 * Parameters : l is the list whose macros must be dumped to fp.
 * Comments   : Dumps macros for list l.
 *
 * ------------------------------ */
{
  fprintf(fp, "/*\n * ********** MACROS FOR %s NODES **********\n */\n",l);
  /* Macro for malloc */
  fprintf(fp, "# ifdef DEBUG\n");
  fprintf(fp, "#   define %s_Malloc()   %s_malloc()\n",l,l);
  fprintf(fp, "# else\n");
  fprintf(fp, "#   define %s_Malloc() \\\n",l);
  fprintf(fp, "     ((gmm_mcr_aux = get_vadd()), \\\n");
  fprintf(fp, "     ( (gmm_%s_l.nodes--)  \\\n",l);
  fprintf(fp, "        ? (gmm_%s_l.next_nd = (gmm_mcr_aux2 =gmm_%s_l.next_nd)+(gmm_%s_l.nd_size), \\\n",l,l,l);
  fprintf(fp, "           vadd_map(gmm_mcr_aux,gmm_mcr_aux2) ) \\\n");
  fprintf(fp, "        : (gmm_mcr_aux2=gmm_%s_malloc(),vadd_map(gmm_mcr_aux,gmm_mcr_aux2))  ))\n",l);
  fprintf(fp, "#endif\n\n");

  /* Macro to find if there is no room for a node in current page. */
  fprintf(fp,"# define %s_is_full()\\\n");
  fprintf(fp,"     (gmm_%s_l.nodes==0)\n\n",l);

  

} /* macro_impl */

void get_mem_impl(l,which_l,fp,hdr)
  char *l;      /* I */
  int  which_l; /* I */
  FILE *fp;     /*I-O*/
  int hdr;      /* I */
/* ------------------------------
 * Parameters : l is the name for the list being processed.
 *              fp is the file where we're dumping the functions.
 *              If hdr is non-zero a prototipe-like declaration
 *                is dumped, otherwise the header for the function
 *              `{' inclusive is dumped.
 * Comments   : Dumps the functions to get memory: <list>_malloc, gmm_<list>_malloc.
 *
 * ------------------------------ */
 
{
  fprintf(fp, "char *gmm_%s_malloc()",l);
  if (hdr)  { /* Prototype */
     fprintf(fp, ";\n");
     fprintf(fp, "/* ------------------------------\n");
     fprintf(fp, " * Returns    : Pointer to allocated %s node; NULL if error.\n",l);
     fprintf(fp, " * Global     : gmm_%s_l.\n",l);
     fprintf(fp, " * Comments   : Get a new page and allocates a %s node\n",l);
     fprintf(fp, " *\n");
     fprintf(fp, " * ------------------------------ */\n\n");
  } else {    /* Implementation */
     fprintf(fp, "\n{\n");
     fprintf(fp, "  list_elem_ptr new_page;\n\n");
     fprintf(fp, "\n  DEBUG_Init_Func(\"gmm_%s_malloc\");\n\n",l);
     fprintf(fp, "  if ( (new_page = Pg_Get_Page()) == (pg_t)(-1)) {\n");
     fprintf(fp, "       gmm_compress( %d );\n",which_l);
     fprintf(fp, "       new_page = Pg_Get_Page();\n");
     fprintf(fp, "  }\n");
     fprintf(fp, "  if (new_page != (pg_t)(-1))  { \n");
     fprintf(fp, "     gmm_%s_l.data    = List_Insert(gmm_%s_l.data,(list_elem_ptr)new_page);\n",l,l);
     fprintf(fp, "     gmm_%s_l.pg      = new_page;\n",l);
     fprintf(fp, "     gmm_%s_l.first   = (char *)new_page +gmm_%s_l.first_off;\n",l,l);
     fprintf(fp, "     gmm_%s_l.next_nd = gmm_%s_l.first + gmm_%s_l.nd_size;\n",l,l,l);
     fprintf(fp, "     gmm_%s_l.nodes   = gmm_%s_l.nds_pg;\n",l,l);
     fprintf(fp, "     DEBUG_End_Func(\"gmm_%s_malloc\");\n",l);
     fprintf(fp, "     return(gmm_%s_l.first);\n",l);
     fprintf(fp, "  } else {\n");
     fprintf(fp, "     DEBUG_End_Func(\"gmm_%s_malloc\");\n",l);
     fprintf(fp, "     return( (char *)NULL );\n");
     fprintf(fp, "  }\n");
     fprintf(fp, "} /* gmm_%s_malloc */\n\n",l);
  }


  fprintf(fp, "#ifdef DEBUG\n");
  fprintf(fp, "char *%s_malloc()",l);
  if (hdr)  { /* Prototype */
     fprintf(fp, ";\n");
     fprintf(fp, "/* ------------------------------\n");
     fprintf(fp, " * Returns    : Pointer to allocated %s node; NULL if error.\n",l);
     fprintf(fp, " * Global     : gmm_%s_l.\n",l);
     fprintf(fp, " * Comments   : Get allocates a %s node. It's only executed when in DEBUG mode.\n",l);
     fprintf(fp, " *              Otherwise the equivalent macro is executed.\n");
     fprintf(fp, " *\n");
     fprintf(fp, " * ------------------------------ */\n");
  } else {    /* Implementation */
     fprintf(fp, "\n{\n");
     fprintf(fp, "\n     DEBUG_Init_Func(\"%s_malloc\");\n\n",l);
     fprintf(fp, "     gmm_mcr_aux = get_vadd();\n");
     fprintf(fp, "     if (gmm_%s_l.nodes--)  {\n",l);
     fprintf(fp, "         gmm_%s_l.next_nd = (gmm_mcr_aux2 =gmm_%s_l.next_nd)+(gmm_%s_l.nd_size);\n",l,l,l);
     fprintf(fp, "         DEBUG_End_Func(\"%s_malloc\");\n",l);
     fprintf(fp, "         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));\n");
     fprintf(fp, "     } else {\n");
     fprintf(fp, "         gmm_mcr_aux2=gmm_%s_malloc();\n",l);
     fprintf(fp, "         DEBUG_End_Func(\"%s_malloc\");\n",l);
     fprintf(fp, "         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));\n");
     fprintf(fp, "     }\n");
     fprintf(fp, "} /* %s_malloc */\n",l);
  }
  fprintf(fp, "#endif\n\n");

} /* get_mem_impl */


void clear_impl(c,v,fp,hdr)
  int c;    /* I */
  char **v; /* I */
  FILE *fp; /*I-O*/
  int hdr;  /* I */
/* ------------------------------
 * Parameters : c si the number of strings that v contains.
 *              fp is the file where we're dumping the functions.
 *              If hdr is non-zero a prototipe-like declaration
 *                is dumped, otherwise the header for the function
 *              `{' inclusive is dumped.
 * Comments   : Dumps the function to clear memory: gmm_clear.
 *
 * ------------------------------ */
{
  int ind;

  fprintf(fp, "void gmm_clear()");
  if (hdr) {    /* Prototype */
     fprintf(fp, ";\n");
     fprintf(fp, "/* ------------------------------\n");
     fprintf(fp, " * Global     : All page lists; pool.\n");
     fprintf(fp, " * Comments   : Moves all memory lists to the pool list.\n");
     fprintf(fp, " *\n");
     fprintf(fp, " * ------------------------------ */\n\n");
  } else {      /* Implementation */
     fprintf(fp, "\n{\n");
     fprintf(fp, "   DEBUG_Init_Func(\"gmm_clear\");\n\n");
     fprintf(fp, "   vadd_clear();\n");
     for( ind=0; ind<c; ind++) {
        fprintf(fp, "   List_Join(pool,gmm_%s_l.data);\n",v[ind]);
        fprintf(fp, "   gmm_%s_l.data = gmm_%s_l.pg = gmm_%s_l.first =\n",v[ind],v[ind],v[ind]);
        fprintf(fp, "   gmm_%s_l.next_nd = (void *)(gmm_%s_l.nodes = 0);\n\n",v[ind],v[ind]);
     }
     fprintf(fp, "\n   DEBUG_End_Func(\"gmm_clear\");\n");
     fprintf(fp, "} /* gmm_clear */\n\n");
  }
} /* clear_impl */




/* ========== END OF FUNCTION IMPLEMENTATIONS ========== */



main( argc, argv )
   int argc;
   char **argv;
{
  int  ind;
  char *prgName=*argv;
  FILE *impl = fopen("gmmimpl.c","w");
  FILE *decl = fopen("gmmdecl.h","w");
  FILE *macr = fopen("gmmmacr.h","w");

  argc--; argv++; /* take out who am i */
  if ( argc == 0 ){ 
    fprintf(stderr," Usage: %s name1 [name2 ... ]\n",prgName); exit(1);
  } else if (  decl == NULL || impl == NULL || macr == NULL  ) {
    fprintf(stderr," %s: Fail while opening file...\n",prgName); exit(1);
  }

  /*
   * Generate "./gmmimpl.c"
   */
  fprintf(impl,"/******* CODE GENERATED BY mkgmm **************/\n\n");
  fprintf(impl,"# define GMM_NUM_LIST %d\n\n",argc);
  for( ind = 0; ind < argc ; ind++ ) { /* structures for page lists */
     data_impl( argv[ind],impl );
  }

  do_listVect(argc,argv,impl);

  init_b_impl( argc, argv, impl , FALSE);
  init_impl( argc, argv,impl );
  init_e_impl(impl);

  for( ind=0; ind<argc; ind++ )  {     /* implementation of get_mem functions */
     get_mem_impl(argv[ind],ind,impl,FALSE);
  }

  clear_impl(argc,argv,impl,FALSE);    /* implementation of clear function */

  
  fprintf(impl,"/******* END OF CODE GENERATED BY mkgmm *******/\n\n");
  fclose(impl);

  /*
   * Generate "./gmmdecl.h"
   */
  fprintf(decl,"/******* CODE GENERATED BY mkgmm **************/\n\n");
  do_listenums(argc, argv,decl);
  fprintf(decl,"# define GMM_NUM_LIST %d\n\n",argc);
  for( ind = 0; ind < argc ; ind++ ) {
     data_decl( argv[ind],decl);
  }

  init_b_impl(argc,argv,decl,TRUE);
  for( ind=0; ind < argc ; ind++) {
     macro_decl(argv[ind],decl);
  }

  for( ind=0; ind<argc; ind++ )  {     /* prototypes of get_mem functions */
     get_mem_impl(argv[ind],ind,decl,TRUE);
  }

  clear_impl(argc,argv,decl,TRUE);    /* prototype of clear function */


  fprintf(decl,"/******* END OF CODE GENERATED BY mkgmm *******/\n\n");
  fclose(decl);

  /*
   * Generate "./gmmmacr.h"
   */
  fprintf(macr,"/******* CODE GENERATED BY mkgmm **************/\n\n");
  for( ind=0; ind < argc ; ind++) {
     macro_impl(argv[ind],macr);
  }

  fprintf(macr,"/******* END OF CODE GENERATED BY mkgmm *******/\n\n");
  fclose(macr);

  return(0);
}/*main*/
