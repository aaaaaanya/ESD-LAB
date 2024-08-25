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

	MOV R3,#10
	LDR R0,=N
	LDR R1,=RESULT
	MOV R4,R1
	

;code to data memory
BACK
	LDR R2,[R0],#4
	STR R2,[R1],#4
	SUB R3,#1
	CMP R3,#0
	BNE BACK
	
;R4 has address of 1st element in data memory
; can reuse R0,R1,R2,R3
;R3 BECAME 0
;MAKE REST 0 TO REUSE
	MOV R0,#0
	MOV R1,#0
	MOV R2,#0

OUTER
	
	
	LDR R0,[R4]
	MOV R2,R0 ;r2 will hold initial value
	MOV R10,R4 ;r10 will hold initial address
	ADD R4,#4 ;to increment
	
	ADD R3,#1 ;R3 HAS COUNT FOR ITERATIONS
	
	CMP R3,#10
	BEQ STOP
	
	RSB R5,R3,#10 ;no. of elements to compare to
	MOV R6,#0 
	MOV R7,#0 ;WILL HOLD ADDRESS OF MIN ELEMENT
	
INNER	
	LDR R1,[R4,R6] ;R1 WILL HAVE THE ELEMENTS TO COMPARE
	ADD R6,#4 ;ADD+4 AFTER EVERY ADDRESS
	CMP R0,R1
	MOVHI R0,R1 ;MOVE R1 ELEMENT INTO R0 IF R0>R1
	ADDHI R7,R10,R6 ; TO GET ADDRESS OF MIN ELEMENT
	SUB R5,#1
	CMP R5,#0
	
	;IF MINIMUM IS FOUND WE HAVE TO SWAP MIN ELEMENT R0(AT R7=R10+R6) ADDRESS AND INITIAL ELEMENT R8  (AT R2)
	MOVEQ R9,R0 ;R9 ACTS AS TEMP AND STORES THE MIN VALUE 
	MOVEQ R8,R2 ;gets initial element
	
	STREQ R8,[R7] ;moveinitial element to min element place
	STREQ R9,[R10] ;move min element to initial element wala place
	
	BEQ OUTER
	B INNER
	
	
	
STOP B STOP


N DCD 5,6,7,2,18,72,30,3,12,1

	AREA mydata,DATA,READWRITE
RESULT DCD 0,0,0,0,0,0,0,0,0,0
	END