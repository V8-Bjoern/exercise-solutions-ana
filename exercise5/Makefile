# Makefile for intro to C++ with ROOT

CPP=g++
LD=g++

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS =
LFLAGS =

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC1= dV.o mcint.o

%.o: %.cxx
	$(CPP) $(RCXX) -c $<

all: mcint

mcint: $(SRC1)
	$(LD) $(SRC1) $(RLXX) -o mcint
	@echo '-> mcint created!'

clean:
		@rm -f *~
		@rm -f *.o 
		@rm -f *.x
