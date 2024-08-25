	;Write a program for BCD multiplication (this is for 2 digit)
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
	LDR R1,=N
	LDR R2,=M
	LDR R1,[R1]
	LDR R2,[R2]
	
	AND R3,R1,#0XF ;R3=5
	LSL R4,R1,#4 ;R4=1
	
	AND R5,R2,#0XF ;R5=0
	LSL R6,R2,#4 ;R6=2
	
	


N DCD 0X15
M DCD 0X20

	AREA mydata,CODE,READWRITE
	
RES DCD 0
	END
