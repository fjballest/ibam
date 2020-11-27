/* --------------------------------
 *
 *    File: @(#)txio.c   1.1
 *     Date: 4/19/91
 *    Module:   Miscellaneous ( misc )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports "portable" ( ? ) i/o functions.
 * 
 *
 * --------------------- */

# include "../share/defs.h"

# if ATT || SPARC
#   include <varargs.h>
# else
#   include <stdarg.h>
# endif


# include <stdio.h>
# include <ctype.h>

/* Select io library */
# ifdef CURSES
#   include <curses.h>
# endif
# ifdef TURBOC
#   include <conio.h>
# endif

# include "../share/share.h"

/* define max row value */
# ifndef MAXROW
#       define MAXROW 25
# endif

# ifndef MAXCOL
#   define MAXCOL 80
# endif

int txio_scrinitd      = FALSE; /* initialization done              */
int txio_lines_printed = 0;     /* to scroll window                 */
int txio_scroll_set    = TRUE;  /* allow scroll without pause       */
int txio_refresh_flag  = TRUE;  /* default refresh for <<printf>>   */
int txio_dump_enable   = TRUE;  /* echoing output enable            */

FILE *txio_dump = NULL;

#ifdef CURSES
WINDOW *output;
#else 
void *output = NULL;
#endif 

# ifndef TURBOC
void txio_printstr( va_alist  )
va_list va_alist;

# else 

