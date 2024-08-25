;Write a program to subtract two 32 bit numbers

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
	LDR R1,=N
	LDR R2,=M
	LDR R0,=REM
	LDR R1,[R1]
	LDR R2,[R2]
	
	SUB R3,R1,R2
	
	STR R3,[R0]
	
	

	
STOP 
	B STOP

N DCD 5
M DCD 8

	AREA mydata,DATA,READWRITE

REM DCD 0
	END