#
#  A sample Makefile
#

ADLIB_PATH	= ../../include
CC		= g++
CINCLUDE	= -I$(ADLIB_PATH)
COPTS		= -O6
PROP		= prop
PROP_OPTS	= -s -v

D		= $(ADLIB_PATH)/AD/symbolic
ad		= $(ADLIB_PATH)/AD

OBJS		= bdd.o expr.o string.o atom.o term.o fouriermotzkin.o

all:	$(OBJS)

src:	$(SRC)

bdd.o:		bdd.cc $D/bdd.h $(ad)/generic/generic.h
expr.o:		expr.cc $D/expr.h $(ad)/generic/generic.h
string.o:	string.cc $D/expr.h $D/string.h $(ad)/generic/generic.h \
		$(ad)/strings/string.h
atom.o:		atom.cc $D/atom.h $D/expr.h $D/string.h $(ad)/generic/generic.h \
		$(ad)/strings/string.h
term.o:		term.cc $D/term.h $D/expr.h $(ad)/generic/generic.h 
fouriermotzkin.o: fouriermotzkin.cc $D/fouriermotzkin.h \
		$(ad)/generic/generic.h $(ad)/memory/mem.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.c++
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.c++)

%.o:	%.c
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.c)

%.cc:	%.pcc
	$(PROP) $(PROP_OPTS) $(CINCLUDE) $(@:.cc=.pcc)

%.h:	%.ph
	$(PROP) $(PROP_OPTS) $(CINCLUDE) $(@:.h=.ph)
