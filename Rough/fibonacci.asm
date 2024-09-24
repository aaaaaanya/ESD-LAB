;NOT WOKRING
;Explain the usage of the stack in a recursive function. Write an assembly language program to store
;the Fibonacci series up to "N" using recursion, where "N" is a two-digit hexadecimal number
	EXPORT __Vectors
	
__Vectors 
	DCD 0X10001000
	DCD Reset_Handler
	
	ALIGN 
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R2,=N
	LDR R2,[R2]
	LDR R6,=DST
	
	;TERMS F0 AND F1
	MOV R0,#0
	MOV R1,#1
	
	BL FIB ;USING R2 NO. OF ITERATIONS
	
	
	


N DCD 5
;FN=FN-1+FN-2
FIB 
	CMP R2,#1;R2 SHOULD BE THE N-1=1 SO N-2=0
	BEQ FIBEXIT
	
	PUSH{R0,R1,LR,R3}
	SUB R2,#1
	BL FIB
	
	SUB R2,#2
	BL FIB
	
FIBEXIT
	POP{R0,R1,LR,R3}
	STM R3,[R6],#4 ;STORING EACH TERM
	ADD R3,R0,R1
	BX LR
	

	AREA mydata,DATA,READWRITE
DST DCD 0


	END
