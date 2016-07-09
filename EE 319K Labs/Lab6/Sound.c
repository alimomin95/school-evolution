// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(uint32_t period){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 80000;
	NVIC_ST_CURRENT_R = 0;
	//NVIC_SYS_PRI3_R = ((NVIC_SYS_PRI3_R&0x00FFFFFF) | 0x40000000); //priority 2 
	NVIC_ST_CTRL_R = 0x00000007;
	DAC_Init();
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
uint8_t SinTab[32] = {8,9,11,13,14,14,15,15,15,15,14,14,13,11,9,8,7,6,4,2,1,1,0,0,0,0,1,1,2,4,6,7};
 
void Sound_Play(uint32_t period){
	NVIC_ST_RELOAD_R = period;

}
int work;
int idx = 0;
void SysTick_Handler(void){
		GPIO_PORTF_DATA_R ^= 0x02;
		work = SinTab[idx];
		DAC_Out(work);
		idx = idx + 1;
		idx = idx % 32;
}
