// ***** 0. Documentation Section *****
// TrafficLight.c for Lab 5
// Runs on LM4F120/TM4C123
// Implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano
// Feb 24, 2015

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

//Initialize SysTick timer
void SysTick_Init (void) {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000005;
}

//Delay
void SysTick_Wait(uint32_t count) {
	NVIC_ST_RELOAD_R = count;
	NVIC_ST_CURRENT_R = 0;
	while (!(NVIC_ST_CTRL_R & 0x00010000)){}
	}

void SysTick_Wait10ms(uint32_t delay){
	uint32_t i;
	for(i=0; i<delay; i++){
		SysTick_Wait(800000);
	}
}
int main(void){ 
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210); // activate grader and set system clock to 80 MHz
	// Initializing clock	
// Initializing clock	
	SYSCTL_RCGC2_R |= 0x32;
	int i;
	for(i=0; i<5; i ++){
	}		
	//Setting I/O
	GPIO_PORTB_DIR_R |= 0x3F;
	GPIO_PORTE_DIR_R &= 0xF8;
	GPIO_PORTF_DIR_R |= 0x0A;
	//AFSEL off
	GPIO_PORTB_AFSEL_R &= 0xE0;
	GPIO_PORTE_AFSEL_R &= 0xF8;
	GPIO_PORTF_AFSEL_R &= 0xFA;
	//DEN ON
	GPIO_PORTB_DEN_R |= 0x3F;
	GPIO_PORTE_DEN_R |= 0x07;
	GPIO_PORTF_DEN_R |= 0x0A;
	int GOS = 0;
	int WaitS = 1;
	int GOW = 2;
	int WaitW = 3;
	int GOP = 4;
	int WaitP1 = 5;
	int WaitP2 = 6;
	int WaitP3 = 7;
	int WaitP4 = 8;
	int WaitP5 = 9;
	int WaitP6 = 10;
	int WaitP7 = 11;
	int WaitP8 = 12;
	int output; 
	int output_portf1;
	int output_portf3;
	int s = GOS; 
	int input;
	uint32_t t;

struct foo{
		uint32_t Bout;
		uint32_t Fout;
		uint32_t time; 
		uint32_t Next[8];
};

	typedef const struct foo state; 
	state FSM[13] = {
		{0x21, 0x02, 200, {GOS, WaitS, GOS, WaitS, WaitS, WaitS, WaitS, WaitS}}, //GOS
		{0x22, 0x02, 100, {GOW, GOW, GOW, GOW, GOP, GOW, GOP, GOW}},							//WaitS
		{0x0C, 0x02, 200, {GOW, GOW, WaitW, WaitW, WaitW, WaitW, WaitW, WaitW}}, //GOW
		{0x14, 0x02, 100, {GOP, GOP, GOS, GOS, GOP, GOP, GOS, GOP}},							//WaitW
		{0x24, 0x08, 200, {GOP, WaitP1, WaitP1, WaitP1, GOP, WaitP1, WaitP1, WaitP1}},	//GOP
		{0x24, 0x00, 25, {WaitP2, WaitP2, WaitP2, WaitP2, WaitP2, WaitP2, WaitP2, WaitP2}},//WaitP1
		{0x24, 0x02, 25, {WaitP3, WaitP3, WaitP3, WaitP3, WaitP3, WaitP3, WaitP3, WaitP3}},//WaitP2
		{0x24, 0x00, 25, {WaitP4, WaitP4, WaitP4, WaitP4, WaitP4, WaitP4, WaitP4, WaitP4}},//WaitP3
		{0x24, 0x02, 25, {WaitP5, WaitP5, WaitP5, WaitP5, WaitP5, WaitP5, WaitP5, WaitP5}},//WaitP4
		{0x24, 0x00, 25, {WaitP6, WaitP6, WaitP6, WaitP6, WaitP6, WaitP6, WaitP6, WaitP6}},//WaitP5
		{0x24, 0x02, 25, {WaitP7, WaitP7, WaitP7, WaitP7, WaitP7, WaitP7, WaitP7, WaitP7}},//WaitP6
		{0x24, 0x00, 25, {WaitP8, WaitP8, WaitP8, WaitP8, WaitP8, WaitP8, WaitP8, WaitP8}},//WaitP7
		{0x24, 0x02, 25, {GOS, GOW, GOS, GOS, GOS, GOW, GOS, GOS}}//WaitP8
		};
  EnableInterrupts();
	SysTick_Init();
		while(1){
		//current state then output  	
		GPIO_PORTB_DATA_R = FSM[s].Bout;
		GPIO_PORTF_DATA_R = FSM[s].Fout;
	
		
		//delay
		SysTick_Wait10ms(FSM[s].time);
			
		//read inputs for next state 
		input = GPIO_PORTE_DATA_R & 0x07;
		s = FSM[s].Next[input];
		
  }
}

