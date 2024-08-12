
;3)Write an assembly language program to copy data from one memory block to another when the memory blocks are overlapping
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
	LDR R0,=(N+(SIZE-1)*4) ;will point to the last number in the register
	LDR R1,=(N+(SIZE-1)*4+SHIFTS*4);will point to the last no. + 2 blocks after that
BACK
	LDR R2,[R0],#-4
	STR R2,[R1],#-4
	SUB R3,#1 ;Subtracts the value of R3 by a by value of 1
	CMP R3,#0 ;Keeps comparing the value of R3 with 0
	BNE BACK ;BNE--> Branch when Not equal, so it breaks if R3 becomes equal to 0,as long as not equal it keeps looping
	
	
STOP 
	B STOP

SIZE EQU 5
SHIFTS EQU 2

	AREA mydata, DATA, READWRITE
N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC`

	END