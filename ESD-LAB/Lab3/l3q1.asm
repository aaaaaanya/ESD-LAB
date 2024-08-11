
;Write a program to add ten 32 bit numbers stored in code segment and store the result in data segment
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
	MOV R1,#10
	LDR R5,=SUM
	;LDR R3,=REM
LOOP	
	LDR R4,[R0],#4
	ADDS R2,R4
	ADC R3,#0
	SUBS R1,#1
	BNE LOOP
	
	STR R2,[R5],#4
	STR R3,[R5]
	

	
STOP 
	B STOP

N DCD 1,2,3,4,5,6,7,8,9,10

	AREA mydata,DATA,READWRITE
SUM DCD 0,0
;REM DCD 0
	END
