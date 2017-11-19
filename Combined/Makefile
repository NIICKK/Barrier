OMPFLAGS = -fopenmp
OMPLIBS = -lgomp

CC = gcc -w
CPPFLAGS = -g -Wall $(OMPFLAGS) 
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

MPICC =  mpicc
MPICH = /usr/lib64/openmpi
CFLAGS = -I$(MPICH)/include

all: testMPI testDisseminationMPI testTournament testCombine

testMPI:  MPI.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) -lm

testDisseminationMPI: testDisseminationMPI.o MPIdissemination.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) -lm

testTournament: testTournament.o tournament.o
	$(MPICC) -o $@ $(LDFLAGS) $^ $(LDLIBS) -lm

testCombine:  testCombine.o combine.o
	$(MPICC) -o $@ $(CPPFLAGS) $^ $(LDLIBS) -lm 

clean:  
	rm -f *.o testMPI testDisseminationMPI testTournament testCombine

