;works
;Write an ARM assembly language program to covert 2-digit hexadecimal number in ASCII

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

	LDR R0,=N
	LDR R0,[R0]
	LDR R1,=RESULT
	
	LSR R2,R0,#4 ;to get 2
	AND R3,R0,#0xF ; to get D
	
	CMP R2,#0XA ;for the 2 digit
	ADDLO R2,#0X30 ;48(in decimal)=30(in hex)
	ADDHS R2,#0X37; 55(in decimal)=37
	
	CMP R3,#0XA; for the D digit
	ADDLO R3,#0X30
	ADDHS R3,#0X37
	
	LSL R4,R2,#8 ; packing of digits into R4
	ADD R4,R3
	
	STR R4,[R1]
	
	
	





STOP B STOP

N DCD 0x2D ; 45 in decimal

	AREA mydata,DATA,READWRITE
RESULT DCD 0
	END