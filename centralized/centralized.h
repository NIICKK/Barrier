#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

typedef enum {false,true} bool;
void centralizedBarrierInit(int num_threads);
void centralizedBarrier ();
