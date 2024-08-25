;Write an assembly program to sort an array using selection sort
	AREA RESET, DATA, READONLY
	EXPORT __Vectors
	EXPORT Reset_Handler
	
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	
	
Reset_Handler

	LDR R10,=N
	LDR R0,=RESULT
	MOV R4,#10
	MOV R12,R0
	
	
	
	
;CODE TO DATA

BACK
	LDR R2,[R10],#4
	STR R2,[R12],#4
	SUB R4,#1
	CMP R4,#0
	BNE BACK
	
	MOV R12,#0
	


	
OUTER
	
	LDR R2,[R0],#4 ;OUTER LOOP
	ADD R4,#1
	RSB R5,R4,#10
	MOV R6,#0
	;MOV R6,#4
	
INNER
	
	
	LDR R3,[R0,R6]
	ADD R6,#4
	CMP R2,R3
	MOVHI R2,R3
	SUB R5,#1
	CMP R5,#0
	;STREQ R3,[R1],#4 ;here we gotta swap
	SUB R12,R0,#4
	MOVEQ R7,R12 ;R7 WILL HAVE ADDRESS OF INITIAL ELEMENT
	ADDEQ R8,R12,R6 ;R8 HAS ADDRESS OF SMALLEST ELEMENT
	
	LDREQ R11,[R7]
	STREQ R2,[R7]
	STREQ R11,[R8]
	;MOVEQ R9,R7
	;MOVEQ R7,R8
	;MOVEQ R8,R9
	
	BEQ OUTER
	B INNER
	
	



N DCD 5,6,7,2,18,72,30,3,12,1

	AREA mydata,DATA,READWRITE
RESULT DCD 0,0,0,0,0,0,0,0,0,0
	END