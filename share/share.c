/* --------------------------------
 *
 *    File: @(#)share.c	1.1
 *	  Date: 4/22/91
 *    Module: share
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Shared objects.
 * 
 *
 * --------------------- */ 

int CONF_MAX_PRG_SIZE = 500; 	/* Max. program length         */
int CONF_MAX_FUNC     = 100;    /* Number of function names    */

/*
int CONF_MAX_CONST    = 30;     * Max. number of constants    *
int CONF_MAX_CONSTR   = 30;     * Max. number of constructors *
*/

int qsortStrCmp( src , dst )
void * src;
void * dst;
/* --------------------------------
 * Returns: The same as strcmp for qsort()
 * --------------------- */ 

{
        return strcmp( (char *)src,(char *)dst);

}/* qsortStrCmp */

