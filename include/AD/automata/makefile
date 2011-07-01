#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include		# Path of the ADlib
CC		=	gcc 	   		# Name of the compiler
COPTS		=	-g -O6			# Compiler options
CINCLUDE	=	-I$(ADLIB_PATH)		# Compiler include directive
PROP		=	prop

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/automata

SRC	= treegram.h ebnf.h

all:	$(SRC)

treegram.h:	treegram.ph 
ebnf.h:		ebnf.ph


%.h:	%.ph
	$(PROP) -s $(@:.h=.ph)
