	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000;

	DCD Reset_Handler ; reset vector (; is a comment)
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	;LDR R0,=N
	;LDR R1,[R0]
	;LDR R2,=0XA1243140
	MOV R3,#5
	LDR R0,=(N+(SIZE-0*4)
	LDR R1,=(N+(SIZE-1)*4+SHIFTS*4)
BACK	LDR R2,[R0],#4; post indexing:combines LDR R2,[R0] and ADD R0,#4
	STR R2,[R1],#4;combines LDR R2,[R1] and ADD R1,#4
	
	LDR R2,[R0]
	STR R2,[R1]
	
	SUB R3,#1
	CMP R3,#0
	BNE BACK;BRANCH WHEN IT IS NOT EQUAL, BACK IS USER DEFINED LABEL
STOP
	B STOP;stops execution here, branching statement (here unconditional branching)
;data defined (stores in code memory only)	
SIZE EQU 5
SIZE EQU 2
;N DCD 0X12345678,0x6A,0X234,0X49C,0XA13BC ;In program memory here
	AREA mydata,DATA,READWRITE
N DCD 0X12345678,0x6A,0X234,0X49C,0XA13BC ; In data memory here, have to manually input
DST DCD 0,0,0,0,0

	END