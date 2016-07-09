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
#include "FIFO.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on Nokia
// main3 adds your convert function, position data is no Nokia

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

uint32_t data = 0;
uint32_t ADCStatus = 0;
uint32_t ADCMail = 0;
int con=0;
char array[5];

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


int error = 0;
int RxCounter= 0;
char Mail;
void UART1_Handler(void){
	GPIO_PORTF_DATA_R ^= 0x04;
	GPIO_PORTF_DATA_R ^= 0x04;
	FIFO_Init();
	while((UART1_FR_R &=0x10) == 0){
		Mail = (UART1_DR_R & 0xFF); //masking the bits out 
		error = FIFO_Put(Mail);
		if(Mail == 0){
		error++;
	}
	}
	
	RxCounter++;
	UART1_ICR_R = 0x10;
	GPIO_PORTF_DATA_R ^= 0x04;
	
}



//initialize PE1 and PE0 for UART7
int clock;
	void UART1_Init(void){
	volatile unsigned long clock_Delay;
  SYSCTL_RCGCUART_R |= 0x0002;		// Activate UART1
		int i;
		for(i=0; i<5; i ++){
	}
		i=0;
  SYSCTL_RCGCGPIO_R |= 0x0004; 											// Port C activation
		for(i=0; i<5; i ++){
	}
	UART1_CTL_R &= 0xFFFE;      											// Disable UART
  UART1_IBRD_R = 50;  															// IBRD=int(80000000/(16*100,000)) = int(50)
	UART1_FBRD_R = 0;  																// FBRD = round(0.0 * 64) = 0
	UART1_LCRH_R = 0x0070;  													// 8-bit length, enable FIFO
	UART1_CTL_R = 0x0301;   													// Enable RXE, TXE and UART
	GPIO_PORTC_AFSEL_R |= 0x30; 											// Alt funct on PC4-5, UART1
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF);
	GPIO_PORTC_PCTL_R = GPIO_PORTC_PCTL_R + 0x00220000;
  GPIO_PORTC_DEN_R |= 0x30;   											// Digital I/O on PC4-5
	GPIO_PORTC_AMSEL_R &= 0xAF; 											// No analog on PC4-5
	
	UART1_IM_R |= 0x10;
  UART1_IFLS_R = (UART1_IFLS_R&0xFFFFFFC7);         // set bits 5,4,3 to 010 (1/2 full)
	UART1_IFLS_R = UART1_IFLS_R + 0x10;
	NVIC_PRI1_R = 0x00E00000;					  							// bits 21-23
  NVIC_EN0_R |= 0x00000040;													// enable interrupt 6 in NVIC
}

//Wait for buffer to be not full, then output
void UART1_OutChar(uint8_t thing) 
	{
	
  while((UART1_FR_R&0x20) != 0);  							//TXFF not zero, wait until then 	
  UART1_DR_R = thing;
}

void Con_to_ASCII(int data){
	char temp;
	
	temp = (data/1000) + 0x30;
	array[0] = temp;
	data = data % 1000;
	
	temp = 0x2E;
	array[1] = temp;
	
	temp = (data/100) + 0x30;
	array[2] = temp;
	data = data % 100;
	
	temp = (data/10) + 0x30;
	array[3] = temp;
	data = data % 10;
	
	temp = data + 0x30;
	array[4] = temp;
	
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
//y=0.4809x + 141.57
uint32_t Convert(uint32_t input){
  uint32_t y;
	y = 481*input + 141570;
	y = y / 1000;
	return (y);
}
int TXCounter=0;
void SysTick_Handler(void){
	GPIO_PORTF_DATA_R ^= 0x04;
	ADC0_ISC_R = 0x0008;
	ADCMail = ADC_In();
	GPIO_PORTF_DATA_R ^= 0x04;
	ADCStatus = 1;
	data = AVeraG();
	con = Convert(data);
	Con_to_ASCII(con);
	UART1_OutChar(0x02);
	int i = 0;
	while(i<5){
		UART1_OutChar(array[i]);
		i ++;
	}
	UART1_OutChar(0x0D);
	UART1_OutChar(0x03);
	TXCounter++;
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

int main20	(void){
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
int check = 0;
int main10(void){
  TExaS_Init();
	ST7735_InitR(INITR_REDTAB); 
	SysTick_Init();
	UART1_Init();
	FIFO_Init();
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

	int main(void){
		int arrays[20];
		int i;
		TXCounter =0;
		RxCounter=0;
		error=0;
		check = 0; 
		DisableInterrupts();
		TExaS_Init();
		PortF_Init();
		FIFO_Init();
		ST7735_InitR(INITR_REDTAB);
		ADC_Init();
		UART1_Init();
		SysTick_Init();
		EnableInterrupts();
		
		while(1){
			check = FIFO_Get(arrays);
			
				if(check != 1){
					check++;
		}
				
			check = FIFO_Get(arrays);
			if(arrays[0] == 0x02){
				ST7735_SetCursor(0,0);
				i=0;
				check = FIFO_Get(arrays);
			while(i<5){
				ST7735_OutChar(*arrays);
				check = FIFO_Get(arrays);
				if(check != 1){
					check++;
		}
				i++;
				}
			ST7735_OutChar(' ');
			ST7735_OutChar('c');
			ST7735_OutChar('m');
			}
	}
}
