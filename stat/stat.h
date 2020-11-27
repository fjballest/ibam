/* --------------------------------
 *
 *    File: @(#)stat.h   1.0
 *    Date: 4/22/91
 *    Module: Statistics (stat ).
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Provides a data structure for statistics
 *              and macros to update it.
 * 
 *
 * --------------------- */ 

#ifndef __STAT_H
#  define __STAT_H 1

extern int stat_sta_flag ;

extern struct stat_staStruct {
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
    } stat_sta;

# define stat_incInstructions()      stat_sta.instructions++
# define stat_incFails()             stat_sta.fails++
# define stat_incReductions()        stat_sta.reductions++
# define stat_incFuncNodes()         stat_sta.funcNodes++
# define stat_decFuncNodes()         stat_sta.funcNodes--
# define stat_incDisposedNodes()     stat_sta.disposedNodes++
# define stat_decnDisposedNodes(n)   \
         stat_sta.disposedNodes=stat_sta.disposedNodes-(n)
# define stat_incTaskNodes()         stat_sta.taskNodes++
# define stat_decTaskNodes()         stat_sta.taskNodes--
# define stat_decnVarNodes(n)        stat_sta.varNodes=stat_sta.varNodes-(n)
# define stat_incnVarNodes(n)        stat_sta.varNodes=stat_sta.varNodes+(n)
# define stat_incnCreatedNodes(n)    \
         stat_sta.createdNodes=stat_sta.createdNodes+(n)
# define stat_incNumbNodes()         stat_sta.numbNodes++
# define stat_decNumbNodes()         stat_sta.numbNodes--
# define stat_incConstNodes()        stat_sta.constNodes++
# define stat_decConstNodes()        stat_sta.constNodes--
# define stat_incConstrNodes()        stat_sta.constrNodes++
# define stat_decConstrNodes()        stat_sta.constrNodes--


void stat_showSta();
/* --------------------------------
 * Globals: stat_sta
 * Req.:    stat_sta initialized
 * Comments: Prints a statistics report calling misc functions.
 *  
 * --------------------- */ 

# endif





