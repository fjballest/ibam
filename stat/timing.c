/* --------------------------------
 *
 *    File: @(#)timing.c   1.0
 *    Date: 4/22/91
 *    Module: Timing 
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Supports portable timming functions.
 * 
 *
 * --------------------- */ 

/* ============== SOME DEPENDENCIES ===========================*/

#include "../share/defs.h"
#include "../txio/txio.h"

/* ============== END OF SOME DEPENDENCIES ====================*/

# ifdef ATT
long time_count1;
long time_count2;
long time_of_stop;
# endif

# ifdef SPARC
#               include <sys/time.h>
struct timeval t_1;
struct timeval t_2;
struct timeval t_stop;
struct timeval t_cont;
struct timezone tz;
struct timeval *tp_1 = &t_1;
struct timeval *tp_2 = &t_2;
struct timeval *tp_stop = &t_stop;
struct timeval *tp_cont = &t_cont;
struct timezone *tzp = &tz;

# endif

# ifdef BSD 
#    ifdef DOS
#       include <sys\timeb.h>
#    else
#       include <sys/timeb.h>
#        endif
struct timeb time_count1;
struct timeb time_count2;
struct timeb time_of_stop;

void time_print()
/* --------------------------------
 * Globals: time_count1, time_count2
 * Comments: prints time.
 *  
 * --------------------- */
{
   long ttime;
   ttime = (time_count2.time    - time_count1.time  ) +
       time_count2.millitm - time_count1.millitm ;
   txio_printstr(" Execution time ( milliseconds): %ld \n",ttime);
}

void time_resume()
/* --------------------------------
 * Globals: time_of_stop, time_count1
 * Req.:  time account stopped
 * Comments: Resumes timing.
 *  
 * --------------------- */
{
   long stime, msc, sc;
   struct timeb tim;

   ftime( &tim );
   stime = (tim.time - time_of_stop.time ) * 1000 +
       tim.millitm - time_of_stop.millitm;
   msc = time_count1.millitm + stime % 1000;
   sc = time_count1.time + stime / 1000 + msc / 1000;
   msc %= 1000;
   time_count1.millitm = msc;
   time_count1.time = sc;

}


# endif




