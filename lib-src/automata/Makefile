#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	g++ 
COPTS		=	-O6 
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/automata

PROP		=	../../bin/prop
PROP_OPTS	=	-s $(CINCLUDE)

OBJS	= ac.o acgen.o bottomup.o lr0.o compdfa.o densedfa.o 
OBJS2	= gentable.o grammar.o lr1.o lalr1gen.o 
OBJS3	= lexer.o lexergen.o ll1.o ll1gen.o ll1parse.o lrgen.o
OBJS4	= llk.o llkgen.o lrk.o lrparser.o lookahd.o
OBJS5	= scanner.o sparsdfa.o topdown.o topdowng.o 
OBJS6	= treeauto.o treegen.o treegram.o regexmat.o
OBJS7	= nullable.o firstset.o follow.o first_k.o follow_k.o operprec.o
OBJS8	= nfa.o nfa_node.o nfa32.o lr1gen.o lrkgen.o gla.o lexerbuf.o
OBJS9	= iolexerbuf.o iolexerstack.o item.o firstset2.o fastac.o

all:	$(OBJS) $(OBJS2) $(OBJS3) $(OBJS4) \
	$(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8) $(OBJS9)

#############################################################################
#  Prop stuff
#############################################################################
SRC	= treegram.cc topdowng.cc treegen.cc 

src:	$(SRC)

treegram.cc:	treegram.pcc $D/treegram.ph
topdowng.cc:	topdowng.pcc $D/treegram.ph
treegen.cc:	treegen.pcc  $D/treegram.ph
 
ac.o:		ac.cc $D/ac.h $D/compdfa.h $(ad)/generic/generic.h \
		$D/sparsdfa.h $D/dfatable.h
acgen.o:	acgen.cc $D/acgen.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/tries/briandai.h $(ad)/contain/varstack.h \
		$(ad)/contain/queue.h $(ad)/generic/generic.h \
		$D/dfatable.h
factac.o:	factac.cc $D/acgen.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/tries/briandai.h $(ad)/contain/varstack.h \
		$(ad)/contain/queue.h $(ad)/generic/generic.h \
		$D/dfatable.h
