#include "tournament.h"
#include <sys/time.h>

#define TOMICRO 1000000
#define ROUNDS  1000000

int main(int argc, char **argv){
  int num_procs,pid,i,j;
  double start,end,total;
  double* recv_buf = NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  if(pid == 0)
  	recv_buf = (double*)calloc(num_procs,sizeof(double));

  tournamentBarrierInit(num_procs);
  
  for(i = 0; i<ROUNDS; i++){
	for(j=0;j<100;j++);
	start = MPI_Wtime();
	tournamentBarrier();
	//printf("%d\n",i);
	end = MPI_Wtime();
	total += end-start;
  }
  total = total/ROUNDS;
  MPI_Gather(&total, 1, MPI_DOUBLE, recv_buf, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  //calculate average,only 1 process needs to do this
  if(pid == 0){
  	double total_time = 0;
	for(i=0;i<num_procs;i++)
		total_time += recv_buf[i];
	printf("%fms\n", total_time / num_procs*TOMICRO);
  	free(recv_buf);
  }
  tournamentBarrierFinalize();
  MPI_Finalize();
  return 0;
}
