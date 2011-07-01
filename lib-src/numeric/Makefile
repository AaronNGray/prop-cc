#############################################################################
#  The following parameters must be altered for each platform and compiler.
#  The default is for g++ on Unix and MSDOG.
#############################################################################
ADLIB_PATH	=	../../include
CC		=	gcc
COPTS		=	-g -O6
CINCLUDE	=	-I$(ADLIB_PATH)

ad		=	$(ADLIB_PATH)/AD
D		=	$(ADLIB_PATH)/AD/numeric

#OBJS	= bcd.o bigint.o complex.o fixpt.o gauss.o gaussint.o 
OBJS	= bcd.o bigint.o fixpt.o gauss.o 
OBJS2	= matrix.o pmatrix.o polynom.o rabin.o ratio.o simplex.o solovay.o
OBJS3	= tensor.o trapez.o vector.o vector3d.o z.o 

all:	$(OBJS) $(OBJS2) $(OBJS3)

bcd.o:		bcd.cc $D/bcd.h $(ad)/generic/generic.h
bigint.o:	bigint.cc $D/bigint.h $(ad)/generic/generic.h
complex.o:	complex.cc $D/complex.h $(ad)/generic/generic.h
fixpt.o:	fixpt.cc $D/fixpt.h $(ad)/generic/generic.h
gauss.o:	gauss.cc $D/gauss.h $(ad)/generic/generic.h
gaussint.o:	gaussint.cc $D/gaussint.h $(ad)/generic/generic.h
matrix.o:	matrix.cc $D/matrix.h $(ad)/generic/generic.h
pmatrix.o:	pmatrix.cc $D/pmatrix.h $(ad)/generic/generic.h
polynom.o:	polynom.cc $D/polynom.h $(ad)/generic/generic.h
rabin.o:	rabin.cc $D/primes.h $D/bigint.h $(ad)/generic/generic.h
ratio.o:	ratio.cc $D/ratio.h $D/bigint.h $(ad)/generic/generic.h
simplex.o:	simplex.cc $D/simplex.h $(ad)/generic/generic.h
solovay.o:	solovay.cc $D/primes.h $D/bigint.h $(ad)/generic/generic.h
tensor.o:	tensor.cc $D/tensor.h $(ad)/generic/generic.h
trapez.o:	trapez.cc $D/trapez.h
vector.o:	vector.cc $D/vector.h $(ad)/generic/generic.h
vector3d.o:	vector3d.cc $D/vector3d.h $(ad)/generic/generic.h
z.o:		z.cc $D/z.h $(ad)/generic/generic.h

%.o:	%.cc
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.cc)

%.o:	%.C
	$(CC) -c $(COPTS) $(CINCLUDE) $(@:.o=.C)