nullable.o:	nullable.cc $D/nullable.h $(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
firstset.o:	firstset.cc $D/firstset.h $D/nullable.h $(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
firstset2.o:	firstset2.cc $D/firstset2.h \
		$D/firstset.h $D/nullable.h $(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
follow.o:	follow.cc $D/follow.h $D/firstset.h $D/nullable.h \
		$(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
first_k.o:	first_k.cc $D/first_k.h $D/follow.h $D/firstset.h $D/nullable.h \
		$(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
follow_k.o:	follow_k.cc $D/follow_k.h $D/first_k.h $D/follow.h \
		$D/firstset.h $D/nullable.h $(ad)/contain/bitset.h \
		$D/grammar.h $(ad)/memory/mempool.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
bottomup.o:	bottomup.cc $D/bottomup.h $D/treeauto.h \
		$D/treepat.h $D/termpat.h $(ad)/generic/generic.h \
		$(ad)/contain/dchmap.h $(ad)/memory/mempool.h \
		$(ad)/contain/vararray.h $(ad)/contain/stack.h \
		$(ad)/contain/varqueue.h $D/treetab.h \
		$D/dfatable.h $(ad)/memory/mem.h \
		$D/compdfa.h $D/sparsdfa.h
item.o:		item.cc $D/item.h $D/grammar.h $D/gentable.h \
		$(ad)/generic/generic.h 
lr0.o:		lr0.cc $D/lr0.h $D/grammar.h $D/gentable.h \
		$(ad)/hash/dchash.h $(ad)/contain/hashmap.h \
		$(ad)/contain/dchmap.h $(ad)/generic/generic.h \
		$(ad)/generic/ordering.h $D/item.h $(ad)/memory/mempool.h \
		$D/dfatable.h $(ad)/contain/bitset.h $(ad)/memory/mem.h
gla.o:		gla.cc $D/gla.h $D/grammar.h $D/gentable.h \
		$(ad)/hash/dchash.h $(ad)/contain/hashmap.h \
		$(ad)/contain/dchmap.h $(ad)/generic/generic.h \
		$(ad)/generic/ordering.h $(ad)/memory/mempool.h \
		$D/dfatable.h $(ad)/contain/bitset.h $(ad)/memory/mem.h
compdfa.o:	compdfa.cc $D/compdfa.h $(ad)/generic/generic.h \
		$D/dfatable.h
densedfa.o:	densedfa.cc $D/densedfa.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/contain/varstack.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
dfa.o:		dfa.cc $D/dfa.h $(ad)/contain/map.h $(ad)/memory/mempool.h \
		$(ad)/generic/generic.h $(ad)/memory/mem.h
gentable.o:	gentable.cc $D/gentable.h $(ad)/generic/generic.h
graminfo.o:	graminfo.cc $D/graminfo.h $D/grammar.h \
		$(ad)/contain/intsets.h $(ad)/generic/generic.h \
		$(ad)/sort/shellsrt.h $(ad)/generic/ordering.h \
		$(ad)/sort/sorting.h $D/dfatable.h
grammar.o:	grammar.cc $D/grammar.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/strings/charesc.h
#labtree.o:	labtree.cc $D/labtree.h $(ad)/contain/charset.h \
#		$(ad)/generic/generic.h $D/dfatable.h
lr1.o:		lr1.cc $D/lr1.h $D/grammar.h $(ad)/generic/generic.h \
		$D/dfatable.h
lrparser.o:	lrparser.cc $D/lrparser.h $D/lr1.h \
		$D/grammar.h $(ad)/generic/generic.h \
		$D/compdfa.h $D/dfatable.h
lalr1gen.o:	lalr1gen.cc $D/grammar.h $(ad)/generic/generic.h \
		$(ad)/hash/dchash.h $(ad)/contain/hashmap.h $(ad)/contain/dchmap.h \
		$(ad)/memory/mempool.h $D/gentable.h $D/lrgen.h \
		$D/lr0.h $D/lookahd.h $D/operprec.h \
		$D/dfatable.h $(ad)/contain/bitset.h $D/densedfa.h \
		$D/sparsdfa.h $(ad)/memory/mem.h
lookahd.o:	lookahd.cc $D/lookahd.h $D/grammar.h $(ad)/generic/generic.h \
		$(ad)/hash/dchash.h $(ad)/contain/hashmap.h $(ad)/contain/dchmap.h \
		$(ad)/memory/mempool.h $D/gentable.h $D/lrgen.h \
		$D/lr0.h $D/firstset.h $D/nullable.h $D/operprec.h \
		$D/dfatable.h $(ad)/contain/bitset.h $(ad)/memory/mem.h \
		$D/firstset2.h
lrgen.o:	lrgen.cc $D/lrgen.h $(ad)/generic/generic.h \
		$D/compdfa.h $D/sparsdfa.h $D/densedfa.h $D/grammar.h  \
		$D/dfatable.h 
lexer.o:	lexer.cc $D/lexer.h $D/compdfa.h $(ad)/generic/generic.h \
		$D/dfatable.h
lexergen.o:	lexergen.cc $D/lexergen.h $D/labtree.h $D/dfa.h \
		$D/densedfa.h $D/sparsdfa.h $D/compdfa.h $D/nfa.h $D/nfa_node.h\
		$(ad)/contain/varstack.h $(ad)/contain/fixqueue.h \
		$(ad)/hash/dchash.h $(ad)/generic/generic.h \
		$(ad)/contain/bitset.h $D/dfatable.h $(ad)/contain/fbitset.h
ll1.o:		ll1.cc $D/ll1.h $D/grammar.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h
ll1gen.o:	ll1gen.cc $D/ll1gen.h $D/grammar.h $D/sparsdfa.h \
		$D/compdfa.h $(ad)/generic/generic.h $D/dfatable.h \
		$D/nullable.h $D/firstset.h $D/follow.h \
		$(ad)/contain/bitset.h $(ad)/memory/mempool.h $(ad)/memory/mem.h
ll1parse.o:	ll1parse.cc $D/ll1.h \
		$D/grammar.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h
llk.o:		llk.cc $D/llk.h $D/grammar.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h
llkgen.o:	llkgen.cc $D/llkgen.h $D/graminfo.h \
		$D/grammar.h $D/densedfa.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h \
		$D/follow_k.h $D/first_k.h $D/follow.h $D/firstset.h \
		$D/nullable.h $(ad)/contain/bitset.h $(ad)/memory/mempool.h $(ad)/memory/mem.h
lr1gen.o:	lr1gen.cc $D/grammar.h $(ad)/generic/generic.h \
		$(ad)/hash/dchash.h $(ad)/contain/hashmap.h $(ad)/contain/dchmap.h \
		$(ad)/memory/mempool.h $D/gentable.h $D/lr0.h \
		$D/dfatable.h $D/lrgen.h $D/sparsdfa.h $D/compdfa.h
lrk.o:		lrk.cc $D/lrk.h $D/grammar.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/memory/mem.h
lrkgen.o:	lrkgen.cc $D/lrkgen.h $D/graminfo.h \
		$D/grammar.h $D/densedfa.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h
nfa.o:		nfa.cc $D/nfa.h $D/nfa_node.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/contain/fbitset.h $(ad)/contain/bitset.h
nfa_node.o:	nfa_node.cc $D/nfa_node.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/contain/bitset.h $(ad)/contain/fbitset.h
nfa32.o:	nfa32.cc $D/nfa32.h $(ad)/generic/generic.h \
		$D/dfatable.h
scanner.o:	scanner.cc $D/scanner.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/sparsdfa.h $D/densedfa.h \
		$D/lexer.h $D/dfatable.h
sparsdfa.o:	sparsdfa.cc $D/sparsdfa.h $D/compdfa.h \
		$(ad)/contain/varstack.h $(ad)/generic/generic.h \
		$D/dfatable.h
#termpat.o:	termpat.cc $D/termpat.h $(ad)/generic/generic.h \
#		$D/dfatable.h
topdowng.o:	topdowng.cc $D/topdowng.h $D/acgen.h $D/treegram.h \
                $D/sparsdfa.h $D/compdfa.h \
		$(ad)/contain/varstack.h \
		$(ad)/tries/briandai.h $(ad)/generic/generic.h \
		$D/dfatable.h $(ad)/contain/bitset.h
topdown.o:	topdown.cc $D/topdown.h $D/ac.h $D/sparsdfa.h $D/compdfa.h \
		$(ad)/generic/generic.h $D/dfatable.h
treeauto.o:	treeauto.cc $D/treeauto.h $D/gentable.h \
		$(ad)/generic/generic.h $D/dfatable.h $D/treetab.h \
		$(ad)/contain/n_array.h 
#
#  Compiler bug in g++ 2.5.8 under Linux makes it impossible to
#  compile this file with symbols.  
#
#	$(CC) -c -O6 $(CINCLUDE) $(@:.o=.cc)
treegen.o:	treegen.cc $D/treegen.h $D/treegram.h $D/treeauto.h \
		$(ad)/generic/generic.h $(ad)/contain/dchmap.h \
		$(ad)/contain/vararray.h $(ad)/memory/mempool.h \
		$D/dfatable.h $(ad)/memory/mem.h $D/treetab.h \
		$(ad)/contain/bitset.h \
		$D/compdfa.h $D/sparsdfa.h
treegram.o:	treegram.cc $D/treegram.h $D/treeauto.h $(ad)/generic/generic.h \
		$(ad)/contain/bitset.h
#treemat.o:	treemat.cc $D/treemat.h $D/treeauto.h $(ad)/generic/generic.h
#treepat.o:	treepat.cc $D/treepat.h $D/termpat.h $(ad)/generic/generic.h \
#		$(ad)/memory/mempool.h $D/treeauto.h $(ad)/memory/mem.h
regexmat.o:	regexmat.cc $D/regexmat.h $D/lexer.h $D/dfatable.h \
		$(ad)/generic/generic.h
lexerbuf.o:	lexerbuf.cc $D/lexerbuf.h $D/regexmat.h $D/lexer.h \
		$D/dfatable.h $(ad)/generic/generic.h $(ad)/strings/charesc.h
iolexerbuf.o:	iolexerbuf.cc $D/iolexerbuf.h \
		$D/lexerbuf.h $D/regexmat.h $D/lexer.h \
		$D/dfatable.h $(ad)/generic/generic.h $(ad)/strings/charesc.h
iolexerstack.o:	iolexerstack.cc $D/iolexerstack.h $D/iolexerbuf.h \
		$D/lexerbuf.h $D/regexmat.h $D/lexer.h \
		$D/dfatable.h $(ad)/generic/generic.h $(ad)/strings/charesc.h
operprec.o:	operprec.cc $D/operprec.h $D/grammar.h $D/dfatable.h \
		$(ad)/generic/generic.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.cpp
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cpp)

%.o:	%.cxx
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cxx)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)

%.cc:	%.pcc
	$(PROP) $(PROP_OPTS) $(@:.cc=.pcc)
