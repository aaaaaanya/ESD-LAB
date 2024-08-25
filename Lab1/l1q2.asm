	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0x10001000 ;Stack pointer value wehn stack is empty
	
	DCD Reset_Handler ;reset vector
	
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R0,#0x10
	MOV R1,#2_1010
	MOV R3,#-2
	MOV R4,#3_1010
	MOV R5,0XFFFF
	LDR R6,=0XFFFF
	
STOP B STOP

NUM EQU 10
SRC DCD 8,0x123456,34567891
	END