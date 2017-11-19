#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef enum { false, true } bool;	//in C 0 - false, 1 -true
void MPIdisseminationBarrierInit(int numProcs, int pid);
void MPIdisseminationBarrier();


