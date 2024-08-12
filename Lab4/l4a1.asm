;Write an ARM assembly language program to covert 2-digit hexadecimal number in ASCII unpacked form into its equivalent packed hexadecimal number

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

	LDR R4,=N
	;LDR R0,[R0]
	LDR R1,=RESULT
;for 1st digit		
	LDR R0,[R4]
	CMP R0,#0X30
	BLO LET
	CMP R0,#0X39 ;48<n<57
	BHI LET
	SUB R2,R0,#0X30 ;R2 will now have 2
	

LET 
	CMP R0,#0X41
	BLO EXIT
	CMP R0,#0X46
	BLO EXIT
	SUB R2,R0,#0X37 ;minus 55
	
	ADD R4,#4
;for 2nt digit		
	LDR R0,[R4]
	CMP R0,#0X30
	BLO LET2
	CMP R0,#0X39 ;48<n<57
	BHI LET2
	SUB R2,R0,#0X30 ;R2 will now have 2
	
	
LET2 
	CMP R0,#0X41
	BLO EXIT
	CMP R0,#0X46
	BLO EXIT
	SUB R2,R0,#0X37 ;R3 will now have D
	
	;packing
	LSL R5,R2,#4
	ADD R5,R3
	STR R5,[R1]
	
	
	




EXIT
STOP B STOP

N DCD 0x44,0x32 ; 45 in decimal
; 44=D's ASCII
;32= 2's ASCII


	AREA mydata,DATA,READWRITE
RESULT DCD 0
;ans shud be 2D
	END