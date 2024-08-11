;complete
;Write an assembly language program to find GCD of two numbers 
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
	;finding gcd
BACK
	CMP R1,R2
	BEQ EXIT
	SUBHI R1,R2
	SUBLO R2,R1
	B BACK

	
EXIT
	LDR R4,=RESULT
	STR R1,[R4]
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC,0x69,0xA666,0x227799,0x98243231,0x01
N DCD 12
M DCD 30
	AREA mydata,DATA,READWRITE
RESULT DCD 0
	END
