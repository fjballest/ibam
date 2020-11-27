#################################################################
#                                                                   
#         ksh profile:                                                
#         initial setup file for both interactive and noninteractive
#         Korn-Shells
#         (c)-1991 Francisco J. Ballesteros ( Nemo )
#
#################################################################

#
# Environment variables ....
#
export OPENWINHOME=/usr/openwin \
	MANPATH=/usr/openwin/man:/usr/man:/usr/lang/man:/usr.sol/man:/usr.sol/local/manl \
	HELPPATH=/usr/lang/SC1.0/SourceBrowser.info \
	PATH=/usr/lang:/usr/local/bin:/usr/ucb:/usr/bin:/usr/etc:/etc:/usr/5bin.:~:~/bin  \
	LC_CTYPE='iso_8859_1' \
	LD_LIBRARY_PATH='/usr/openwin/lib' \
	TMP=~/tmp \
	PS1=`hostname`'\$'`whoami`'%'
	PRINTER=cain \
	HISTFILE=$HOME/sh_history \
	EDITOR=$(whence vi) \
	BABROOT=/home/esther/Babel/Emulator/Lbam-1.0 \
	CJOBS=$HOME/babel/c_jobs \
	PAGER=$(whence more) \
	PWD=$HOME \
	OLDPWD=$HOME \
	FCEDIT=$(whence vi) \
	PROFDIR=./prof \
	BOOKINFO=/usr/AnswerBook/SysSoft1.1/bookinfo.new \
	ENV=$HOME/.envfile \
	SUN_SOURCE_BROWSER_EX_FILE=/usr/lang/sbrowser_ow


export TERM TERMCAP 

#
# Set up ( on-site ) specific devices ....
#

# Moises....
if [[ `hostname` = "moises" ]]
then # The streamer
	export TAPE=/dev/rst1 \
	       DISPLAY=esther:0
	
fi

# Esther & Judith ....
if [[ `hostname` = "esther" || `hostname` = "judith" ]]
then
	export TAPE="/dev/fd0"
fi

# Antares ....
if [[ `hostname` = "antares" ]]
then
	export TAPE="/dev/fd1b"
fi


# 
# Do not destroy files & vi editor....
#
set -o noclobber -o vi

#
# Permissions mask....
#
umask 0027


