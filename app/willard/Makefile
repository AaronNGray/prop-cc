PROP		=	../../bin/prop
PROPOPTS	=	-strict -report -v2 -save_space -Orewriting
PROPLIBDIR	= 	../../lib

CC 		= g++
CINCLUDE	= -I../../include 
COPTS		= -O6 -pedantic 
LDOPTS		= -lg++ 
CFLAGS		= $(CINCLUDE) $(COPTS)
LDFLAGS		= -L$(PROPLIBDIR) -lprop $(LDOPTS)

PROP_H_SRC	= willard-ast.ph paige.ph parser.ph rename.ph \
		  querygraph.ph smap.ph \
		  phase1.ph phase2.ph phase3.ph phase4.ph phase5.ph proj.ph \
		  willard.ph list.ph
PROP_C_SRC	= willard-ast.pcc paige.pcc paige-aux.pcc rename.pcc \
		  querygraph.pcc \
		  phase1.pcc phase2.pcc phase3.pcc phase4.pcc phase5.pcc proj.pcc \
		  parser.pcc willard.pcc 
PROP_SRC	= $(PROP_H_SRC) $(PROP_C_SRC)

GEN_H_SRC	= $(PROP_H_SRC:.ph=.h)
GEN_C_SRC	= $(PROP_C_SRC:.pcc=.cc)
GEN_SRC		= $(GEN_H_SRC) $(GEN_C_SRC)

C_SRC		= $(GEN_C_SRC)

OBJS		= $(C_SRC:.cc=.o)

all:	$(GEN_SRC) $(OBJS) willard

willard:	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@ 
wc:	
	wc $(PROP_SRC)
genwc:	
	wc $(GEN_SRC)
spotless:
	rm -f $(GEN_SRC) $(OBJS) *.report
test:	willard run-test

run-test:
	for t in 1 2 3 4 5 6 7 ; do \
	   echo "./willard <data$$t >test$$t"; \
	   ./willard <data$$t >test$$t; \
	   echo "diff out$$t test$$t"; \
	   diff out$$t test$$t; \
	   if [ $$? = 1 ] ; then \
	      exit 1; \
	   fi; \
	done 
	@echo All tests ran ok.

makeout:	willard
	for t in 1 2 3 4 5 6 7 ; do \
	   ./willard <data$$t >out$$t; \
	done

%.o:	%.cc
	$(CC) -c $(CFLAGS) $< 
%.cc:	%.pcc $(PROP)
	$(PROP) $(PROPOPTS) $< 
%.h:	%.ph $(PROP)
	$(PROP) $(PROPOPTS) $< 

depends: $(GEN_SRC)
	$(PROP) -M $(PROPOPTS) $(PROP_H_SRC) $(PROP_C_SRC) > prop-depends
	$(CC) -MM $(COPTS) $(C_SRC) > c-depends

include prop-depends
include c-depends
