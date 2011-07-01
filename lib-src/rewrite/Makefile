#
#  A sample Makefile
#

ADLIB_PATH	= ../../include
CC		= gcc
CINCLUDE	= -I$(ADLIB_PATH)
COPTS		= -g -O6
#COPTS		= -g -O6 -pg
PROP		= ../../bin/prop
PROP_OPTS	= -s 

D		= $(ADLIB_PATH)/AD/rewrite
ad		= $(ADLIB_PATH)/AD

OBJS		= twig.o b_item.o b_items.o b_rules.o burs_gen.o \
		  twig_gen.o burs.o cache.o
SRC		= b_rules.cc

all:	$(SRC) $(OBJS)

src:	$(SRC)

b_rules.cc:	b_rules.pcc $(ad)/automata/treegram.ph

twig.o:		twig.cc $D/twig.h $(ad)/automata/topdown.h \
		$(ad)/automata/ac.h $(ad)/automata/sparsdfa.h \
		$(ad)/automata/compdfa.h $(ad)/automata/dfatable.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/contain/bitset.h $(ad)/generic/generic.h
twig_gen.o:	twig_gen.cc $D/twig_gen.h $(ad)/automata/topdown.h \
		$(ad)/automata/ac.h $(ad)/automata/sparsdfa.h \
		$(ad)/automata/compdfa.h $(ad)/automata/dfatable.h \
		$(ad)/memory/mem.h $(ad)/memory/boundtag.h \
		$(ad)/contain/bitset.h $(ad)/generic/generic.h
b_item.o:	b_item.cc $D/b_item.h $(ad)/automata/treetab.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
b_items.o:	b_items.cc $D/b_items.h $D/b_item.h $(ad)/automata/treetab.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
b_rules.o:	b_rules.cc $D/b_rules.h $D/b_items.h $D/b_item.h \
		$(ad)/automata/treetab.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h
burs.o:		burs.cc $D/burs.h \
		$(ad)/automata/treetab.h $(ad)/automata/treeauto.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h 
burs_gen.o:	burs_gen.cc $D/burs_gen.h \
		$D/b_items.h $D/b_item.h $D/b_rules.h \
		$(ad)/automata/treetab.h $(ad)/automata/treeauto.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h $(ad)/hash/dchash.h \
		$(ad)/automata/dfatable.h $(ad)/automata/compdfa.h \
		$(ad)/automata/sparsdfa.h
burs_gn2.o:	burs_gn2.cc $D/burs_gn2.h $D/burs_gen.h \
		$D/b_items.h $D/b_item.h $D/b_rules.h \
		$(ad)/automata/treetab.h $(ad)/automata/treeauto.h \
		$(ad)/automata/treegram.h $(ad)/memory/mem.h \
		$(ad)/generic/generic.h $(ad)/hash/dchash.h \
		$(ad)/automata/dfatable.h $(ad)/automata/compdfa.h \
		$(ad)/automata/sparsdfa.h


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
