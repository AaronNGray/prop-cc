OBJS	= array.o colors.o \
	  tiny.o logic.o list.o list2.o tree.o \
	  poly.o poly2.o 
CSRC	= array.cc colors.cc \
	  tiny.cc logic.cc list.cc list2.cc tree.cc \
          poly.cc poly2.cc poly3.cc 

CC	= gcc
CINCLUDE= -I../../include
COPTS	= -O2
RM	= rm -f

PROP	= ../../bin/prop
PROPOPTS= 

all:	src $(OBJS)
src:	$(CSRC)
spotless:
	$(RM) *.cc *.h *.o 

array.o:	array.cc
calculus.o:	calculus.cc calculus.h
colors.o:	colors.cc
family.o:	family.cc
logic.o:	logic.cc logic.h
record.o:	record.cc
tiny.o:		tiny.cc tiny.h
list.o:		list.cc
list2.o:	list2.cc
tree.o:		tree.cc
lex.o:		lex.cc
lex2.o:		lex2.cc
poly.o:		poly.cc
poly2.o:	poly2.cc
poly3.o:	poly3.cc

array.cc:	array.pcc
calculus.cc:	calculus.pcc calculus.ph
colors.cc:	colors.pcc
family.cc:	family.pcc
logic.cc:	logic.pcc logic.ph
record.cc:	record.pcc
tiny.cc:	tiny.pcc tiny.ph
list.cc:	list.pcc
list2.cc:	list2.pcc
tree.cc:	tree.pcc
lex.cc:		lex.pcc
lex2.cc:	lex2.pcc
poly.cc:	poly.pcc
poly2.cc:	poly2.pcc
poly3.cc:	poly3.pcc

%.h:		%.ph $(PROP)
	$(PROP) $(PROPOPTS) $(@:.h=.ph)
%.cc:		%.pcc  $(PROP)
	$(PROP) $(PROPOPTS) $(@:.cc=.pcc)
%.o:		%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)
