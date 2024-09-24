;Write an assembly language program to convert a 4-digit BCD number available in the code memory into hexadecimal, 
;using a function which converts a 2-digit BCD number into hexadecimal. Store the result in the data memory.
;4dig BCD->HEX
	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors 
	DCD 0X10001000
	DCD Reset_Handler
	
	ALIGN 
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	;commit all function stuff on r1
	
	LDR R5,=N
	LDR R5,[R5]
	LDR R6,=DST
	
	AND R1,R5,0XFF
	BL BCDTOHEX
	;R4 WILL HAVE THE LOWER KA HEX VAL
	MOV R7,R4
	
	LSR R1,R5,#8
	BL BCDTOHEX
	
	;RESULT IN R4
	;100 TO MULTIPLY
	MOV R8,#100
	MLA R9,R8,R4,R7
	
	STR R9,[R6]
	
	
STOP B STOP	
	
	
	
	
	
	



BCDTOHEX
	;CONSIDER R1 HAS 25
	AND R2,R1,#0XF ;TO GET 5
	LSR R3,R1,#4 ; TO GET 2
	MOV R0,#10
	
	MLA R4,R3,R0,R2
	;R4 WILL STORE THE HEX VALUE
	BX LR
	
	

N DCD 0x1492

	AREA mydata,DATA,READWRITE
DST DCD 0

	END
