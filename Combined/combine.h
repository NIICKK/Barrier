#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

typedef enum {false,true} bool;
typedef enum { WINNER, LOSER, BYE, CHAMPION, DROPOUT} Role;
typedef struct{
  Role role;
  int opponent;	//oponent vpid
  MPI_Status stat;
} round_t;

void combineBarrierInit();
void combineBarrier();
void combineBarrierFinalize();
