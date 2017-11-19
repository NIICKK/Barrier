#include "tournament.h"

round_t* rounds;	//array [0..LogP] of round_t, each MPI process maintains its rounds structure
int processCount, roundCount, vpid;

void tournamentBarrierInit(int process_count){
  processCount = process_count;
  roundCount = (int)ceil(log2(processCount))+1;	// roundCount = log(processCount)+1 - last round + 1
  rounds = (round_t*)calloc(roundCount+1,sizeof(round_t));
  
  int k,prevKpow,curKpow = 1; //pow(2,k) = pow(2,0) = 1 initially
  MPI_Comm_rank(MPI_COMM_WORLD, &vpid);
  for(k=0;k<roundCount;k++){
	//set role and oponent
	if(k == 0){
		rounds[k].role = DROPOUT;	
	}
	else if(vpid == 0 && curKpow >= processCount){
		rounds[k].role = CHAMPION;
		rounds[k].opponent = vpid + prevKpow;
	}
	else if(vpid % curKpow == prevKpow){
		rounds[k].role = LOSER;
		rounds[k].opponent = vpid - prevKpow;
	}
	else if(vpid % curKpow == 0){
		if(vpid+prevKpow >= processCount){
			rounds[k].role = BYE;
		}
		else if(curKpow < processCount){
			rounds[k].role = WINNER;
			rounds[k].opponent = vpid + prevKpow;		
		}	
	}
	prevKpow = curKpow;
	curKpow *= 2;	
  }
}

void tournamentBarrier(){
  int k = 1;
  //arrival
  bool loop = true; 
  while(loop){
  	switch(rounds[k].role){
		case LOSER:
			//using MPI_send and MPI_recv replaces the original usage of sense 
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

void tournamentBarrierFinalize(){
  if(rounds!=NULL) free(rounds);
}
