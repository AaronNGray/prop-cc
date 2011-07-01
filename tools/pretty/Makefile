RM=	/bin/rm
all:	niceprop

spotless:
	$(RM) -f lex.yy.c niceprop *.o 

niceprop:	lex.yy.c
	gcc -O2 lex.yy.c -o niceprop
	strip niceprop

lex.yy.c:	niceprop.l
	flex niceprop.l
