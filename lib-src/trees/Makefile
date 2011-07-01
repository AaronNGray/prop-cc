#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-g -O
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/trees

OBJS	= avl.o fibheap.o leftist.o pagoda.o rlxheap.o splay.o trees.o vbpq.o

all:	$(OBJS)

avl.o:		avl.cc  $D/avl.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
fibheap.o:	fibheap.cc $D/fibheap.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
leftist.o:	leftist.cc $D/leftist.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
pagoda.o:	pagoda.cc $D/pagoda.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
rlxheap.o:	rlxheap.cc $D/rlxheap.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
splay.o:	splay.cc $D/splay.h $D/trees.h \
		$(ad)/generic/ordering.h $(ad)/generic/generic.h
trees.o:	trees.cc $D/trees.h $(ad)/generic/ordering.h $(ad)/generic/generic.h
vbpq.o:		vbpq.cc $D/vbpq.h $(ad)/generic/ordering.h $(ad)/generic/generic.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)
