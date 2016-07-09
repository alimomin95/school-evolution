;****************** main.s ***************
; Program written by: put your names here
; Date Created: 1/24/2015 
; Last Modified: 1/24/2015 
; Section 1-2pm     TA: Saugata Bhattacharyya
; Lab number: 2
; Brief description of the program
; The overall objective of this system is a digital lock
; Hardware connections
;  PF4 is switch input  (1 means SW1 is not pressed, 0 means SW1 is pressed)
;  PF2 is LED output (1 activates blue LED) 
; The specific operation of this system 
;    1) Make PF2 an output and make PF4 an input (enable PUR for PF4). 
;    2) The system starts with the LED ON (make PF2 =1). 
;    3) Delay for about 1 ms
;    4) If the switch is pressed (PF4 is 0), then toggle the LED once, else turn the LED ON. 
;    5) Repeat steps 3 and 4 over and over

GPIO_PORTF_DATA_R       EQU   0x400253FC
GPIO_PORTF_DIR_R        EQU   0x40025400
GPIO_PORTF_AFSEL_R      EQU   0x40025420
GPIO_PORTF_PUR_R        EQU   0x40025510
GPIO_PORTF_DEN_R        EQU   0x4002551C
GPIO_PORTF_AMSEL_R      EQU   0x40025528
GPIO_PORTF_PCTL_R       EQU   0x4002552C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608

       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
       EXPORT  Start
Start
	BL PortF_Init
	LDR R1, =GPIO_PORTF_DATA_R
	LDR R0, [R1]
	ORR R0, R0, #0x04
	STR R0, [R1]
	
loop  
	BL Delay
	
	LDR R1, =GPIO_PORTF_DATA_R
	LDR R0, [R1]
	AND R2, R0, #0x10
	CMP R2, #0x00
	BNE TON
	
	LDR R1, =GPIO_PORTF_DATA_R
	LDR R0, [R1]
	EOR R0, R0, #0x04
	STR R0, [R1]
	B DONE

TON 
	LDR R1, =GPIO_PORTF_DATA_R
	LDR R0, [R1]
	ORR R0, #0X04
	STR R0, [R1]
	
DONE
	B    loop

PortF_Init
	LDR R1, =SYSCTL_RCGCGPIO_R
	LDR R0, [R1]
	ORR R0, R0, #0x0020
	STR R0, [R1]
	
	NOP
	NOP
	NOP
	NOP
	
	LDR R1, =GPIO_PORTF_DIR_R
	LDR R0, [R1]
	ORR R0, R0, #0x04
	BIC R0, #0x10
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTF_AFSEL_R
	LDR R0, [R1]
	BIC R0, R0, #0x14
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTF_DEN_R
	LDR R0, [R1]
	ORR R0, R0, #0x14
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTF_PUR_R
	LDR R0, [R1]
	ORR R0, R0, #0x10
	STR R0, [R1]
	
	BX LR
	
Delay
	MOV R0, #0xC80
Decrement
	ADD R0, R0, #-1
	CMP R0, #0x00
	BNE Decrement
	BX LR

       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       