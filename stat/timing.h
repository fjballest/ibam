
/* --------------------------------
 *
 *    File: @(#)timing.h   1.0
 *    Date: 4/22/91
 *    Module: Timing 
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports portable timming functions.
 * 
 *
 * --------------------- */ 





#ifndef __TIME_H
#  define __TIME_H

#  ifndef NULL
#    define NULL 0
#  endif

#  include "share/defs.h"

#  ifdef ATT

/*******************************************************************
 *                   ATT timing
 */

#       include <sys/clock.h>
                extern long time_count1;
                extern long time_count2;
                extern long time_of_stop;

#       define TIME_GETT1  time_count1=clock()
/* --------------------------------
 * Globals: time_count1
 * Comments: turns on timing
 *  
 * --------------------- */ 

#       define TIME_GETT2  time_count2=clock()
/* --------------------------------
 * Globals: time_count2
 * Comments: fix up-to-time.
 *  
 * --------------------- */ 

#       define TIME_PRINT  \
   txio_printstr(" Execution time ( milliseconds):%ld \n",(time_count2-time_count1)/1000)
/* --------------------------------
 * Globals: time_count1, time_count2
 * Comments: prints time.
 *  
 * --------------------- */


#       define TIME_STOP  time_of_stop=clock()
/* --------------------------------
 * Globals: time_of_stop
 * Comments: stop time accounting
 *  
 * --------------------- */ 

#       define TIME_CONT  time_count1=time_count1-time_of_stop+clock()
/* --------------------------------
 * Globals: time_of_stop, time_count1
 * Req.:  time account stopped
 * Comments: Resumes timing.
 *  
 * --------------------- */

#  else
#          ifdef SUN
/*******************************************************************
 *                   SUN timing
 */

#               include <sys/time.h>
                extern struct timeval *tp_1;
                extern struct timeval *tp_2;
                extern struct timeval *tp_stop;
                extern struct timeval *tp_cont;
                extern struct timezone *tzp;

#               define TIME_GETT1  gettimeofday(tp_1,tzp)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_GETT2  gettimeofday(tp_2,tzp)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_PRINT  \
                        txio_printstr(" Execution time ( milliseconds ): %ld \n",(tp_2->tv_sec-tp_1->tv_sec)*1000+(tp_2->tv_usec-tp_1->tv_usec)/1000)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_STOP  gettimeofday(tp_stop,tzp)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_CONT  gettimeofday(tp_cont,tzp);\
                        tp_1->tv_sec=tp_cont->tv_sec+tp_1->tv_sec-tp_stop->tv_sec;\
                        tp_1->tv_usec=tp_cont->tv_usec+tp_1->tv_usec-tp_stop->tv_usec;\
                        tp_1->tv_sec+=((int)(tp_1->tv_usec/1000000));\
                        tp_1->tv_usec%=1000000

/* --------------------------------
 * Comments: As above !
 * --------------------- */


#  else
#      ifdef BSD
/*******************************************************************
 *                   pure BSD timing
 */

#       ifdef DOS
#          include <sys\timeb.h>
#       else
#          include <sys/timeb.h>
#       endif

                extern struct timeb time_count1;
                extern struct timeb time_count2;
                extern struct timeb time_of_stop;

#               define TIME_GETT1 ftime(&time_count1)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_GETT2 ftime(&time_count2)
/* --------------------------------
 * Comments: As above !
 * --------------------- */


#               define TIME_PRINT time_print()
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#               define TIME_STOP ftime(&time_of_stop)
/* --------------------------------
 * Comments: As above !
 * --------------------- */
#       define TIME_CONT time_resume()
/* --------------------------------
 * Comments: As above !
 * --------------------- */

                void time_print();
                void time_resume();
/* Both are  "local" functions. */

#    endif
#       endif
#  endif


#endif





