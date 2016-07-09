;****************** main.s ***************
; Program written by: Ali Ziyaan Momin, Zain Modi
; Date Created: 9/8/2015 
; Last Modified: 9/8/2015 
; Section 4-5pm WED     TA: Jenny Chen
; Lab number: 1
; Brief description of the program
; The overall objective of this system is a digital lock
; Hardware connections
;  PE3 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
;  PE4 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
;  PE2 is LED output (0 means door is locked, 1 means door is unlocked) 
; The specific operation of this system is to 
;   unlock if both switches are pressed

GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608

      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      EXPORT  Start
Start
	BL PortE_Init				;initialize port E input outputs
loop
	LDR R1, =GPIO_PORTE_DATA_R	; Load address for Port E data register
	LDR R0, [R1]				; Load contents of Port E data register
	AND R2, R0, #0x10			; Mask PE4 and put in R2
	AND R3, R0, #0x08			; Mask PE3 and put in R3
	ASR R2, #2					; Shift right PE4 2 places
	ASR R3, #1					; Shift right PE3 1 place
	EOR R2, R2, #0xFF			; NOT PE4
	EOR R3, R3, #0xFF			; NOT PE3
	AND R2, R2, R3				; AND values of PE4 and PE3
	STR R2, [R1]				; Put the result back into the Port E data register
	  B   loop
PortE_Init
	LDR R1, =SYSCTL_RCGCGPIO_R	; 1) Activate clock for Port E
	LDR R0, [R1]
	ORR R0, R0, #0x0010			; Set bit 4 to turn on the clock
	STR R0, [R1]
	
	NOP							 
	NOP							;allow time for clock to finish
	
	LDR R1, =GPIO_PORTE_DIR_R	; 2) Set direction register
	MOV R0, #0x04				; PE4 and PE3 are 0 for inputs and PE2 is 1 for output
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTE_AFSEL_R	; 3) Regular port function
	MOV R0, #0x00				; 0 means alternate function disabled
	STR R0, [R1]
	
	LDR R1, =GPIO_PORTE_DEN_R	; 4) Enable Port E digital port
	MOV R0, #0xFF				; 1 means enable digital I/O
	STR R0, [R1]
	
	BX LR

      ALIGN        ; make sure the end of this section is aligned
      END          ; end of file