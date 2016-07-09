;****************** main.s ***************
; Program written by: Ali Ziyaan Momin, Zain Modi
; Date Created: 9/29/2015 
; Last Modified: 9/30/2015 
; Section 4-5pm WED     TA: Jenny Chen
; Lab number: 3
; Brief description of the program
;   If the switch is presses, the LED toggles at 8 Hz
; Hardware connections
;  PE0 is switch input  (1 means pressed, 0 means not pressed)
;  PE1 is LED output (1 activates external LED on protoboard) 
;Overall functionality of this system is the similar to Lab 2, with five changes:
;1-  the pin to which we connect the switch is moved to PE0, 
;2-  you will have to remove the PUR initialization because pull up is no longer needed. 
;3-  the pin to which we connect the LED is moved to PE1, 
;4-  the switch is changed from negative to positive logic, and 
;5-  you should increase the delay so it flashes about 8 Hz.
; Operation
;	1) Make PE1 an output and make PE0 an input. 
;	2) The system starts with the LED on (make PE1 =1). 
;   3) Wait about 62 ms
;   4) If the switch is pressed (PE0 is 1), then toggle the LED once, else turn the LED on. 
;   5) Steps 3 and 4 are repeated over and over


GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
TIME_DELAY				EQU   0x000F3D40

       IMPORT  TExaS_Init
       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
       EXPORT  Start
Start
 ; TExaS_Init sets bus clock at 80 MHz
    BL  TExaS_Init ; voltmeter, scope on PD3
; you initialize PE1 PE0
	BL PortE_Init					;subroutine that initializes port E
	
	LDR R1, =GPIO_PORTE_DATA_R		;turn on led via PE1
	LDR R0, [R1]
	ORR R0, R0, #0x02
	STR R0, [R1]

    CPSIE  I    ; TExaS voltmeter, scope runs on interrupts

loop  
	BL Delay						;go to delay subroutine
	
	
	LDR R1, =GPIO_PORTE_DATA_R		;the following steps compare PE0 to zero
	LDR R0, [R1]					
	AND R2, R0, #0x01				;mask data register to obtain value of PE0
	CMP R2, #0x01					;compare PE0 to zero
	BNE TON							;if not equal to zero then go to TON (turn on subroutine), this means switch is not pressed 
	
	LDR R1, =GPIO_PORTE_DATA_R		;the following steps will turn off the LED via PE1
	LDR R0, [R1]
	EOR R0, R0, #0x02				;the exclusive or will make the LED turn off since 1EOR1 = 0 
	STR R0, [R1]					;store the PE1 modification back to the data register
	B DONE

TON 								;the section toggles led via PE1 bit being flipped
	LDR R1, =GPIO_PORTE_DATA_R
	LDR R0, [R1]
	ORR R0, #0x02
	STR R0, [R1]
	
DONE
	B    loop
	
PortE_Init
	LDR R1, =SYSCTL_RCGCGPIO_R		;activate clock
	LDR R0, [R1]
	ORR R0, R0, #0x0010
	STR R0, [R1]
	
	NOP
	NOP
	NOP
	NOP								;delay to allow time for clock to activate
	
	LDR R1, =GPIO_PORTE_DIR_R		;the subroutine that turns on the led via PE0 
	LDR R0, [R1]
	ORR R0, R0, #0x02
	BIC R0, #0x01
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTE_AFSEL_R		;turn off alternate function for bits PE0 and PE1
	LDR R0, [R1]
	BIC R0, R0, #0x03
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTE_DEN_R		;digital enable on PE0 and PE1 bits 
	LDR R0, [R1]
	ORR R0, R0, #0x03
	STR R0, [R1]
	
	BX LR
	
Delay
	LDR R0, =TIME_DELAY				;move the number 200000 into R0 
Decrement
	ADD R0, R0, #-1					;decrement by 1 
	CMP R0, #0x00					;compare to 0
	BNE Decrement					;if not equal to zero keep decrementing
	BX LR





      ALIGN      ; make sure the end of this section is aligned
      END        ; end of file
       