void txio_printstr( char *format, ... )
# endif 
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `printf'
 *  
 * --------------------- */ 
{
   va_list pvar;
   int type  = 0;
   char myformat[10];
# ifdef TURBOC
   va_start(pvar,format);
# else 
   char *format;
   va_start(pvar);
# endif

   strcpy(myformat,"");
#   ifndef TURBOC
   format = va_arg(pvar, char *);
#   endif

   for ( ; *format!= (char)0 ; format++ ) { /* print format with args. */
      switch( *format ) {
         /* special chars */
      case '%':
         if ( type ) {   /* a scape to % */
            type = 0;
# ifdef CURSES
            waddch(output,*format);
# else
            putchar(*format);
# endif
            if ( txio_dump_enable && txio_dump != NULL )
               putc(*format,txio_dump);
         }
         else {    /* format indication begin */
            strcpy( myformat,"%");
            type = 1;
         }
         break;
      case '\n':
         if ( txio_lines_printed < MAXROW -1){
            txio_lines_printed++;
# ifdef CURSES
            wprintw(output,"\n");
# else 
            printf("\n");
# endif 
         }
         else{   /* scroll up if allowed */
            if (!txio_scroll_set){
# ifdef CURSES
               wrefresh(output);
# endif 
               txio_getch();
            }
# ifdef CURSES
            scroll(output);
            wprintw(output,"\n");
# else
            printf("\n");
# endif 
         }

         if ( txio_dump_enable && txio_dump != NULL )
            putc('\n',txio_dump);
         break;
      case '\t':

# ifdef CURSES
         wprintw(output,"\t");
# else 
         printf("\t");
# endif 
         if ( txio_dump_enable && txio_dump != NULL )
            putc('\t',txio_dump);
         break;
      case '\r':

# ifdef CURSES
         wprintw(output,"\r");
# else
         printf("\r");
# endif 
         if ( txio_dump_enable && txio_dump != NULL )
            putc('\r',txio_dump);

      default: /* non-special chars */

         if (!type ){ /*normal char -> echo */
# ifdef CURSES
            waddch(output,*format);
# else 
            putchar(*format);
# endif 
            if ( txio_dump_enable && txio_dump != NULL )
               putc(*format,txio_dump);
            strcpy(myformat,"");
         }
         else { /* format indication char */
            type = 0;
            strncat(myformat,format,1);
            switch( *format ) {
               char *_str;
               void *_ptr;
               char _cint;
            case 'd':
            case 'i':
               switch(*(format-1)){
                  int _int;
                  long int _lint;
                  short int _sint;

               case 'l':
                  _lint = va_arg(pvar, long int );
# ifdef CURSES
                  wprintw(output,myformat,_lint);
# else
                  printf(myformat, _lint);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _lint);
                  break;
               case 'h':
                  _sint = va_arg(pvar, short int );
# ifdef CURSES
                  wprintw(output,myformat,_sint);
# else
                  printf(myformat, _sint);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _sint);
                  break;
               default:
                  _int = va_arg(pvar, int );
# ifdef CURSES
                  wprintw(output,myformat,_int);
# else
                  printf(myformat, _int);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _int);
               } /*of modifier switch*/
               strcpy(myformat,"");
               break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
               switch(*(format-1)){
                  unsigned int _uint;
                  short unsigned int _suint;
                  long unsigned int  _luint;
               case 'h':
                  _suint = va_arg(pvar, short unsigned int );
# ifdef CURSES
                  wprintw(output,myformat,_suint);
# else
                  printf(myformat, _suint);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _suint);
                  break;
               case 'l':
                  _luint = va_arg(pvar, long unsigned int );
# ifdef CURSES
                  wprintw(output,myformat,_luint);
# else
                  printf(myformat, _luint);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _luint);
                  break;
               default : /* unsigned int */
                  _uint = va_arg(pvar, unsigned int );
# ifdef CURSES
                  wprintw(output,myformat,_uint);
# else
                  printf(myformat, _uint);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat, _uint);
               }
               strcpy(myformat,"");
               break;
            case 's':
               _str = va_arg(pvar, char *);
# ifdef CURSES
               wprintw(output,"%s",_str);
# else
               printf("%s", _str);
# endif
               if ( txio_dump_enable && txio_dump != NULL )
                  fprintf(txio_dump,"%s",_str);
               strcpy(myformat,"");
               break;
            case 'f':
            case 'e':
            case 'g':
            case 'E':
            case 'G':
               switch( *(format-1)){
                  float _float;
                  double _dfloat;

               case 'l': /* double float */
                  _dfloat = va_arg(pvar,double );
# ifdef CURSES
                  wprintw(output,myformat,_dfloat);
# else
                  printf(myformat, _dfloat);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat,_dfloat);
                  break;
               case 'L':
                  _dfloat = va_arg(pvar, double );
# ifdef CURSES
                  wprintw(output,myformat,_dfloat);
# else
                  printf(myformat, _dfloat);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat,_dfloat);
                  break;
               default : /* float */
                  _float = va_arg(pvar,float);
# ifdef CURSES
                  wprintw(output,myformat,_float);
# else
                  printf(myformat, _float);
# endif
                  if ( txio_dump_enable && txio_dump != NULL )
                     fprintf(txio_dump,myformat,_float);
               }
               strcpy(myformat,"");
               break;
            case 'p':
               _ptr = va_arg(pvar, void *);
# ifdef CURSES
               wprintw(output,myformat,_ptr);
# else
               printf(myformat, _ptr);
# endif
               if ( txio_dump_enable && txio_dump != NULL )
                  fprintf(txio_dump,myformat,_ptr);
               strcpy(myformat,"");
               break;
            case 'c':
               _cint = va_arg(pvar,char );
# ifdef CURSES
               wprintw(output,myformat,_cint);
# else
               printf(myformat, _cint);
# endif
               if ( txio_dump_enable && txio_dump != NULL )
                  fprintf(txio_dump,myformat,_cint);
               strcpy(myformat,"");
               break;
            default:
               type = 1;
               break;
            }
         }
      }/*switch*/
   }/* print format-args*/
# ifdef CURSES
   if ( txio_refresh_flag )
      wrefresh(output);
# endif
   va_end(pvar);

}/*txio_printstr*/


char *txio_getstr( str )
char* str;
/* --------------------------------
 * Returns: pointer to readed string.
 * Globals: "all"
 * Req.:  screen initd.
 * Comments: a `gets'
 *  
 * --------------------- */ 
{
# ifdef CURSES
   echo();
   flushinp();
   wscanw(output,"%s",str);
   noecho();
# else
   gets(str);
# endif
   if ( txio_dump_enable && txio_dump != NULL )
      fprintf(txio_dump,"%s",str);
   return( str );
}/*txio_getstr*/

int txio_getch()
/* --------------------------------
 * Returns: next input char.
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `getch'
 *  
 * --------------------- */ 
{

#ifndef CURSES
# ifndef TURBOC
   int c,dust;
   c = getc(stdin);
   while ( c != '\n' && (dust = getc(stdin)) != '\n' && dust != EOF )
      ;
   if ( txio_dump_enable && txio_dump != NULL )
      putc(c,txio_dump);
   return(c);
# else
   int c;
   c = getch();
   return ( c );
# endif
#else
   int c;
   noecho();
   c = getchar();
   echo();
   return ( c );
#endif
}/*txio_getch*/

int txio_putchar( ch )
int ch;
/* --------------------------------
 * Returns: ch
 * Globals: "all"
 * Req.: screen initd.
 * Comments: a `putchar'
 *  
 * --------------------- */ 

