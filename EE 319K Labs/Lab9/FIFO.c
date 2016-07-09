#include "tm4c123gh6pm.h"
#include <stdint.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////
#define FIFO_SIZE 10


int FIFO[FIFO_SIZE];
int *PutPt;
int dataa;
int *GetPt;

void FIFO_Init(void){
	PutPt = GetPt = &FIFO[0];
}



int FIFO_Get(int *dat){
	if(GetPt==PutPt){
		return 0;
	}
	if(GetPt == &FIFO[FIFO_SIZE]){
		GetPt = &FIFO[0];
	}
	*dat = *GetPt;
	GetPt++;
	return 1;
	
}

int FIFO_Put(int datt){
	if(PutPt == &FIFO[FIFO_SIZE]){
		PutPt = &FIFO[0];
		return 0;
	}
	*PutPt = datt;  
	PutPt++;
	return 1; 
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
