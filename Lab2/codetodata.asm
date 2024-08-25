;1)Write an assembly language program to copy an array of two 32-bit numbers from code memory to data memory
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
	;LDR R0,=N
	;LDR R1,[R0]
	;LDR R2,=0xA1243140

    ;Copying an array of values from one variable to another,Q1
	;LDR R0,=N
	;LDR R1,=DST
	;LDR R2,[R0]
	;STR R2,[R1]
	;ADD R0,#0x00000004
	;ADD R1,#0x00000004
	;LDR R2, [R0]
	;STR R2,[R1]
	
	;Copying an array of values from one variable to another,Q1, 2nd method
	;LDR R0,=N
	;LDR R1,=DST
	;LDR R2,[R0],#4
	;STR R2,[R1],#4
	;LDR R2, [R0]
	;STR R2,[R1]
	
	;Copying an array of values from one variable to another,Q1, 3rd method using loop
	MOV R3,#5
	LDR R0,=N
	LDR R1,=DST
BACK
	LDR R2,[R0],#4
	STR R2,[R1],#4
	SUB R3,#1 ;Subtracts the value of R3 by a by value of 1
	CMP R3,#0 ;Keeps comparing the value of R3 with 0
	BNE BACK ;BNE--> Branch when Not equal, so it breaks if R3 becomes equal to 0,as long as not equal it keeps looping, the loop breaks when Z flag becomes 1 from 0, the Z flag can be seen under xPSR
	;BEQ--> Branch when equal
	
STOP 
	B STOP

N DCD 0x12345678,0x6A,0x234,0x49C,0xA13BC

	AREA mydata, DATA, READWRITE
DST DCD 0,0,0,0,0 ;Remember to allocate enough space to reserve the memory, if not allocated properly values may be overwritten 

	END