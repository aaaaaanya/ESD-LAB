; Write a program to multiply two 32 bit numbers using repetitive addition
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
	LDR R1,[R1]
	LDR R2,[R2]
	
BACK	ADDS R3,R3,R1
	ADCS R4,#0
	SUB R2,#1
	CMP R2,#0
	BNE BACK
	
	LDR R5,=RES
	STR R3,[R5],#4
	STR R4,[R5]
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC,0x69,0xA666,0x227799,0x98243231,0x01
N DCD 12
M DCD 3
	AREA mydata,DATA,READWRITE
RES DCD 0,0
	END
