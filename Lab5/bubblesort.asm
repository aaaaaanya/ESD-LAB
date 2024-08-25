;Write an assembly program to do bubble sort
 	AREA RESET,DATA,READONLY
	EXPORT __Vectors
	
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	ALIGN
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R1,=N
	LDR R0,=DST
	MOV R2,R0 ;R2 HAS R0
	MOV R3,#10
	;code to data
BACK
	LDR R4,[R1],#4
	STR R4,[R2],#4
	SUBS R3,#1
	CMP R3,#0
	BNE BACK
	;R0 has start of array
	;reuse
	MOV R1,#0
	MOV R2,#0
	MOV R3,#0
	MOV R4,#0
	
	
	MOV R5,R0
	MOV R1,#10
	
OUTER
	SUB R1,#1
	CMP R1,#0
	BEQ STOP
	MOV R0,R5
	;lets make r6 have number of iterations inside
	MOV R6,R1
	
INNER	LDR R2,[R0] ;j
	LDR R3,[R0,#4] ;j+1
	CMP R2,R3
	;IF HI THEN SWAP
	;MOVHI R4,R2 ;R4 IS TEMP BUFFER
	STRHI R3,[R0]
	STRHI R2,[R0,#4]
	ADD R0,#4
	SUB R6,#1
	CMP R6,#0
	BNE INNER
	B OUTER
	
	
	
	
	
	
STOP B STOP	

N DCD 5,6,7,2,18,72,30,3,12,1

	AREA mydata,DATA,READWRITE
DST DCD 0,0,0,0,0,0,0,0,0,0
	END
