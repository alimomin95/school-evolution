#include <stdint.h>
#include "ST7735.h"
#include "TExaS.h"



void Timer0_Init(void(*task)(void), uint32_t period);
void Timer0A_Handler(void);
void Timer0A_Stop(void);
void Timer0A_Start(void);
	
void Timer1_Init(void(*task)(void), uint32_t period);
void Timer1A_Handler(void);
void Timer1A_Stop(void);
void Timer1A_Start(void);
	
void Timer2_Init(void(*task)(void), uint32_t period);
void Timer2A_Handler(void);
void Timer2A_Stop(void);
void Timer2A_Start(void);
		

