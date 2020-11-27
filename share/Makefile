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
CPPFLAGS += -DSPARC=1 -DDEBUG=1
CFLAGS += -g
LDFLAGS +=
MKGMMFLAGS += 'tsk fun num'


# everyguy ************************************************

ALL_FILES=share.c share.h defs.h stck.h stckmacr.h stck.c list.c list.h rgetopts.h rgetopts.c


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[share] help done.'

all : clean share
	-@echo 'BAM[share] all done.'


clean :
	-@echo
	-@echo '****>[share] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@ cd mem ; make clean ; cd ..
	-@echo 'BAM[share] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[share] Making xref listing ...'
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
	-@cd mem ; make xref ; cd ..
	-@echo 'BAM[share] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

share : Makefile share.o stck.o list.o rgetopts.o
	-@ cd mem ; make mem ; cd .. 
#CC=$(CC) CFLAGS=$(CFLAGS) 
#             CPPFLAGS=$(CPPFLAGS) LDFLAGS=$(LDFLAGS) 
#BABELROOT=$(BABELROOT) MKGMMFLAGS+=$(MKGMMFLAGS) mem ; cd ..
	-@echo
	-@echo 'BAM[share] make done.'
	-@echo  

share.o :  defs.h share.c share.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c share.c

stck.o : stck.c stck.h share.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c stck.c

list.o : list.c list.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c list.c

rgetopts.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c rgetopts.c

# all files ************************************************

share.h : 
share.c : 
defs.h  : 
stck.h :
stck.c :
stckmacr.h :
list.c :
list.h :
rgetopts.c :
rgetopts.h :
