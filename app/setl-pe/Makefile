PROP=		../../bin/prop
PROP_OPTS=	-s -S -O15 -r -v2
#PROP_OPTS=	-S -O15 -r -v2
CC=		g++
COPTS=		-O2
CINCLUDE=	-I../../include

H_SRC=	foundation.h setl-lexeme.h setl-ast.h setl-syntax.h
C_SRC=	setl-lexer.cc setl-syntax.cc setl-ast.cc
SRC=	$(H_SRC) $(C_SRC) 
OBJS=	setl-lexer.o setl-syntax.o setl-ast.o

all:	$(SRC) $(OBJS)

spotless:
	/bin/rm -f *.o $(SRC) *.report

tar:
	tar -cvf - Makefile *.*cc *.*h | gzip >SETL.tar.gz

setl-syntax.cc: foundation.ph setl-lexeme.ph setl-syntax.ph setl-ast.ph setl-syntax.pcc 
setl-lexer.cc:	foundation.ph setl-lexeme.ph setl-lexer.pcc
setl-ast.cc:	foundation.ph setl-ast.ph setl-ast.pcc

setl-syntax.o:	foundation.h setl-lexeme.h setl-syntax.h setl-syntax.cc
setl-lexer.o:	foundation.h setl-lexeme.h setl-lexer.cc
setl-ast.o:	foundation.h setl-ast.h setl-ast.cc

%.h:	%.ph $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.h=.ph) 
%.cc:	%.pcc  $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.cc=.pcc) 
%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc) 
