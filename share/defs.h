/* --------------------------------
 *
 *    File: @(#)defs.h   1.1
 *    Date: 4/22/91
 *    Module:    Defines ( def )
 *    Programmer: Franc. J.B. Camara
 *
 *    Comments: Defaults for conditional compilation
 * 
 *
 * --------------------- */ 

#ifndef __DEFS_H
# define __DEFS_H 1

# ifdef DOS
/* Check if PC system --> Default BSD Lib( opt. ATT Lib) */
#       undef DOS
#       define DOS 1
#       ifndef ATT
#               undef BSD
#               define BSD 1
#       endif
# else
/*  Define computer type. ( Default UNIX std. sys V ). */
#       undef UNIX
#       define UNIX 1
#       if ! ( BSD || SUN || SPARC )
#               undef SPARC
#               define SPARC 1
#       else 
#         if ( ATT || V )
#           undef ATT
#           define ATT 1
#         endif
#       endif
# endif


# endif


