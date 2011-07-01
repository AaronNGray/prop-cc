#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	g++
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/memory

OBJS1	= arena.o boundtag.o freelist.o mempool.o sysmem.o cleanmem.o
OBJS2	= ptr.o strpool.o ref.o variant.o mem.o variant.o buddysys.o blacklistmem.o

all: $(OBJS1) $(OBJS2)

buddysys.o:	buddysys.cc $D/buddy.h $(ad)/generic/generic.h $(ad)/generic/tables.h $D/mem.h
sysmem.o:	sysmem.cc $D/mem.h $D/sysmem.h
arena.o:	arena.cc $D/arena.h $(ad)/generic/generic.h $D/mem.h
mem.o:		mem.cc $D/mem.h $D/sysmem.h
cleanmem.o:	cleanmem.cc $D/mem.h $D/cleanmem.h
blacklistmem.o:	blacklistmem.cc $D/mem.h $D/blacklistmem.h $(ad)/gc/gcheaps.h
boundtag.o:	boundtag.cc $D/boundtag.h $(ad)/generic/generic.h $D/mem.h
freelist.o:	freelist.cc $D/freelist.h $(ad)/generic/generic.h
mempool.o:	mempool.cc $D/mempool.h $(ad)/generic/generic.h $D/mem.h
ptr.o:		ptr.cc $D/ptr.h $D/ref.h $(ad)/generic/generic.h
ref.o:		ref.cc $D/ref.h $(ad)/generic/generic.h
strpool.o:	strpool.cc $D/strpool.h $(ad)/generic/generic.h $D/mem.h
variant.o:	variant.cc $D/variant.h $D/ref.h $(ad)/generic/generic.h
	
%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)
