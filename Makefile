#############################################################################
#
#  Top level makefile for installing Prop and ADLib
#
#############################################################################

VERSION	= 2.3.0

RM	= rm -f
LIBRARY	= libprop.a
CC	= g++
COPTS   	= -O6 -pedantic
PROP_COPTS	= $(COPTS) -Wno-deprecated
LIBRARY_COPTS   = -O6 -pedantic -Wall -Wno-deprecated
LDOPTS  = #-lg++

TARGET_BIN_DIR = /usr/local/bin
TARGET_LIB_DIR = /usr/local/lib
TARGET_INCLUDE_DIR = /usr/local/include

##############################################################################
#   Files in the ADLib package:
##############################################################################
MiscFiles= INSTALL README NOTICE COPYRIGHT \
	   Makefile lib-src/Makefile
Areas	= algebra automata contain csp dynparser gc generic \
	  generic hash memory numeric object objc \
	  prop rete rewrite persist prettypr \
	  sort strings symbolic trees tries \
	  scheduling absinterp machine dataflow parser-tools \
	  backend_tools
TarFile= prop-$(VERSION).tar.gz

#############################################################################
#
#   Build the ADLib library and the tools
#
#############################################################################
build:
	cd lib-src; make CC="$(CC)" COPTS="$(LIBRARY_COPTS)" LDOPTS="$(LDOPTS)"
	cd prop-src; make CC="$(CC)" COPTS="$(PROP_COPTS)" LDOPTS="$(LDOPTS)"
	cd docs; make
	@echo Done

config:
	./Configure $(CC)

#############################################################################
#
#   Test prop
#
#############################################################################
test:
	cd prop-src; make test CC="$(CC)" COPTS="$(COPTS)" LDOPTS="$(LDOPTS)"
	@echo Testing of the prop translator ran ok.

testall:
	cd tests; make test CC="$(CC)" COPTS="$(COPTS)" LDOPTS="$(LDOPTS)"
	@echo All test programs ran ok.

demo:
	cd demos; make CC="$(CC)" COPTS="$(COPTS)" LDOPTS="$(LDOPTS)"
	@echo All demo programs have been compiled.

#############################################################################
#
#  Line count
#
#############################################################################
wc:
	wc include/AD/*/*.h lib-src/*/*.cc \
	prop-src/[a-z]*.ph \
	prop-src/[a-z]*.pcc

#############################################################################
#
#  Clean up: remove all *.o files and .cc and .h files generated using
#            Prop.  But don't remove the executable and the library.
#
#############################################################################
spotless:
	cd lib-src; make spotless
	cd prop-src; make spotless
	cd tools/test; make spotless
	cd tests; make spotless
	cd demos; make spotless
	cd tools/pretty; make spotless
	#cd docs; make spotless

cleanhouse:
	cd lib-src; make spotless
	cd prop-src; make clean
	cd tools/test; make spotless
	cd tests; make spotless
	cd demos; make spotless
	cd tools/pretty; make spotless
	cd docs; make spotless
	$(RM) lib-src/$(LIBRARY) prop-src/prop

clean:
	cd lib-src; make spotless
	cd prop-src; make clean

#############################################################################
#  Make tar.gz files for Unix distribution.
#############################################################################
dist:	tar
tar:
	bin/Distribute NO_DISTRIBUTE
full-dist:
	bin/Distribute NO_DISTRIBUTE2

first-install:
	cp prop-src/prop $(TARGET_BIN_DIR)
	chmod 755 $(TARGET_BIN_DIR)/prop
	cp tools/scripts/* $(TARGET_BIN_DIR)
	cp lib-src/$(LIBRARY) $(TARGET_LIB_DIR)
	chmod 644 $(TARGET_LIB_DIR)/$(LIBRARY)
	cp include/propdefs.h $(TARGET_INCLUDE_DIR)

install: first-install
	ln -f -s `pwd`/include/AD $(TARGET_INCLUDE_DIR)/AD

full-install: first-install
	(umask 022; cp -R include $(TARGET_INCLUDE_DIR))
