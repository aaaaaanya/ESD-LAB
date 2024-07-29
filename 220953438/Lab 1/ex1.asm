	AREA RESET,DATA,READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000;

	DCD Reset_Handler; reset vector (; is a comment)
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R0,#0X123
	MOV R1,#0123
	ADD R2,#33
	ADD R2,R1
	LDR R4,=0X22222222
	
STOP
	B STOP ;stops execution here, branching statement (here unconditional branching)
;data defined (stores in code memory only)	
NUM EQU 10
SRC DCD 8,0X123456,34567891
	END