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
	LDR R0,=N
	
	LDR R1,[R0],#4 ;to get D
	CMP R1,#0X39 ;57 IN HEX ;
	SUBLS R1,#0X30 ;if 48<n<57  (from 0 to 9)
	SUBHI R1,#0X37; if 65<n<70 (from A to F)
	
	LDR R2,[R0] ;to get 2
	CMP R2,#0X39
	SUBLS R2,#0X30
	SUBHI R2,#0X37
	
	
	LSL R3,R2,#4
	ADD R3,R1
	LDR R4,=RES
	STR R3,[R4]
	
	
	
	
STOP B STOP	

N DCD 0X44,0x32 ;(for 2D=45)

	AREA mydata,DATA,READWRITE
RES DCD 0
	END