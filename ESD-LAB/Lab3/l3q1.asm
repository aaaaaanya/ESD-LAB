;incomplete
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

MOV R0,#1 ;i
LDR R1,=N
LDR R2,=M
CMP [R1],[R2]
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC,0x69,0xA666,0x227799,0x98243231,0x01
N DCD 12
M DCD 30
	AREA mydata,DATA,READWRITE
LCM DCD 0
	END