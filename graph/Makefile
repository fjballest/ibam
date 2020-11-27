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
CPPFLAGS += -DDEBUG=1 -DSPARC=1
LDFLAGS += -sb -g


# everyguy ************************************************

ALL_FILES= gc.c gc.h gcmacr.h grph.c grph.h grphmacr.h \
           grphtype.h vinb.c vinb.h


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[graph] help done.'

all : clean graph
	-@echo 'BAM[graph] all done.'


clean :
	-@echo
	-@echo '****>[graph] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[graph] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[graph] Making xref listing ...'
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
	-@echo 'BAM[graph] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

graph: Makefile gc.o vinb.o grph.o
	-@echo
	-@echo 'BAM[graph] make done.'
	-@echo  

gc.o : gc.c gc.h gcmacr.h ../share/share.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c gc.c

vinb.o : vinb.c vinb.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c vinb.c

grph.o : grph.c grph.h grphmacr.h grphtype.h ../share/share.h \
         ../share/stck.h ../txio/txio.h ../share/mem/alloc.h      \
         gc.h vinb.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c grph.c


# all files ************************************************

gc.c :
gc.h :
gcmacr.h :
grph.c :
grph.h :
grphmacr.h :
grphtype.h :
vinb.c :
vinb.h :

