;Factorial Recursion Program
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
	LDR R0,[R0]
	MOV R2,#1
	BL FACTORIAL

	LDR R3,=FACT
	STR R2,[R3]


STOP B STOP

FACTORIAL
	CMP R0,#1
	BEQ EXIT
	PUSH{R0,LR}
	SUB R0,#1
	BL FACTORIAL
	
EXIT
	POP{R1,LR}
	MUL R2,R1
	BX LR
	

N DCD 5 

	AREA mydata,DATA,READWRITE
FACT DCD 0

	END