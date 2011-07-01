#
#  A sample Makefile
#

ADLIB_PATH	= ../../include
CC		= g++
CINCLUDE	= -I$(ADLIB_PATH)
COPTS		= -O6
PROP		= prop
PROP_OPTS	= -s -v

D		= $(ADLIB_PATH)/AD/absinterp
ad		= $(ADLIB_PATH)/AD

OBJS		= absdomain.o 

all:	$(OBJS)

src:	$(SRC)

absdomain.o:	absdomain.cc $D/absdomain.h $(ad)/generic/generic.h

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
