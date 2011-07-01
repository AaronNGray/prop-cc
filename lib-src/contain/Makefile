#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/contain

OBJS	= basiccol.o bytearry.o charset.o dlist.o intset.o intsets.o \
	  slist.o unionfnd.o variset.o bitset.o fbitset.o n_array.o

all:	$(OBJS)

basiccol.o:	basiccol.cc $(D)/basiccol.h $(ad)/generic/generic.h
bytearry.o:	bytearry.cc $(D)/bytearry.h $(ad)/generic/generic.h
charset.o:	charset.cc  $(D)/charset.h $(ad)/generic/generic.h
dlist.o:	dlist.cc    $(D)/dlist.h  $(D)/dlink.h $(ad)/generic/generic.h
intset.o:	intset.cc   $(D)/intset.h $(ad)/generic/generic.h
intsets.o:	intsets.cc  $(D)/intsets.h $(ad)/generic/generic.h
slist.o:	slist.cc    $(D)/slist.h  $(D)/slink.h $(ad)/generic/generic.h
unionfnd.o:	unionfnd.cc $(D)/unionfnd.h $(ad)/generic/generic.h
variset.o:	variset.cc $(D)/variset.h $(ad)/generic/generic.h
bitset.o:	bitset.cc $(D)/bitset.h $(ad)/memory/mem.h $(ad)/generic/generic.h
fbitset.o:	fbitset.cc $(D)/fbitset.h \
		$(D)/bitset.h $(ad)/memory/mem.h $(ad)/generic/generic.h
n_array.o:	n_array.cc $(D)/n_array.h $(ad)/generic/generic.h

%.o:	%.cc 
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)
