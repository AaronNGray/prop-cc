#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix. 
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/graph

OBJS	 = graph.o node.o edge.o \
		graphaux.o

all:	$(OBJS) 

graph.o:	$(D)/graph_base.h $(D)/graph.h $(ad)/pretty/postream.h \
		graphinline.h
edge.o:		$(D)/graph_base.h $(D)/graph.h $(ad)/pretty/postream.h
node.o:		$(D)/graph_base.h $(D)/graph.h $(ad)/pretty/postream.h
graphaux.o:	$(D)/graph_base.h $(D)/graph.h $(D)/node.h $(D)/edge.h 

qa:	qa.cc $(OBJS)
	$(CC) $(COPTS) $(CINCLUDE) -o qa qa.cc *.o -liostream

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
