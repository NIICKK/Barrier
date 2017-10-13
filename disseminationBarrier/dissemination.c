#include "dissemination.h"

#define NO_MSG 0
#define MSG 1

int rounds; 	
int msgArray[12][20];//MAX #ofthreads and MAX #ofround

void setBarrier(int numThreads){
        omp_set_num_threads(numThreads);
	rounds = ceil(log(numThreads)/log(2));	
        
	for (int i = 0; i < rounds; i++){
                for (int j =0; j < numThreads; j++){
		        msgArray[i][j] = 0; 
                }
	}
}

void runBarrier(int numThreads){
	int refID, myID = omp_get_thread_num();
	//run each round, i: round number
	for (int i = 0; i < rounds; i++){
                //the prcosss who sends me the message
		refID = (myID + (int)pow(2,i))%numThreads;

                /*if yet to send msg -> spin*/
		while(msgArray[i][refID] == MSG);
		msgArray[i][refID] = MSG;//send msg now

		/*if yet to recieve msg -> spin*/
		while(msgArray[i][myID] == NO_MSG);

                //reset and go to next round
		msgArray[i][myID] = NO_MSG;
	}
}
