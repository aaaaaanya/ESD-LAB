;Write an assembly program to find the factorial of a unsigned number using recursion
	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	EXPORT Reset_Handler
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	
	
Reset_Handler
	LDR R1, =N
	LDR R1, [R1]
	BL FACT

	
	LDR R0, =RESULT
	STR R1, [R0]

STOP
	B STOP

N DCD 5

FACT
	CMP R1,#1
	BEQ EXIT
	PUSH {R1,LR} 
	SUB R1,#1
	BL FACT
	
EXIT
	POP {R2,LR}
	MUL R1,R2
	BX LR



	AREA mydata,DATA,READWRITE
RESULT DCD 0
	END