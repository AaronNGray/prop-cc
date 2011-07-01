#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-g -O
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/tries

OBJS	= briandai.o comptrie.o hashtrie.o patricia.o trie.o

all:	$(OBJS)

briandai.o:	briandai.cc $D/briandai.h $(ad)/generic/generic.h 
comptrie.o:	comptrie.cc $D/comptrie.h $(ad)/generic/generic.h
hashtrie.o:	hashtrie.cc $D/hashtrie.h $(ad)/generic/generic.h
patricia.o:	patricia.cc $D/patricia.h $(ad)/generic/generic.h
trie.o:		trie.cc $D/trie.h $(ad)/generic/generic.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)
