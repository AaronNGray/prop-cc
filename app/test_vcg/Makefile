PROP=		../../bin/prop
PROP_OPTS=	-s -S -O15 -r -v2
#PROP_OPTS=	-S -O15 -r -v2
CC=		g++
COPTS=		-O2 -pedantic
CINCLUDE=	-I../../include
LDOPTS=	-L../../lib -lprop
LIBRARY=../../lib/libprop.a

H_SRC=	
C_SRC=  exp.cc
SRC=	$(H_SRC) $(C_SRC) 
OBJS=	cfg.o exp.o
PROGS=		cfg exp

all:	$(SRC) $(OBJS) $(PROGS)

spotless:
	/bin/rm -f *.o $(SRC) $(PROGS) *.report

tar:
	tar -cvf - Makefile *.*cc *.*h | gzip >VCG.tar.gz

cfg.o:	cfg.cc

cfg:	cfg.o $(LIBRARY)
	$(CC) $(COPTS) $@.o $(LDOPTS) -o $@
	strip $@

exp:	exp.o $(LIBRARY)
	$(CC) $(COPTS) $@.o $(LDOPTS) -o $@
	strip $@

%.h:	%.ph $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.h=.ph) 
%.cc:	%.pcc  $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.cc=.pcc) 
%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc) 
