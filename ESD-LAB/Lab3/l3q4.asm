;complete
;Write an assembly language program to find LCM of two numbers 
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
	LDR R1,[R1] ;12
	LDR R2,[R2] ;30
	MOV R0,#1 ;i
	;finding lcm


 
LOOP	MUL R3,R1,R0 
	MOV R5,R3
L2	CMP R5,R2 ;division to get remainder
	BLO EXIT2
	SUB R5,R2
	B L2
	;R3 now has remainder
EXIT2	CMP R5,#0
	BEQ EXIT
	ADDNE R0,#1
	B LOOP
	

	
EXIT
	MUL R3,R1,R0
	LDR R4,=RESULT
	STR R3,[R4]
	
STOP 
	B STOP

;N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC,0x69,0xA666,0x227799,0x98243231,0x01
N DCD 12
M DCD 30
	AREA mydata,DATA,READWRITE
RESULT DCD 0
	END
