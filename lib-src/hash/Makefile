#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-g -O
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/hash

OBJS	= bhash.o chash.o dchash.o dhash.o hashfn.o lhash.o ohash.o 

all:	$(OBJS)

hashfn.o:	hashfn.cc $(D)/hashfn.h
bhash.o:	bhash.cc  $(D)/bhash.h  $(ad)/generic/ordering.h
chash.o:	chash.cc  $(D)/chash.h  $(ad)/generic/ordering.h
dchash.o:	dchash.cc $(D)/dchash.h $(ad)/generic/ordering.h
dhash.o:	dhash.cc  $(D)/dhash.h  $(ad)/generic/ordering.h
lhash.o:	lhash.cc  $(D)/lhash.h  $(ad)/generic/ordering.h
ohash.o:	ohash.cc  $(D)/ohash.h  $(ad)/generic/ordering.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)

