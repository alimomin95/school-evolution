// Lab8.c
// Runs on LM4F120 or TM4C123
// Student names: Zain Modi and Ali Ziyaan Momin
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 3/6/2015 

// Analog Input connected to PE2=ADC1
// displays on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats

#include <stdint.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "tm4c123gh6pm.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on Nokia
// main3 adds your convert function, position data is no Nokia

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

uint32_t data = 0;
uint32_t ADCStatus = 0;
uint32_t ADCMail = 0;

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;
	//NOP
	int i;
	extern int idx;
	for(i=0; i<5; i ++){
	}	
	//Setting I/0
	GPIO_PORTF_DIR_R |= 0x04;
	//AFSEL off
	GPIO_PORTF_AFSEL_R = 0x00;
	//DEN on
	GPIO_PORTF_DEN_R |= 0x04;
}
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 800000000;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000007;
	ADC_Init();
	PortF_Init();
}

uint32_t AVeraG(void){
	uint32_t avg;
	int z;
	uint32_t dat = 0;
	for(z=0; z<256; z ++){
		dat = dat + ADCMail;	
	}
	avg = dat / z;
	
	return(avg);
}
void SysTick_Handler(void){
	GPIO_PORTF_DATA_R ^= 0x04;
	GPIO_PORTF_DATA_R ^= 0x04;
	ADC0_ISC_R = 0x0008;
	ADCMail = ADC_In();
	ADCStatus = 1;
	GPIO_PORTF_DATA_R ^= 0x04;
}
uint32_t Data;        // 12-bit ADC
uint32_t Position;    // 32-bit fixed-point 0.001 cm
int main8(void){      // single step this program and look at Data
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 1
  while(1){                
    Data = ADC_In();  // sample 12-bit channel 1
  }
}

int main6(void){
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 1
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  while(1){           // use scope to measure execution time for ADC_In and LCD_OutDec           
    PF2 = 0x04;       // Profile ADC
    Data = ADC_In();  // sample 12-bit channel 1
    PF2 = 0x00;       // end of ADC Profile
    ST7735_SetCursor(0,0);
    PF1 = 0x02;       // Profile LCD
    LCD_OutDec(Data); 
    ST7735_OutString("    ");  // these spaces are used to coverup characters from last output
    PF1 = 0;          // end of LCD Profile
  }
}
//y=0.4809x + 141.57
uint32_t Convert(uint32_t input){
  uint32_t y;
	y = 481*input + 141570;
	y = y / 1000;
	return (y);
}
int main9(void){ 
  TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  ADC_Init();         // turn on ADC, set channel to 1
  while(1){  
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 1
    PF3 = 0x08;       // Profile Convert
    Position = Convert(Data); 
    PF3 = 0;          // end of Convert Profile
    PF1 = 0x02;       // Profile LCD
    ST7735_SetCursor(0,0);
    LCD_OutDec(Data); ST7735_OutString("    "); 
    ST7735_SetCursor(6,0);
    LCD_OutFix(Position);
    PF1 = 0;          // end of LCD Profile
  }
}   
int main(void){
  TExaS_Init();
	ST7735_InitR(INITR_REDTAB); 
	SysTick_Init();
  // your Lab 8
  while(1){
		uint32_t con;
		if(ADCStatus == 1){
			data = AVeraG();
			con = Convert(data);
			ST7735_SetCursor(0,0);
			LCD_OutFix(con);
			ADCStatus = 0;
			PF1 = 0;          // end of LCD Profile

		}
  }
}
	
