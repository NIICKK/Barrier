#include "MPIdissemination.h"

int num_procs,roundCount;

void MPIdisseminationBarrierInit(int numProcs, int pid){
    num_procs = numProcs;
    roundCount = (int)ceil(log2(num_procs));
}
    
void MPIdisseminationBarrier(){
    int vpid; 
    MPI_Comm_rank(MPI_COMM_WORLD, &vpid);
    int i;
    for (i = 0; i < roundCount; i++) {
        MPI_Send(NULL, 0, MPI_INT, (vpid + (1 << i)) % num_procs, 1, MPI_COMM_WORLD);
        MPI_Recv(NULL, 0, MPI_INT, (vpid + num_procs - (1 << i)) % num_procs, 1, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);	//vpid + P to make sure it is not negative
    }
}






