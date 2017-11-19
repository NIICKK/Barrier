OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc
CPPFLAGS = -g -Wall
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC = mpicc
MPICH = /usr/lib/openmpi
CFLAGS = -I$(MPICH)/include

all: testTournament

testTournament: testTournament.o tournament.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) -lm

