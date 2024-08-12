;Write a program to add two 128 bit numbers stored in code segment and store the result in data segment.
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
	MOV R0,#4
	LDR R1,=N
	LDR R2,=M 
	LDR R5,=SUM
	ADDS R10,#0 ;to make carry flag c=0
	
	;SUM IN R3
BACK LDR R6,[R1],#4
	LDR R7,[R2],#4
	ADCS R3,R6,R7
	STR R3,[R5],#4
	SUB R0,#1
	TEQ R0,#0
	
	;using ADCS OR CMP updates carry flag c to 1
	;hence we use TEQ (Test if equal) since it doesnt touch carry flag, it performs xor operation
	BNE BACK
	ADC R4,#0
	
	STR R4,[R5]
	
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC,0x69,0xA666,0x227799,0x98243231,0x01
N DCD 1,2,3,4
M DCD 5,0xFFFFFFFF,7,8
	AREA mydata,DATA,READWRITE
SUM DCD 0,0,0
	END