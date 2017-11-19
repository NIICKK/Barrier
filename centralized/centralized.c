#include "centralized.h"

int count;
bool sense;
int threadCount;

void centralizedBarrierInit(int num_threads){
	threadCount = num_threads;	
	count = num_threads;
	sense = true;
	omp_set_num_threads(num_threads);
}

void centralizedBarrier(){ 
	bool localSense = !sense;	//toggle local sense
       	//atomic decrement - an alternative is __Sync_fetch_and_sub but here we are using openMP style code
	//printf("%d",count);
	if(__sync_fetch_and_sub(&count, 1) == 1){
		count = threadCount;
		sense = localSense;
	}
	else{
		while(sense != localSense);
	}	
}



