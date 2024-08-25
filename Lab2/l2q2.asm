;Reverse an array of ten 32 bit numbers in the memory.

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
	MOV R3,#10
	LDR R0,=(N+(SIZE-1)*4) ;will point to the last number in the register
	LDR R1,=(N+(SIZE-1)*4+SHIFTS*4);will point to the last no. + 2 blocks after that
BACK
	LDR R2,[R0],#-4
	STR R2,[R1],#4
	SUB R3,#1 ;Subtracts the value of R3 by a by value of 1
	CMP R3,#0 ;Keeps comparing the value of R3 with 0
	BNE BACK ;BNE--> Branch when Not equal, so it breaks if R3 becomes equal to 0,as long as not equal it keeps looping
	
	
STOP 
	B STOP

SIZE EQU 10
SHIFTS EQU 1

	AREA mydata, DATA, READWRITE
N DCD 1,2,3,4,5,6,7,8,9,10
	END