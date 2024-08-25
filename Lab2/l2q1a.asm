;3)Write an assembly language program to copy data from one memory block to another when the memory blocks are non-overlapping
	AREA RESET, DATA, READONLY 
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R3,#5
	LDR R0,=N
	LDR R1,=(N+SIZE*4+SHIFTS*4)
BACK
	LDR R2,[R0],#4
	STR R2,[R1],#4
	SUB R3,#1
	CMP R3,#0
	BNE BACK
	
STOP 
	B STOP

SIZE EQU 5
SHIFTS EQU 2

	AREA mydata, DATA, READWRITE
N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC

	END