#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-g -O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/rete

OBJS	= rete.o fact.o retenet.o gen_rete.o alphamem.o betamem.o token.o

all:	$(OBJS)

rete.o:		rete.cc $D/rete.h $D/fact.h $D/retenet.h \
		$(ad)/contain/varqueue.h $(ad)/generic/ordering.h \
		$(ad)/generic/generic.h $(ad)/hash/chash.h \
		$(ad)/memory/mem.h $(ad)/memory/arena.h
fact.o:		fact.cc $D/fact.h
retenet.o:	retenet.cc $D/fact.h $D/retenet.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/generic/generic.h
gen_rete.o:	gen_rete.cc $D/fact.h $D/gen_rete.h $D/token.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/generic/generic.h $D/alphamem.h $D/betamem.h
alphamem.o:	alphamem.cc $D/alphamem.h $D/fact.h $D/token.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/memory/arena.h
betamem.o:	betamem.cc $D/betamem.h $D/fact.h $D/token.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/memory/arena.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)
