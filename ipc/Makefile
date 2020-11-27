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
CPPFLAGS=
CFLAGS= $(CFLAGS) -sb
LDFLAGS=


# everyguy ************************************************

ALL_FILES= ipc.c ipc.h ipctype.h share.h


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[ipc] help done.'

all : clean ipc
	-@echo 'BAM[ipc] all done.'


clean :
	-@echo
	-@echo '****>[ipc] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[ipc] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[ipc] Making xref listing ...'
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
	-@echo 'BAM[ipc] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************


ipc: Makefile ipc.o
	-@echo
	-@echo 'BAM[ipc] make done.'
	-@echo  

ipc.o : ipc.c ipc.h ipctype.h share.h ../share/share.h ../share/defs.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c ipc.c


# all files ************************************************

ipc.c:

ipc.h:

ipctype.h:

share.h:
