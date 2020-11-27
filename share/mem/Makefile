#
#
#   L.B.A.M. Rev. @(#)Makefile	1.0
#   Makefile.unix
#
#       (c) Laboratorio de Lenguajes Declarativos (LLD) 1989,1990,1991.
#   


# Babel root directory ************************************
#BABELROOT= /usr2/babel/lbam-1.0
BABELROOT= /home/esther/babel/Emulator/Lbam-1.0/src
# defaults ************************************************
CFLAGS += -g
CPPFLAGS += -DDEBUG=1 -DSPARC=1
LDFLAGS +=
MKGMMFLAGS += tsk fun num

ALL_FILES= blmtypes.h blm.c blm.h vadd.c vadd.h gmm.c gmm.h gmmtype.h mkgmm.c \
           pgpool.c pgpool.h blmtypes.h


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[mem] help done.'

all : clean mem
	-@echo 'BAM[mem] all done.'


clean :
	-@echo
	-@echo '****>[mem] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[mem] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[mem] Making xref listing ...'
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
	-@echo 'BAM[mem] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

mem: Makefile gmm.o blm.o vadd.o pgpool.o
	-@echo
	-@echo 'BAM[mem] make done.'
	-@echo  

gmm.o : gmm.c gmm.h gmmtype.h ../share.h ../list.h buildgmm
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c gmm.c

buildgmm : mkgmm
	mkgmm $(MKGMMFLAGS)  

mkgmm : mkgmm.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o mkgmm mkgmm.c

blm.o : blm.c blm.h blmtypes.h pgpool.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c blm.c

vadd.o : vadd.c vadd.h ../share.h ../list.h ../stck.h pgpool.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c vadd.c

pgpool.o : pgpool.c pgpool.h ../share.h ../list.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c pgpool.c

# all files ************************************************

blm.c :
blm.h :
blmtypes.h :
vadd.c :
vadd.h :
gmm.c :
gmm.h :
gmmtype.h :
mkgmm.c :
pgpool.c :
pgpool.h :


