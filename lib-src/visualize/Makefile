#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-O6 -fexternal-templates -g
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/visualize

OBJS	 = vcg.o

all:	$(OBJS) 

qa:	qa.cc $(OBJS)
	$(CC) $(COPTS) $(CINCLUDE) -o qa qa.cc *.o -liostream

vcg.o:		vcg.cc $(D)/vcg.h $(ad)/generic/generic.h \
		$(ad)/hash/lhash.h \
		$(ad)/visualize/vcg.h \
		$(ad)/hash/lhash.h \
		$(ad)/memory/strpool.h \
		$(ad)/contain/varstack.h \
		$(ad)/strings/charesc.h \
		$(ad)/pretty/postream.h 


%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)

%.o:	%.s
	$(AS) $(@:.o=.s) -o $@
