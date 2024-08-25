;Write a program to convert a 32 bit number in the unpacked form into packed form.
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
	MOV R2,#8
	
BACK	LDR R3,[R1],#4
	LSL R3,R4
	ADD R4,#4
	ADD R0,R3
	SUBS R2,#1
	CMP R2,#0
	BNE BACK
	
	LDR R5,=RES
	STR R0,[R5]
	
STOP B STOP	

N DCD 8,7,6,5,4,3,2,1 ;should be 0x12345678

	AREA mydata,DATA,READWRITE
RES DCD 0
	END