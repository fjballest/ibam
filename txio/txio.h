
/* --------------------------------
 *
 *    File: @(#)txio.h   1.1
 *     Date: 4/19/91
 *    Module:   Text I/O ( txio ).
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports "portable" ( ? ) i/o functions.
 * 
 *
 * --------------------- */

# ifndef __TXIO_H
# define __TXIO_H 1


# define txio_printf txio_printstr
# define MISC_NO_EXIT  -1

void txio_printstr( /* frm, ... */ );
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `printf'
 *  
 * --------------------- */ 

char *txio_getstr( /*str*/ );
/* --------------------------------
 * Returns: pointer to readed string.
 * Globals: "all"
 * Req.:  screen initd.
 * Comments: a `gets'
 *  
 * --------------------- */ 

int txio_getch();
/* --------------------------------
 * Returns: next input char.
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `getch'
 *  
 * --------------------- */ 

int txio_putchar( /*ch*/ );
/* --------------------------------
 * Returns: ch
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `putchar'
 *  
 * --------------------- */ 

void txio_waitstroke();
/* --------------------------------
 * Returns: delays until a key is pressed.
 * Globals: "all"
 * Req.: screen initd.
 * --------------------- */ 

void txio_initscr();
/* --------------------------------
 * Globals: "all"
 * Comments: initializes screen.
 *  
 * --------------------- */ 

void txio_endscr();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Terminates screen
 *  
 * --------------------- */ 

void txio_fatal( /*msg */);
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: reports a fatal error msg. and 
 *           terminates screen and execution.
 *           returns `-1' to system.
 * --------------------- */ 


void txio_clrstdin();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: clean input buffer.
 *  
 * --------------------- */ 

void txio_clrstdout();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: clear screen.
 *  
 * --------------------- */ 

void txio_exit(/*code*/);
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: terminates screen an exits with  code.
 *  
 * --------------------- */ 

void txio_attrBold();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns on Bold writting mode.
 *  
 * --------------------- */ 

void txio_attrnoBold();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns off Bold writting mode
 *  
 * --------------------- */ 


void txio_attrInv();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns on inverse video mode.
 *  
 * --------------------- */ 

void txio_attrnoInv();
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns off inverse video mode.
 *  
 * --------------------- */ 


int txio_lnscr( /*name*/ );
/* --------------------------------
 * Returns: non-zero if error.
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Opens fname and dumps stdout to it.
 *  
 * --------------------- */ 



# endif


