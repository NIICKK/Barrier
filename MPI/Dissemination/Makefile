OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC = mpicc
MPICH = /usr/lib/openmpi
CFLAGS = -I$(MPICH)/include

all: testDisseminationMPI

testDisseminationMPI: testDisseminationMPI.o MPIdissemination.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) -lm

