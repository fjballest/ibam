/******* CODE GENERATED BY mkgmm **************/

# define GMM_NUM_LIST 3

gmm_list_tp gmm_tsk_l ; /* list for tsk */

gmm_list_tp gmm_fun_l ; /* list for fun */

gmm_list_tp gmm_num_l ; /* list for num */

gmm_list_tp *gmm_listVect[GMM_NUM_LIST] = {
     &gmm_tsk_l,
     &gmm_fun_l,
     &gmm_num_l
};

char *gmm_swapBuff[GMM_NUM_LIST];

gmm_cf_tp gmm_cf[GMM_NUM_LIST] = { 
       NULL,NULL,NULL};

void gmm_init(  tsk_size, fun_size, num_size)
   size_t tsk_size; 
   size_t fun_size; 
   size_t num_size; 
/* ------------------------------ 
 * Returns    :
 * Use        : lists 
 * Global     : list structs
 * Parameters : the sizes for each list.
 * Comments   : Initializes the lists.
 *
 * ------------------------------ */
{
DEBUG_Init_Func("gmmimpl->gmm_init");

pg_init();
vadd_init();
blm_init();

gmm_tsk_l.data = gmm_tsk_l.pg  
   = gmm_tsk_l.next_nd = gmm_tsk_l.first = (void *)0;  
gmm_tsk_l.nd_size = tsk_size + sizeof(void *); 
gmm_tsk_l.nodes 
  = gmm_tsk_l.nds_pg = 
        (Page_Size - 2 * sizeof( void *)) /
        gmm_tsk_l.nd_size;
gmm_tsk_l.first_off = 2 * sizeof( void *);
if (!(gmm_swapBuff[0] = (char *)malloc(gmm_tsk_l.nd_size))) 
   err_fatal("Generic memory allocation error.\n"); 

gmm_fun_l.data = gmm_fun_l.pg  
   = gmm_fun_l.next_nd = gmm_fun_l.first = (void *)0;  
gmm_fun_l.nd_size = fun_size + sizeof(void *); 
gmm_fun_l.nodes 
  = gmm_fun_l.nds_pg = 
        (Page_Size - 2 * sizeof( void *)) /
        gmm_fun_l.nd_size;
gmm_fun_l.first_off = 2 * sizeof( void *);
if (!(gmm_swapBuff[1] = (char *)malloc(gmm_fun_l.nd_size))) 
   err_fatal("Generic memory allocation error.\n"); 

gmm_num_l.data = gmm_num_l.pg  
   = gmm_num_l.next_nd = gmm_num_l.first = (void *)0;  
gmm_num_l.nd_size = num_size + sizeof(void *); 
gmm_num_l.nodes 
  = gmm_num_l.nds_pg = 
        (Page_Size - 2 * sizeof( void *)) /
        gmm_num_l.nd_size;
gmm_num_l.first_off = 2 * sizeof( void *);
if (!(gmm_swapBuff[2] = (char *)malloc(gmm_num_l.nd_size))) 
   err_fatal("Generic memory allocation error.\n"); 

local_init_gmm(); 
DEBUG_End_Func("gmmimpl->gmm_init");


}/*gmm_init*/

char *gmm_tsk_malloc()
{
  list_elem_ptr new_page;


  DEBUG_Init_Func("gmm_tsk_malloc");

  if ( (new_page = Pg_Get_Page()) == (pg_t)(-1)) {
       gmm_compress( 0 );
       new_page = Pg_Get_Page();
  }
  if (new_page != (pg_t)(-1))  { 
     gmm_tsk_l.data    = List_Insert(gmm_tsk_l.data,(list_elem_ptr)new_page);
     gmm_tsk_l.pg      = new_page;
     gmm_tsk_l.first   = (char *)new_page +gmm_tsk_l.first_off;
     gmm_tsk_l.next_nd = gmm_tsk_l.first + gmm_tsk_l.nd_size;
     gmm_tsk_l.nodes   = gmm_tsk_l.nds_pg;
     DEBUG_End_Func("gmm_tsk_malloc");
     return(gmm_tsk_l.first);
  } else {
     DEBUG_End_Func("gmm_tsk_malloc");
     return( (char *)NULL );
  }
} /* gmm_tsk_malloc */

