#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/pretty

OBJS	 = pristream.o prostream.o priostream.o

all:    prostream.o
# 	$(OBJS)

qa:	qa.cc $(OBJS)
	$(CC) $(COPTS) $(CINCLUDE) -o qa qa.cc *.o -liostream

pristream.o:	pristream.cc $(D)/pistream.h
prostream.o:	prostream.cc $(D)/postream.h
priostream.o:	priostream.cc $(D)/piostream.h $(D)/pistream.h $(D)/postream.h

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
