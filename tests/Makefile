##############################################################################
#  Makefile for compiling the sample programs in this directory
#  You *must* have prop and adlib already compiled.
##############################################################################

#
#  C++ compiler setup  (assume gcc)
#
CC	= g++
CINCLUDE= -I../include
COPTS	= -O6 -pedantic
LDOPTS	= -lg++
CFLAGS	= $(COPTS) $(CINCLUDE)
LDFLAGS	= -L../lib -lprop $(LDOPTS)
RM	= /bin/rm 

#
#  The executable.  I assume you have set up the directory hierarchy
#  the same way I do. 
#
PROP	= ../bin/prop


#
#  Options to prop
#  -l    generate no #line directives
#  -f    generate fast tables
#  -r    generate a long report listing
#
PROP_OPTS= -report

#
#  The sample source 
#
PROP_SRC= inference.pcc rewriting2.pcc rewriting3.pcc \
	  rewriting5.pcc rewriting6.pcc rewriting7.pcc \
	  logical_patterns.pcc \
	  regexp.pcc list1.pcc list2.pcc printer1.pcc \
	  poly2.pcc \
	  persist1.pcc persist2.pcc persist3.pcc \
	  tuple.pcc insertion_sort.pcc merge_sort.pcc bubble_sort.pcc \
	  test_gc2.pcc test_gc3.pcc test_gc4.pcc \
	  test_gc5.pcc \
	  test_gc9.pcc test_gc10.pcc test_gc11.pcc \
	  test_gc12.pcc test_gc18.pcc \
	  prop1.pcc prop2.pcc prop3.pcc prop4.pcc prop5.pcc prop6.pcc \
	  prop7.pcc prop8.pcc prop9.pcc

#
#  Generated C++ source from prop
#
SRC	= $(PROP_SRC:.pcc=.cc)

#
#  Compiled demo programs
#
PROGS= inference logical_patterns \
       qa1 qa2 qa3 qa5 qa6 qa7 qa8 \
       rewriting2 rewriting3 rewriting5 rewriting6 rewriting7 \
       regexp list1 list2 printer1 \
       poly2 \
       persist1 persist2 persist3 \
       tuple insertion_sort merge_sort bubble_sort \
       test_gc1 test_gc2 test_gc3 test_gc4 test_gc5 test_gc6 test_gc7 \
       test_gc8 test_gc9 test_gc10 test_gc11 test_gc12 test_gc13 test_gc14 \
       test_gc15 test_gc16 test_gc17 test_gc18 test_gc19 test_gc20 \
       test_gc21 test_gc22 test_gc23 test_gc24 \
       prop1 prop2 prop3 prop4 prop5 prop6 prop7 prop8 prop9

#
#  Prop's output log
#
PROP_LOG= rewriting.report rewriting2.report rewriting3.report 


#
#  Various rules
#

build:	$(SRC) $(PROGS)
	@echo Done.
clean:	
	$(RM) -f $(SRC) *.report
spotless:	clean
	$(RM) -f $(PROP_LOG) $(PROGS) 
test:	build run-tests
run-tests:
	>TESTLOG 
	FAILED=0; \
	for p in $(PROGS); do \
	   echo "[Running $$p]"; \
	   (echo "20" | ./$$p); \
	   if [ $$? != 0 ]; then \
	      FAILED=1; \
	      echo "[$$p has failed.]"; \
	      echo "$$p has failed." >>TESTLOG; \
	   fi; \
	done; \
	if [ $$FAILED = 1 ]; then \
	   echo "See TESTLOG for failed tests."; \
	   exit 1; \
	else \
	   echo "All tests ran successfully."; \
	fi

prop4.cc:	prop4.pcc $(PROP)
	$(PROP) $(PROP_OPTS) -save_space -O15 $(@:.cc=.pcc)
%.cc:	%.pcc $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.cc=.pcc)
%.h:	%.ph $(PROP)
	$(PROP) $(PROP_OPTS) $(@:.h=.ph)
prop3:	prop3.cc ../lib/libprop.a
	$(CC) $(CFLAGS) -fno-implicit-templates -o $@ $@.cc $(LDFLAGS)
	strip $@
prop4:	prop4.cc ../lib/libprop.a
	$(CC) $(CFLAGS) -fno-implicit-templates -o $@ $@.cc $(LDFLAGS)
	strip $@
%:	%.cc ../lib/libprop.a
	$(CC) $(CFLAGS) -o $@ $@.cc $(LDFLAGS)
	strip $@
