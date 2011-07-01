PROP	=	../bin/prop
PROP_OPTS=	-report -v2 -strict -non_linear
CC	= 	g++
CINCLUDE=	-I../include
LDOPTS	=	
COPTS	=	-O6 -pedantic
CFLAGS	=	$(COPTS) $(CINCLUDE) 
LDFLAGS =	-L../lib -lprop $(LDOPTS)

PROP_C_SRC=	logic.pC logic2.pC logic3.pC \
		inference.pC persistence.pC prog.pC exp.pC \
		rewrite-trick1.pC rewrite-trick2.pC rewrite-trick3.pC \
		rewrite-trick4.pC rewrite-trick5.pC 
#		rewrite-trick6.pC

PROP_H_SRC=	logic3.ph
C_SRC	=	$(PROP_C_SRC:.pC=.C)
H_SRC	=	$(PROP_H_SRC:.ph=.h)
OBJS	=	$(C_SRC:.C=.o)
PROGS	=	$(C_SRC:.C=)

all:	$(C_SRC) $(OBJS) $(PROGS)
	@echo Sample programs compiled

spotless:
	rm -f $(C_SRC) $(OBJS) $(PROGS) *.report *.dat

logic3.C:	logic3.h

%.C:	%.pC $(PROP)
	$(PROP) $(PROP_OPTS) $<
%.h:	%.ph $(PROP)
	$(PROP) $(PROP_OPTS) $<
%.o:	%.C 
	$(CC) -c $(CFLAGS) $< 
%:	%.o ../lib/libprop.a
	$(CC) $(CFLAGS) $@.o -o $@ $(LDFLAGS)
	strip $@
