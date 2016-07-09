#include <stdint.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Lab8.c"

//initialize PE1 and PE0 for UART7
void UART_Init(void){
	SYSCTL_RCGCUART_R |= 0x0080; //Activate UART7
	SYSCTL_RCGCGPIO_R |= 0x0010;	//Activate Port E
	UART7_CTL_R &= ~0x0001;
	UART7_IBRD_R = 31; //IBRD = int(50000000/(16*100,000) = int(31.25)
	UART7_FBRD_R = 16;  //FBRD round(0.25 * 64) = 16
	UART7_LCRH_R = 0x0070;  //8-bit world length, enable FIFO 
	UART7_CTL_R = 0x0301; //enable RXE, TXE, and UART
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTE_AMSEL_R &= ~0x03; //disable analog function on PE1-0
	GPIO_PORTE_AFSEL_R |= 0x03; //enable alt funct on PE1-PE0
	GPIO_PORTE_DEN_R |= 0x03; //enable digital I/O on PE1-PE0
}
//wait for new input, then return ASCII code
char UART_InChar(void){
	while((UART7_FR_R&0x0010) != 0); //wait until RXFE is 0 
	return((char) (UART7_DR_R&0xFF));
}

//Wait for buffer to be not full, then output
void UART_OutChar(char data){
	while((UART7_FR_R&0x0020) !=0); //wait until TXFF is 0
	UART7_DR_R = data;
}
int con; 
void Send_Data(void){
	GPIO_PORTF_DATA_R ^= 0x04;
	data = AVeraG();
	GPIO_PORTF_DATA_R ^= 0x04;
	con = Convert(data);
	
}





