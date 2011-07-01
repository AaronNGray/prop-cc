#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/persist

OBJS	= pstream.o pfactory.o pistream.o postream.o piostream.o pobject.o \
	  ptype.o pmisc.o

all:	$(OBJS)

pobject.o:	pobject.cc $D/pstream.h $D/pobject.h $D/pconfig.h \
		$D/pconvert.h $D/ptype.h $D/ptypeentry.h
ptype.o:	ptype.cc $D/ptype.h $D/pstream.h $D/pobject.h \
		$D/pconfig.h $D/pconvert.h $D/ptypeentry.h \
		$(ad)/contain/vararray.h $D/pi_impl.h $D/po_impl.h \
		$(ad)/contain/variset.h $(ad)/contain/varptrarray.h
pstream.o:	pstream.cc $D/pstream.h $D/pobject.h $D/pconfig.h \
		$D/pconvert.h $D/ptype.h $D/ptypeentry.h 
pistream.o:	pistream.cc $D/pstream.h $D/pobject.h $D/pconfig.h $D/pconvert.h \
		$(ad)/hash/lhash.h $(ad)/memory/mem.h $D/pi_impl.h \
		$D/ptype.h $D/ptypeentry.h  $(ad)/contain/vararray.h  \
		$(ad)/contain/varptrarray.h
postream.o:	postream.cc $D/pstream.h $D/pobject.h $D/pconfig.h $D/pconvert.h \
		$(ad)/hash/lhash2.h \
		$D/ptype.h $D/ptypeentry.h $(ad)/contain/variset.h \
		$D/po_impl.h
piostream.o:	piostream.cc $D/pstream.h $D/pobject.h $D/pconfig.h $D/pconvert.h \
		$(ad)/memory/mem.h \
		$D/ptype.h $D/ptypeentry.h
pfactory.o:	pfactory.cc $D/pfactory.h $D/pobject.h $D/pconfig.h $D/pconvert.h \
		$(ad)/hash/lhash.h \
		$D/ptype.h $D/ptypeentry.h
pmisc.o:	pmisc.cc $D/pobject.h $D/pconfig.h $D/pstream.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)