{
# ifdef CURSES
   waddch(output,ch);
   if ( txio_refresh_flag )
      wrefresh(output);
# else
   putchar(ch);
# endif
   if ( txio_dump_enable && txio_dump != NULL )
      putc(ch,txio_dump);
   return ch;
}/*txio_putchar*/

void txio_waitstroke()
/* --------------------------------
 * Returns: delays until a key is pressed.
 * Globals: "all"
 * Req.: screen initd.
 * --------------------- */ 
{
   txio_getch();
}/*txio_waitstroke*/

void txio_initscr()
/* --------------------------------
 * Globals: "all"
 * Comments: initializes screen.
 *  
 * --------------------- */ 
{

#ifdef CURSES


   if ( initscr()                            == ( WINDOW *) ERR ||
       (output = newwin(MAXROW,MAXCOL,1,1)) == ( WINDOW *) ERR    ){
      fprintf(stderr,"txio_initscr: Not enough memory.\n");
      exit(1);
   }
   nl();
   noecho();
   clear();
   wclear(output);
   cbreak();
   scrollok(stdscr,1);
   scrollok(output,1);
   wrefresh(output);
#else
# ifdef TURBOC
   textcolor(WHITE);
   textbackground(BLACK);
   lowvideo();
   clrscr();
# endif
   /* nothing at all */
#endif

   txio_scrinitd = -1;
   txio_lines_printed = 0;
   txio_refresh_flag =  1;
}/*txio_initscr*/

void txio_endscr()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Terminates screen
 *  
 * --------------------- */ 
{
#ifdef CURSES
   nl();
   echo();
   endwin();
   resetterm();

#else
   /* do nothing at all */
#endif
   txio_scrinitd = FALSE;
   fclose(txio_dump);
}/*txio_endscr*/

void txio_fatal( msg)
char * msg;
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: reports a fatal error msg. and 
 *           terminates screen and execution.
 *           returns `-1' to system.
 * --------------------- */ 
{
   txio_printstr("%s",msg);
   if ( txio_scrinitd   )
      txio_endscr();
   if ( txio_dump_enable && txio_dump != NULL )
      fprintf(txio_dump,"%s",msg);

   exit(-1);
}/*txio_fatal*/

txio_clrstdin()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: clean input buffer.
 *  
 * --------------------- */ 
{
# ifdef CURSES

   flushinp();

#endif

}/*txio_clrstdin*/


void txio_exit(code)
int code;
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: terminates screen an exits with  code.
 *  
 * --------------------- */ 
{
   if ( txio_scrinitd )
      txio_endscr();
   exit(code);
}/*txio_exit*/


void txio_attrInv()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns on inverse video mode.
 *  
 * --------------------- */ 
{
# ifdef CURSES
   wattron(output,A_REVERSE);
# else
#   ifdef TURBOC
   highvideo();

#   endif
# endif

}

void txio_attrBold()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns on Bold writting mode.
 *  
 * --------------------- */ 
{
# ifdef CURSES
   wattron(output,A_BOLD);
# else
#   ifdef TURBOC
   highvideo();
#   endif
# endif
}

void txio_attrnoBold()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns off Bold writting mode
 *  
 * --------------------- */ 
{
# ifdef CURSES
   wattroff(output,A_BOLD);
# else
#   ifdef TURBOC
   lowvideo();
#   endif
# endif
}

void txio_attrnoInv()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Turns off inverse video mode.
 *  
 * --------------------- */ 
{
# ifdef CURSES
   wattroff(output,A_REVERSE);
# else
#   ifdef TURBOC
   lowvideo();
#   endif
# endif

}

int txio_lnscr( fname)
subs_fnameType fname;
/* --------------------------------
 * Returns: non-zero if error.
 * Globals: "all"
 * Req.: screen initd.
 * Comments: Opens fname and dumps stdout to it.
 *  
 * --------------------- */ 
{
   return ( ( txio_dump = fopen( fname,"w")) == NULL );
}/*txio_lnscr*/

void txio_clrstdout()
/* --------------------------------
 * Globals: "all"
 * Req.: screen initd.
 * Comments: clear screen.
 *  
 * --------------------- */ 
{
# ifdef CURSES
   wclear(output);
   wrefresh(output);
# else
#   ifdef TURBOC
   clrscr();
#   endif
# endif
   txio_lines_printed = 0;

}/*txio_clrstdout*/





