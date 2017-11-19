OMPFLAGS = -fopenmp
OMPLIBS  = -lgomp

CC = gcc -w 
CPPFLAGS = -g -Wall $(OMPFLAGS)
LDFLAGS = -g -Wall
LDLIBS = $(OMPLIBS)

all: testCentralized

testCentralized: testCentralized.o centralized.o
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

