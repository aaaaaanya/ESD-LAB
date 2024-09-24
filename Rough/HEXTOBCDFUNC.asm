;2dig BCD->HEX
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
	LDR R1,[R1]
	BL BCDTOHEX
	
	LDR R5,=DST
	STR R4,[R5]
	
	
	
	
	
	



BCDTOHEX
	;CONSIDER R1 HAS 25
	AND R2,R1,#0XF ;TO GET 5
	LSR R3,R1,#4 ; TO GET 2
	MOV R0,#10
	
	MLA R4,R3,R0,R2
	;R4 WILL STORE THE HEX VALUE
	BX LR
	
	

N DCD 0x25

	AREA mydata,DATA,READWRITE
DST DCD 0

	END