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
LDFLAGS=


# everyguy ************************************************

ALL_FILES= cnst.c cnst.h cnsttype.h func.c func.h names.c names.h ovar.c ovar.h


# Make inherited options **********************************

help :  Makefile.help README
	-@clear
	-@more Makefile.help
	-@echo 'BAM[tables] help done.'

all : clean tables
	-@echo 'BAM[tables] all done.'


clean :
	-@echo
	-@echo '****>[tables] Removing everything ...'
	-@echo
	-@chmod +w *% core  *.o doc/*.x     2>/dev/null
	-@rm *% core  *.o doc/*.x          2>/dev/null
	-@echo 'BAM[tables] clean done.'

xref : $(ALL_FILES) 
	-@echo
	-@echo '****>[tables] Making xref listing ...'
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
	-@echo 'BAM[tables] xref done.'

# Make options ********************************************

showall :
	-@echo $(ALL_FILES)

# The true makefile.****************************************

tables: Makefile names.o ovar.o cnst.o func.o
	-@echo
	-@echo 'BAM[tables] make done.'
	-@echo  

names.o : names.c names.h 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c names.c

ovar.o : ovar.c ovar.h names.h ../share/share.h ../txio/txio.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c ovar.c

cnst.o : cnst.c cnst.h cnsttype.h names.h ../share/share.h ../txio/txio.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c cnst.c

func.o : func.c func.h names.h ../share/share.h ../txio/txio.h
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -c func.c

# all files ************************************************

names.c:
names.h:
ovar.c:
ovar.h:
cnst.c:
cnst.h:
cnsttype.h:
func.c:
func.h:

