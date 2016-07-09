// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 1/24/2015 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init(0);
	uint32_t delay = 0; 
	SYSCTL_RCGC2_R |= 0x20;
	//NOP
	int i;
	extern int idx;
	for(i=0; i<5; i ++){
	}	
	//Setting I/0
	GPIO_PORTF_DIR_R |= 0x02;
	//AFSEL off
	GPIO_PORTF_AFSEL_R = 0x00;
	//DEN on
	GPIO_PORTF_DEN_R |= 0x02;
  // other initialization
	//
  EnableInterrupts();
  while(1){
		GPIO_PORTF_DATA_R = 0x00;
		if(Piano_In() == 0x01){
			delay = 9615;
			}
		if(Piano_In() == 0x02){
			delay = 7812;
			}
		if(Piano_In() == 0x04){
			delay = 5681;
		}
		if(Piano_In() == 0x00){
			delay = 0;
			idx = 0;
		}
		Sound_Play(delay);	
		
}
}
