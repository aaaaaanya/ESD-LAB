;Find the sum of �n� natural numbers using MLA instruction

	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY 
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,=N
	LDR R0,[R0]
	LDR R1,=SUM
	;Lets say R2 stores sum in code memory
	MLA R2,R0,R0,R0
	LSR R2,#1
	
	STR R2,[R1]
	
	
N DCD 5
	AREA mydata,DATA,READWRITE
SUM DCD 0; ans shud be 15
	END