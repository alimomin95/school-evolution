; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 
GPIO_PORTF_DATA_R  EQU 0x400253FC
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
	PRESERVE8 
  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH{R4-R11, LR}
cnt RN 6
d 	RN 5
n	RN 4 
cnte EQU 0x0000
	MOV n, R0 
	CMP n , #0
	BEQ zer
	BHI mods
Ret1 
	CMP n, #0 
	BHI mods
Ret3 
	CMP cnt, #0 
	BEQ Ret2
	POP {R0}
	BL ST7735_OutChar
	SUB cnt, cnt, #1
	B Ret3
Ret2
	POP{R4-R11, LR}
	BX LR 
mods 
	MOV R3, #10 
	UDIV R2, n, R3     
	MLS  d, R3, R2, n
	ADD d, d, #0x30
	PUSH{d}
	ADD cnt, cnt, #1
	UDIV n, n, R3
	LDR R0, =cnte
	STR cnt, [R0]
	B Ret1
zer
	MOV R0, #0x30
	BL ST7735_OutChar
	B Ret2

;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
fix RN 4
t	RN 5
	PUSH {R4-R11, LR}
	MOV fix, R0
	MOV R7, #9999
	CMP fix, R7
	BHI stars
	
	MOV R3, #1000
	UDIV t, fix, R3
	ADD t, t, #0x30
	MOV R0, t
	BL ST7735_OutChar
	MOV R0, #0x2E
	BL ST7735_OutChar
	MOV R3, #1000 
	UDIV R2, fix, R3     
	MLS  fix, R3, R2, fix
	
	MOV R3, #100
	UDIV t, fix, R3
	ADD t, t, #0x30
	MOV R0, t
	BL ST7735_OutChar
	MOV R3, #100 
	UDIV R2, fix, R3     
	MLS  fix, R3, R2, fix
	
	MOV R3, #10
	UDIV t, fix, R3
	ADD t, t, #0x30
	MOV R0, t
	BL ST7735_OutChar
	MOV R3, #10 
	UDIV R2, fix, R3     
	MLS  fix, R3, R2, fix
	
	ADD fix, fix, #0x30
	MOV R0, fix
	BL ST7735_OutChar
	MOV R0, #0x20
	BL ST7735_OutChar
	MOV R0, #0x63
	BL ST7735_OutChar
	MOV R0, #0x6D
	BL ST7735_OutChar
	B FOO
stars
	MOV R0, #0x2A
	BL ST7735_OutChar
	MOV R0, #0x2E
	BL ST7735_OutChar
	MOV R0, #0x2A
	BL ST7735_OutChar
	MOV R0, #0x2A
	BL ST7735_OutChar
	MOV R0, #0x2A
	BL ST7735_OutChar
FOO	
	POP {R4-R11, LR}
     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
