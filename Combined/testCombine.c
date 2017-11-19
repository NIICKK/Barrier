#include <sys/time.h>
#include "combine.h"

int main(int argc, char **argv) {
    int num_procs,num_threads,rounds,pid;

    if (argc != 3)
    {
        printf("usage: ./test_openmp [nthreads] [rounds]\n");
        exit(1);
    }
    num_threads = atoi(argv[1]);
    rounds = atoi(argv[2]);
   
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    combineBarrierInit(num_procs, num_threads);
    double time[num_threads];

#pragma omp parallel shared(time)
{
        int thread_id = omp_get_thread_num();
	double start,end,total;        
	int i,j;
        for (i = 0; i < rounds; i++){
		for(j=0;j<100;j++);
		start = omp_get_wtime();
		combineBarrier();
		end = omp_get_wtime();
		total += end-start;
	}
	total = total / rounds;
        time[thread_id] = total;
}

    double sum = 0;
    int i;
    for (i = 0; i < num_threads; i++)
        sum += time[i];
    double avgTime = sum / num_threads;

    /* calculate avg result from all node */
    double* recv_buf = (double*) calloc(num_procs ,sizeof(double));
    MPI_Gather(&avgTime, 1, MPI_DOUBLE, recv_buf, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (pid == 0) {
        double avgTimeSum = 0;
        for (i = 0; i < num_procs; i++) avgTimeSum  += recv_buf[i];
        printf("c: %f\n", avgTimeSum / num_procs);
    }

    free(recv_buf);
    combineBarrierFinalize();  
    MPI_Finalize();
    return 0;
}
