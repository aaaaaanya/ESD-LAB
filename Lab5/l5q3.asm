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
	LDR R0,=N
	LDR R2,=KEY
	LDR R5,=RESULT
	LDR R2,[R2]
	MOV R3,#-1 ;R3(pos)=-1 if not found
	MOV R4,#0
	
BACK	LDR R1,[R0],#4
	CMP R1,R2
	BEQ FOUND
	ADD R4,#1
	CMP R4,#10
	BNE BACK
	B NOTFOUND

	
FOUND
	MOV R3,R4
	STR R3,[R5]
	B STOP
	
NOTFOUND
	STR R3,[R5]
	
STOP B STOP	

N DCD 5,6,7,2,18,72,30,3,12,1
KEY DCD 18

	AREA mydata,DATA,READWRITE
RESULT DCD 0,0,0,0,0,0,0,0,0,0
	END
	
	
	
	
	
	
	
	
	
	
	
	