PROP_VER= 2.0
PROP	= ../prop-src/prop
# Generate report with lookahead information.
PROP_OPTS= -r3
RM	= rm -f

PROP_SRC= g0.pcc g1.pcc g2.pcc g3.pcc g7.pcc parse.pcc
SRC	= g0.cc g1.cc g2.cc g3.cc g7.cc parse.cc
OUTPUT	= g0.report g1.report g2.report g3.report g7.report parse.report

src:	$(SRC)
	@echo "Done"

clean:	spotless

spotless:
	$(RM) $(SRC) $(OUTPUT)

%.cc:	%.pcc $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.cc=.pcc)
