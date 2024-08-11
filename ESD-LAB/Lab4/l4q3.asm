
;Write an assembly language program to convert a 2-digit BCD number in to its equivalent hexadecimal number.

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

	LDR R0,=N
	LDR R0,[R0]
	LDR R1,=RESULT
	MOV R2,#0xA
	
	LSR R3,R0,#4 ;shifting to right by 4 bits to obtain 1st digit R3=1st digit
	AND R4,R0,#0xF ;ANDING with 1111 to obtain 2nd digit R4=2nd digit
	
	MLA R5,R3,R2,R4
	STR R5,[R1]
	
	
	





STOP B STOP

N DCD 0x15

	AREA mydata,DATA,READWRITE
RESULT DCD 0
	END