#ifdef DEBUG
char *tsk_malloc()
{

     DEBUG_Init_Func("tsk_malloc");

     gmm_mcr_aux = get_vadd();
     if (gmm_tsk_l.nodes--)  {
         gmm_tsk_l.next_nd = (gmm_mcr_aux2 =gmm_tsk_l.next_nd)+(gmm_tsk_l.nd_size);
         DEBUG_End_Func("tsk_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     } else {
         gmm_mcr_aux2=gmm_tsk_malloc();
         DEBUG_End_Func("tsk_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     }
} /* tsk_malloc */
#endif

char *gmm_fun_malloc()
{
  list_elem_ptr new_page;


  DEBUG_Init_Func("gmm_fun_malloc");

  if ( (new_page = Pg_Get_Page()) == (pg_t)(-1)) {
       gmm_compress( 1 );
       new_page = Pg_Get_Page();
  }
  if (new_page != (pg_t)(-1))  { 
     gmm_fun_l.data    = List_Insert(gmm_fun_l.data,(list_elem_ptr)new_page);
     gmm_fun_l.pg      = new_page;
     gmm_fun_l.first   = (char *)new_page +gmm_fun_l.first_off;
     gmm_fun_l.next_nd = gmm_fun_l.first + gmm_fun_l.nd_size;
     gmm_fun_l.nodes   = gmm_fun_l.nds_pg;
     DEBUG_End_Func("gmm_fun_malloc");
     return(gmm_fun_l.first);
  } else {
     DEBUG_End_Func("gmm_fun_malloc");
     return( (char *)NULL );
  }
} /* gmm_fun_malloc */

#ifdef DEBUG
char *fun_malloc()
{

     DEBUG_Init_Func("fun_malloc");

     gmm_mcr_aux = get_vadd();
     if (gmm_fun_l.nodes--)  {
         gmm_fun_l.next_nd = (gmm_mcr_aux2 =gmm_fun_l.next_nd)+(gmm_fun_l.nd_size);
         DEBUG_End_Func("fun_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     } else {
         gmm_mcr_aux2=gmm_fun_malloc();
         DEBUG_End_Func("fun_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     }
} /* fun_malloc */
#endif

char *gmm_num_malloc()
{
  list_elem_ptr new_page;


  DEBUG_Init_Func("gmm_num_malloc");

  if ( (new_page = Pg_Get_Page()) == (pg_t)(-1)) {
       gmm_compress( 2 );
       new_page = Pg_Get_Page();
  }
  if (new_page != (pg_t)(-1))  { 
     gmm_num_l.data    = List_Insert(gmm_num_l.data,(list_elem_ptr)new_page);
     gmm_num_l.pg      = new_page;
     gmm_num_l.first   = (char *)new_page +gmm_num_l.first_off;
     gmm_num_l.next_nd = gmm_num_l.first + gmm_num_l.nd_size;
     gmm_num_l.nodes   = gmm_num_l.nds_pg;
     DEBUG_End_Func("gmm_num_malloc");
     return(gmm_num_l.first);
  } else {
     DEBUG_End_Func("gmm_num_malloc");
     return( (char *)NULL );
  }
} /* gmm_num_malloc */

#ifdef DEBUG
char *num_malloc()
{

     DEBUG_Init_Func("num_malloc");

     gmm_mcr_aux = get_vadd();
     if (gmm_num_l.nodes--)  {
         gmm_num_l.next_nd = (gmm_mcr_aux2 =gmm_num_l.next_nd)+(gmm_num_l.nd_size);
         DEBUG_End_Func("num_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     } else {
         gmm_mcr_aux2=gmm_num_malloc();
         DEBUG_End_Func("num_malloc");
         return(vadd_map(gmm_mcr_aux,gmm_mcr_aux2));
     }
} /* num_malloc */
#endif

void gmm_clear()
{
   DEBUG_Init_Func("gmm_clear");

   vadd_clear();
   List_Join(pool,gmm_tsk_l.data);
   gmm_tsk_l.data = gmm_tsk_l.pg = gmm_tsk_l.first =
   gmm_tsk_l.next_nd = (void *)(gmm_tsk_l.nodes = 0);

   List_Join(pool,gmm_fun_l.data);
   gmm_fun_l.data = gmm_fun_l.pg = gmm_fun_l.first =
   gmm_fun_l.next_nd = (void *)(gmm_fun_l.nodes = 0);

   List_Join(pool,gmm_num_l.data);
   gmm_num_l.data = gmm_num_l.pg = gmm_num_l.first =
   gmm_num_l.next_nd = (void *)(gmm_num_l.nodes = 0);


   DEBUG_End_Func("gmm_clear");
} /* gmm_clear */

/******* END OF CODE GENERATED BY mkgmm *******/

