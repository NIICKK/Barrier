#include "centralized.h"

void runCentralized (int *num, int *globalSense){

	int NUMTHREADS = *num; 
	int localSense = *globalSense;
        
        /*decrement*/
	#pragma omp critical 
	{
		*num = *num - 1;
	}

	/*flip local sense if the last thread*/
	if( *num == 0 ){
		*num = NUMTHREADS;
		/* Flip the sense for all threads*/
		*globalSense = !localSense;
	}
	else {
		/* Spin on sense reversal*/
		while( *globalSense == localSense );
	}
}



