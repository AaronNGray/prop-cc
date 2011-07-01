#############################################################################
#
#  This Makefile is used to compile the library source code.
#
#############################################################################

#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	g++
#COPTS		=	-O2
#  g++ 2.6.x
COPTS		=	-O6 -fexternal-templates 
#COPTS		=	-g -fexternal-templates 
CINCLUDE	=	-I$(ADLIB_PATH)
AR		= 	ar rv
RANLIB		= 	ranlib
LIBRARY		= 	libprop.a
MFILE		=	Makefile
RM		= 	/bin/rm
PROP		=	../../bin/prop
PROP_OPTS	=	-strict -report -I../../include

MAKE		=	make

#############################################################################
#  A list of all ADLib areas
#############################################################################
AREAS		= algebra automata combinat compress contain \
		  csp database datetime \
		  encrypt gc generic graphics \
		  graph graphtype hash io memory \
		  numeric objc object objstore \
		  persist pipes pretty prettypr \
		  process prop resource rete \
		  rewrite shell stl strings symbolic \
		  trees tries vlsi backend-tools visualize

all:	compile make_library 

make_library:	lib

lib:		
	$(RM) -f $(LIBRARY)
	for dir in $(AREAS); do \
	   if [ -d $$dir ]; then \
	      ar crv $(LIBRARY) $$dir/*.o; \
	   fi; \
	done	
	$(RANLIB) $(LIBRARY)
	@echo "Done"

compile:	
	for dir in $(AREAS); do \
	   if [ -d $$dir ]; then \
	      cd $$dir; \
		make -f $(MFILE) CC="$(CC)" COPTS="$(COPTS)" \
		CINCLUDE="$(CINCLUDE)" PROP="$(PROP)" \
		PROP_OPTS="$(PROP_OPTS)" || exit 1; \
		cd ..; \
	   fi; \
	done

spotless:
	for dir in $(AREAS); do \
	   if [ -d $$dir ]; then $(RM) -f $$dir/*.o; fi; \
	done

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)
