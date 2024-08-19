;Write an assembly program to search an element in an array of ten 32 bit numbers using linear search
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

	LDR R0,=KEY
	LDR R0,[R0]
	LDR R1,=N
	LDR R4,=FLAG
	MOV R6,#0 ;COUNTER
	
	
LOOP
	ADD R6,#1
	LDR R2,[R1],#4
	CMP R0,R2
	BEQ EXIT
	CMP R6,#11
	BEQ EXIT2
	B LOOP
	
	
EXIT2	MOV R3,#0
	STR R3,[R4]

	
EXIT
	MOV R3,#1
	STR R3,[R4]



STOP B STOP

N DCD 5,6,7,2,18,72,30,3,12,1
KEY DCD 30

	AREA mydata,DATA,READWRITE
FLAG DCD 0
	END