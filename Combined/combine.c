#include "combine.h"

round_t* rounds;
int P,T,count,roundCount;
bool sense;

void combineBarrierInit(int num_procs, int num_threads){
  P = num_procs;
  T = num_threads;
  //init centralized barrier
  count = T;
  sense = true;
  omp_set_num_threads(num_threads);
  //init tournament barrier
  roundCount = (int)ceil(log2(P))+1;
  rounds = (round_t*)calloc(roundCount+1,sizeof(round_t));
  int vpid,k,prevKpow,curKpow = 1; //pow(2,k) = pow(2,0) = 1 initially
  MPI_Comm_rank(MPI_COMM_WORLD, &vpid);
  for(k=0;k<roundCount;k++){
	//set role and oponent
	if(k == 0){
		rounds[k].role = DROPOUT;	
	}
	else if(vpid == 0 && curKpow >= P){
		rounds[k].role = CHAMPION;
		rounds[k].opponent = vpid + prevKpow;
	}
	else if(vpid % curKpow == prevKpow){
		rounds[k].role = LOSER;
		rounds[k].opponent = vpid - prevKpow;
	}
	else if(vpid % curKpow == 0){
		if(vpid+prevKpow >= P){
			rounds[k].role = BYE;
		}
		else if(curKpow < P){
			rounds[k].role = WINNER;
			rounds[k].opponent = vpid + prevKpow;		
		}	
	}
	prevKpow = curKpow;
	curKpow *= 2;	
  }
}

void combineBarrier(){
  bool localSense = !sense;	//toggle local sense
  //atomic decrement - an alternative is __Sync_fetch_and_sub but here we are using openMP style code 
  //printf("%d",count);
  if(__sync_fetch_and_sub(&count, 1) == 1){
	count = T;
	sense = localSense;
  }
  else{
	//printf("count %d\n",count);
	while(sense != localSense);
  }	 
  if(omp_get_thread_num() == 0){
  	 //do tournament barrier HERE
	  int k = 1;
	  //arrival
	  bool loop = true; 
	  while(loop){
	  	switch(rounds[k].role){
			case LOSER:
				MPI_Send(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD);
				MPI_Recv(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD, &rounds[k].stat);
				loop = false;
				break;
			case WINNER:
				MPI_Recv(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD, &rounds[k].stat);
				break;
			case CHAMPION:
				MPI_Recv(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD, &rounds[k].stat);
				MPI_Send(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD);
				loop = false;
				break;
			default:
				break;
		}
		k++;
	  }
	  //wakeup
	  loop = true;
	  while(loop){
	  	k--;
		switch(rounds[k].role){
			case WINNER:
				MPI_Send(NULL, 0, MPI_INT, rounds[k].opponent, k, MPI_COMM_WORLD);
				break;
			case DROPOUT:
				loop = false;
				break;
			default:
				break;
			
		}
	  }
  }
}

void combineBarrierFinalize(){
  if(rounds != NULL) free(rounds);
}

