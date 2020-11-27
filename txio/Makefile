#
#
#   L.B.A.M. Rev. @(#)Makefile	1.1
#   Makefile.unix
#
#       (c) Laboratorio de Lenguajes Declarativos (LLD) 1989,1990,1991.
#   

# Be sure of cc current flags. ****************************

# Babel root directory ************************************
#BABELROOT= /usr2/babel/lbam-1.0
BABELROOT= /home.esther/babel/Emulator/Lbam-1.0/src
# Shared files ********************************************
SHARED= $(BABELROOT)/src/share/share.h $(BABELROOT)/src/share/defs.h
# defaults ************************************************
CPPFLAGS=
LDFLAGS=


# everyguy ************************************************

ALL_FILES=txio.c txio.h 

# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[txio] help done.'

all : clean txio
	-@echo 'BAM[txio] all done.'


clean :
	-@echo
	-@echo '****>[txio] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x    2>/dev/null
	-@rm *% core  doc/*.x  *.o        2>/dev/null
	-@echo 'BAM[txio] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[txio] Making xref listing ...'
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
	-@echo 'BAM[txio] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

txio :  Makefile txio.o
	-@echo
	-@echo 'BAM[txio] make done.'
	-@echo  

txio.o : txio.c txio.h $(SHARED)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c txio.c

# all files ************************************************

txio.h : 
txio.c : 
$(SHARED) :
