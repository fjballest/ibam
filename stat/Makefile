#
#
#   L.B.A.M. Rev. @(#)Makefile	1.0
#   Makefile.unix
#
#       (c) Laboratorio de Lenguajes Declarativos (LLD) 1989,1990,1991.
#   


# Babel root directory ************************************
#BABELROOT= /usr2/babel/lbam-1.0
BABELROOT= /home.esther/babel/Emulator/Lbam-1.0/src
# defaults ************************************************
CPPFLAGS +=
LDFLAGS +=
CFLAGS += -g -sb

# everyguy ************************************************

ALL_FILES= stat.c stat.h timing.c timing.h lbamstd.c


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[stat] help done.'

all : clean stat
	-@echo 'BAM[stat] all done.'


clean :
	-@echo
	-@echo '****>[stat] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[stat] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[stat] Making xref listing ...'
	-@echo
	-@mkdir doc 2>/dev/null
	-@rm doc/* 2>/dev/null
	-@cxref -t  $(ALL_FILES) 2>/dev/null | grep -v 'include' >doc/lbam.x
	-@chmod +x list_number 2>/dev/null
	-@echo
	-@echo '****> Numbering files ...'
	-@echo
	-@$(BABELROOT)/bin/list_number
	-@echo
	-@echo 'BAM[stat] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

stat: Makefile stat.o timing.o lbamstd
	-@echo
	-@echo 'BAM[stat] make done.'
	-@echo

lbamstd : lbamstd.o ../ipc/ipc.o ../share/err.o ../share/rgetopts.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lbamstd \
           lbamstd.o ../ipc/ipc.o ../share/err.o ../share/rgetopts.o


lbamstd.o : lbamstd.c ../ipc/ipc.h ../share/share.h ../share/err.h \
          ../share/rgetopts.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c lbamstd.c

stat.o : stat.c stat.h ../share/share.h ../txio/txio.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c stat.c

timing.o : timing.c timing.h ../share/defs.h ../txio/txio.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c timing.c


# all files ************************************************

stat.c:
stat.h:
timing.c:
timing.h:
lbamstd.c:

