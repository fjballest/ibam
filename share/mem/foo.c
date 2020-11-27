  /* Iterator macros ... */


  fprintf(fp,"# define %s_init_itr() \\\n",l);
  fprintf(fp,"   gmm_%s_l.itr_count = 0;\\\n",l);
  fprintf(fp,"   gmm_%s_l.itr_pg = data;\\\n",l);
  fprintf(fp,"   gmm_%s_l.itr_next_nd = (!gmm_%s_l.itr_pg)\\\n",l,l);
  fprintf(fp,"       ?(0) :(((char *)data)+gmm_%s_l.first_off)\n\n",l);

  fprintf(fp,"# define %s_init_itr_blk() \\\n",l);
  fprintf(fp,"   gmm_%s_l.itr_count = 0;\\\n",l);
  fprintf(fp,"   gmm_%s_l.itr_next_nd = ((gmm_%s_l.itr_pg)\\\n",l,l);
  fprintf(fp,"       ?((char*)gmm_%s_l.itr_pg+gmm_%s_l.first_off):(0))\n\n",l,l);

  fprintf(fp,"# define %s_at_end_itr() \\\n",l);
  fprintf(fp,"     (gmm_%s_l.itr_next_nd==gmm_%s_l.next_nd )\n\n",l,l);

  fprintf(fp,"# define %s_at_end_itr_blk() \\\n",l);
  fprintf(fp,"     (gmm_%s_l.itr_next_nd==gmm_%s_l.next_nd || \\\n",l,l);
  fprintf(fp,"       gmm_%s_l.nds_pg == gmm_%s_l.itr_count)\n\n",l,l);

  fprintf(fp,"# define %s_itr_next() \\\n",l);
  fprintf(fp,"     ((gmm_%s_l.itr_next_nd) \\\n",l);
  fprintf(fp,"      ?( (gmm_%s_l.itr_next_nd==gmm_%s_l.next_nd)\\\n",l,l);
  fprintf(fp,"          ?(0)\\\n");
  fprintf(fp,"          :( (gmm_%s_l.nds_pg==gmm_%s_l.itr_count)\\\n",l,l);
  fprintf(fp,"             ?(mcr_aux=(void *)List_Next(gmm_%s_l.itr_pg)+gmm_%s_l.first_off,\\\n",l,l);
  fprintf(fp,"               gmm_%s_l.itr_next_nd=mcr_aux+gmm_%s_l.nd_size,\\\n",l,l);
  fprintf(fp,"               mcr_aux)\\\n");
  fprintf(fp,"             :(gmm_%s_l.itr_next_nd+=gmm_%s_l.nd_size,gmm_%s_l.itr_count+=1,\\\n",l,l,l);
  fprintf(fp,"               gmm_%s_l.itr_next_nd-gmm_%s_l.nd_size ) )) \\\n",l,l);
  fprintf(fp,"      :(0) ) \n\n");
  /* Iterator macros ... */

  fprintf(fp, "/*\n");
  fprintf(fp, " void %s_init_itr();\n",l,l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " * Comments   : Initializes iterator for  %s node.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  fprintf(fp, "/*\n");
  fprintf(fp, " void %s_init_itr_blk();\n",l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " * Comments   : Initializes iterator at current block for  %s node.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  fprintf(fp, "/*\n");
  fprintf(fp, " int %s_at_end_itr();\n",l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    : non zero if itr is at last %s node.\n",l);
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  fprintf(fp, "/*\n");
  fprintf(fp, " int %s_at_end_itr_blk();\n",l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    : non zero if itr is at last %s node in current block.\n",l);
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");

  fprintf(fp, "/*\n");
  fprintf(fp, " void *%s_itr_next();\n",l);
  fprintf(fp, " * ------------------------------\n");
  fprintf(fp, " * MACRO !!\n");
  fprintf(fp, " * Returns    :  Moves iterator.\n",l);
  fprintf(fp, " * Global     : gmm_%s_l.\n",l);
  fprintf(fp, " *\n");
  fprintf(fp, " * ---------------------------- */\n\n");
