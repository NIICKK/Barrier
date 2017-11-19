#include "centralized.h"
#include <sys/time.h>

#define TOMICRO 1000000

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("USAGE: ./testCentralized [nThreads] [rounds]\n");
        exit(1);
    }
    int num_threads = atoi(argv[1]);
    int rounds = atoi(argv[2]);
   
    omp_set_dynamic(0);
    double time[num_threads];
		
    //INIT HERE
    centralizedBarrierInit(num_threads);
    //Main test HERE
#pragma omp parallel shared(time)
    {
	int thread_id = omp_get_thread_num();
	double start,end,total;
	start = omp_get_wtime();
	int i,j = 0;
	total = 0;
	for (i = 0; i < rounds; i++){
	    for(j=0;j<100;j++);
	    start = omp_get_wtime();
	    centralizedBarrier(num_threads);
	    end = omp_get_wtime();
	    total += end-start;
	}  
	time[thread_id] = total/rounds;
    }

   //FINALIZE HERE
    int i;
    double sum=0;
    for (i = 0; i < num_threads; i++){
        sum+=time[i];
    }
    printf("%fms\n",sum/num_threads*TOMICRO);
    return 0;
}
