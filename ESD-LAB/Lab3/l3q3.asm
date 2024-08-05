;Write a program to subtract two 128 bit numbers
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
	CMP R10,#0;to make carry flag c=1
	
	;SUM IN R3
BACK LDR R6,[R1],#4
	LDR R7,[R2],#4
	SBCS R3,R6,R7
	STR R3,[R5],#4
	SUB R0,#1
	TEQ R0,#0
	
	;using ADCS OR CMP updates carry flag c to 1
	;hence we use TEQ (Test if equal) since it doesnt touch carry flag, it performs xor operation
	BNE BACK

	
	
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,
N DCD 5,6,7,0XA
M DCD 1,8,3,4

	AREA mydata,DATA,READWRITE
SUM DCD 0,0,0
	END