#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
#COPTS		=	-O6 
COPTS		=	-g -O6
#COPTS		=	-g 
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/gc

OBJS	 = cgc.o bgc.o markswp.o gc.o gcobject.o gcintern.o \
	   rootset.o gcheaps.o gcbitmap.o gcverify.o gctimer.o weakptr.o \
	   userheap.o

all:	$(OBJS) 

qa:	qa.cc $(OBJS)
	$(CC) $(COPTS) $(CINCLUDE) -o qa qa.cc *.o -liostream

cgc.o:		cgc.cc $(D)/cgc.h $(D)/gc.h $(D)/gcobject.h $(D)/gcintern.h \
		$(D)/rootset.h $(D)/gcconfig.h $(D)/gcheaps.h $(D)/gcbitmap.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h $(ad)/memory/sysmem.h
bgc.o:		bgc.cc $(D)/bgc.h $(D)/gc.h $(D)/gcobject.h $(D)/gcintern.h \
		$(D)/rootset.h $(D)/gcconfig.h $(D)/gcheaps.h $(D)/gcbitmap.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h $(D)/cgc.h \
		$(ad)/generic/generic.h $(ad)/memory/sysmem.h
markswp.o:	markswp.cc $(D)/markswp.h $(D)/gc.h $(D)/gcobject.h \
		$(D)/gcintern.h $(D)/rootset.h $(D)/gcconfig.h \
		$(D)/gcheaps.h $(D)/gcbitmap.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h $(D)/cgc.h \
		$(ad)/generic/generic.h $(ad)/memory/sysmem.h
gc.o:		gc.cc $(D)/gc.h $(D)/gcintern.h \
		$(D)/rootset.h $(D)/gcconfig.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
gcobject.o:	gcobject.cc $(D)/gcobject.h $(D)/gc.h $(D)/gcintern.h \
		$(D)/gcheaps.h $(D)/rootset.h $(D)/gcconfig.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
userheap.o:	userheap.cc $D/userheap.h $(D)/gcobject.h $(D)/gc.h \
		$(D)/gcintern.h $(D)/gcheaps.h $(D)/rootset.h $(D)/gcconfig.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
gcintern.o:	gcintern.cc $(D)/gcintern.h  $(D)/gcconfig.h \
		$(ad)/generic/generic.h $(ad)/memory/mem.h
rootset.o:	rootset.cc $(D)/rootset.h $(D)/gcintern.h $(D)/gcconfig.h \
		$(ad)/generic/generic.h $(ad)/memory/mem.h
gcheaps.o:	gcheaps.cc $(D)/gcheaps.h $(D)/gc.h $(D)/gcobject.h \
		$(D)/gcintern.h $(D)/bgc.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(D)/rootset.h $(D)/gcconfig.h $(D)/gcbitmap.h \
		$(ad)/generic/generic.h $(ad)/memory/sysmem.h \
		$(ad)/sort/insort.h $(ad)/memory/mem.h
gcbitmap.o:	gcbitmap.cc $(D)/gcbitmap.h  $(D)/gcheaps.h \
		$(D)/gcintern.h $(D)/gcconfig.h $(ad)/generic/generic.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h
gcverify.o:	gcverify.cc $(D)/gcverify.h $(D)/gc.h $(D)/gcobject.h \
		$(D)/gcintern.h $(D)/rootset.h $(D)/gcconfig.h \
		$(D)/gcheaps.h $(D)/gcbitmap.h \
		$(D)/gcmacros.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h $(ad)/memory/sysmem.h
gctimer.o:	gctimer.cc $(D)/gctimer.h $(D)/gcconfig.h \
		$(ad)/generic/generic.h $(ad)/memory/mem.h
weakptr.o:	weakptr.cc $(D)/weakptr.h $(D)/gc.h $(D)/gcintern.h \
		$(D)/rootset.h $(D)/gcconfig.h $(ad)/memory/mem.h \
		$(D)/gcmacros.h $(ad)/generic/generic.h

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
