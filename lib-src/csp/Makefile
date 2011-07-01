#
#  A sample Makefile
#

ADLIB_PATH	= ../../include
CC		= gcc
CINCLUDE	= -I$(ADLIB_PATH)
COPTS		= -O6
#COPTS		= -g -O6 -pg
PROP		= prop
PROP_OPTS	= -s 

D		= $(ADLIB_PATH)/AD/csp
ad		= $(ADLIB_PATH)/AD

OBJS		= trail.o logicalterm.o
SRC		= trail.cc logicalterm.cc

all:	$(SRC) $(OBJS)

src:	$(SRC)

trail.o:	trail.cc $D/logicalterm.h $D/trail.h $(ad)/memory/mem.h \
		$(ad)/memory/mempool.h $(ad)/generic/generic.h

logicalterm.o:	logicalterm.cc $D/logicalterm.h $D/trail.h $(ad)/memory/mem.h \
		$(ad)/memory/mempool.h $(ad)/generic/generic.h

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
