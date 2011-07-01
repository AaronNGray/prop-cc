#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	g++
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/strings

OBJS	= atom.o bm.o charesc.o fansu.o kmp.o kr.o 
OBJS2	= quark.o regexp.o shiftadd.o string.o strmatch.o twoway.o

all:	$(OBJS) $(OBJS2)

approx.o:	approx.cc $D/approx.h $D/shiftadd.h $(ad)/generic/generic.h
atom.o:		atom.cc $D/atom.h $(ad)/generic/generic.h $(ad)/hash/dchash.h
bm.o:		bm.cc $D/bm.h $D/strmatch.h $(ad)/generic/generic.h
charesc.o:	charesc.cc $D/charesc.h 
fansu.o:	fansu.cc $D/fansu.h $(ad)/generic/generic.h
kmp.o:		kmp.cc $D/kmp.h $D/strmatch.h $(ad)/generic/generic.h
kr.o:		kr.cc $D/kr.h $D/strmatch.h $(ad)/generic/generic.h
quark.o:	quark.cc $D/quark.h $(ad)/hash/dchash.h \
		$(ad)/memory/strpool.h $(ad)/memory/mem.h $(ad)/generic/generic.h 
regexp.o:	regexp.cc $D/regexp.h $(ad)/contain/charset.h \
		$(ad)/generic/generic.h
shiftadd.o:	shiftadd.cc $D/shiftadd.h $(ad)/generic/generic.h 
string.o:	string.cc $D/string.h $(ad)/generic/generic.h
strmatch.o:	strmatch.cc $D/strmatch.h $(ad)/generic/generic.h
twoway.o:	twoway.cc $D/twoway.h $(ad)/generic/generic.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)
