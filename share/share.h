/* --------------------------------
 *
 *    File: @(#)share.h	1.1
 *	  Date: 4/25/91
 *    Module: share
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Shared objects header.
 * 
 *
 * --------------------- */ 

#ifndef __SHARE_H
#  define __SHARE_H 1

#define PRIVATE static
#define CONST 

#define CONF_MAX_INST_NAME 13

extern int CONF_MAX_PRG_SIZE;
extern int CONF_MAX_FUNC;
  
#define CONF_MAX_ARGS      10
#define CONF_MAX_INST_ARGS 4
#define CONF_MAX_NODES     1000
#define CONF_PRG_BEGIN     6


#define MEM_FAIL      1
#define HELP_FAIL     2         /* error result codes */
#define MISS_PRG_FAIL 3
#define INIT_FAIL     4
#define GRPH_FAIL     5
#define INPUT_FAIL    6


#define SUBS_FNAME_SIZE  30
#define SUBS_MAX_COL     80
#define SUBS_MAX_ROW     25

#ifndef size_t
#   define size_t unsigned
#endif


#ifndef TRUE
#   define TRUE (1)
#endif

#ifndef FALSE
#   define FALSE (0)
#endif

#ifndef NULL
#   define NULL (0)
#endif

#define forever while(1)
#define skip 

typedef char subs_fnameType[SUBS_FNAME_SIZE];

int qsortStrCmp( /* p1, p2 */ );
/* --------------------------------
 * Returns: The same as strcmp for qsort()
 * --------------------- */ 


#endif




