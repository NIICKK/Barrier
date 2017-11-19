OMPFLAGS = -fopenmp
OMPLIBS  = -lgomp

CC = gcc -w 
CPPFLAGS = -g -Wall $(OMPFLAGS)
LDFLAGS = -g -Wall 
LDLIBS = $(OMPLIBS)

all: testDissemination

testDissemination: testDissemination.o dissemination.o
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDLIBS) -lm
