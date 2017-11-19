#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef enum { false, true } bool;	//in C 0 - false, 1 -true
typedef enum { WINNER, LOSER, BYE, CHAMPION, DROPOUT} Role;
typedef struct{
  Role role;
  int opponent;	//oponent vpid
  MPI_Status stat;
} round_t;

void tournamentBarrierInit(int process_count);
void tournamentBarrier();
void tournamentBarrierFinalize();

