TEX	=	refman.tex
DVI	=	refman.dvi
PS	=	refman.ps
RM	= 	/bin/rm
INDEXSTYLE=	bbind.ist

all:	$(DVI) $(PS)

ps:	$(PS)

again:	
	touch $(TEX)
	bibtex refman
	makeindex -s $(INDEXSTYLE) refman.idx
	make 
index:
	makeindex -s $(INDEXSTYLE) refman.idx
html:
	latex2html refman.tex

%.dvi:	%.tex
	latex $(@:.dvi=.tex)
%.ps:	%.dvi
	dvips $(@:.ps=.dvi) -o $@

spotless:
	$(RM) -f *.dvi *.ps *.log *.aux *.blg *.bbl *.toc *.info
