// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 3/6/2015 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;      														// 1)  Activate clock for Port E 
  while((SYSCTL_PRGPIO_R&0x10) == 0){};
	int i;
	for(i=0; i<5; i ++){
	}	
	//Setting I/0
	GPIO_PORTE_DIR_R &= 0xFB;
	//AFSEL off
	GPIO_PORTE_AFSEL_R |= 0x04;
	//DEN on
	GPIO_PORTE_DEN_R &= 0xFB;
	GPIO_PORTE_AMSEL_R |= 0x04;
	SYSCTL_RCGCADC_R |= 0x01;
	for(i=0; i<5; i ++){
	}	
	ADC0_PC_R = 0x01;
	ADC0_SSPRI_R |= 0x123;
	ADC0_ACTSS_R &= 0xF7;
	ADC0_EMUX_R |= 0x0FFF; //Hold Johnny Responsible
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R & 0xFFFFFFF0) + 1;
	ADC0_SSCTL3_R = 0x06;
	ADC0_IM_R &= 0xF7;
	ADC0_ACTSS_R |= 0x08;

}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
	uint32_t data;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R & 0x08) == 0){};
	data = ADC0_SSFIFO3_R & 0xFFF;
	ADC0_ISC_R = 0x0008;
  return data;
}


