/* --------------------------------
 *
 *    File: @(#)stat.c   1.0
 *     Date: 4/22/91
 *    Module: Statistics (stat ).
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Provides a data structure for statistics
 *              and macros to update it.
 * 
 *
 * --------------------- */ 

/*===================== DEPENDENCIES ===============================*/

# include "../share/share.h"
# include "../txio/txio.h"

/*===================== END OF DEPENDENCIES ========================*/

int stat_sta_flag = FALSE;

struct stat_staStruct {
   int createdNodes;
   int disposedNodes;
   int numbNodes;
   int constNodes;
   int constrNodes;
   int varNodes;
   int taskNodes;
   int funcNodes;
   int instructions;
   int reductions;
   int fails;
} stat_sta        = {
   0,0,0,0,0,0,0,0,0,0,0};


void stat_showSta()
/* --------------------------------
 * Globals: stat_sta
 * Req.:    stat_sta initialized
 * Comments: Prints a statistics report calling misc functions.
 *  
 * --------------------- */ 

{
   extern int txio_refresh_flag;

   txio_refresh_flag = FALSE;
   txio_printstr("\n ******** Some statistics *********** \n");
   txio_printstr("    Created  nodes: %d\n",stat_sta.createdNodes);
   txio_printstr("    Disposed nodes: %d\n",stat_sta.disposedNodes);
   txio_printstr("    Nodes in graph:\n");
   txio_printstr("        Number:   %d\n",stat_sta.numbNodes);
   txio_printstr("        Constant: %d\n",stat_sta.constNodes);
   txio_printstr("        Term.:    %d\n",stat_sta.constrNodes);
   txio_printstr("        Var.:     %d\n",stat_sta.varNodes);
   txio_printstr("        Task:     %d\n",stat_sta.taskNodes);
   txio_printstr("        Func.:    %d\n",stat_sta.funcNodes);
   txio_printstr("                ----------- \n");
   txio_printstr("        TOTAL:    %d\n",
       stat_sta.numbNodes   + stat_sta.constNodes +
       stat_sta.constrNodes + stat_sta.varNodes +
       stat_sta.taskNodes   + stat_sta.funcNodes   );
   txio_printstr("    %d instructions executed, %d reductions, %d fails.\n",
       stat_sta.instructions, stat_sta.reductions, stat_sta.fails);
   txio_refresh_flag = TRUE;
   txio_printstr(" ************************************ \n");
}/*stat_showSta*/





