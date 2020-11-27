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
GENFLAGS += tsk fun num


# everyguy ************************************************

ALL_FILES= gc.c gc.h   mkgc.c



# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[gc] help done.'

all : clean gc
	-@echo 'BAM[gc] all done.'


clean :
	-@echo
	-@echo '****>[gc] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[gc] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[gc] Making xref listing ...'
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
	-@echo 'BAM[gc] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

gc : Makefile gc.o
	-@echo
	-@echo 'BAM[gc] make done.'
	-@echo  

gc.o : buildgc gc.h gc.c ../../share/share.h ../../share/list.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c gc.c

buildgc : mkgc
	mkgc $(GENFLAGS)

mkgc : mkgc.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o mkgc mkgc.c


# all files ************************************************

gc.c :
gc.h :   
mkgc.c :


