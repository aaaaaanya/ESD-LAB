#include <LPC17xx.h>
#include <stdio.h>

int seven_seg[]={0x3F,0x06,0x5b,0x4f,0x66,0x60,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int flag1,flag2,temp1,temp2;
int key_input[4]; // To store the inputs A, operator, B, and '='
int idx = 0; // Index for the key input array

// Function to write to the port for LCD
void port_write()
{
	int i;
	LPC_GPIO0->FIOPIN=temp2<<23;
	if(flag1==0)
		LPC_GPIO0->FIOCLR=1<<27;
	else
		LPC_GPIO0->FIOSET=1<<27;
	LPC_GPIO0->FIOSET=1<<28;
	for(i=0;i<20;i++);
	LPC_GPIO0->FIOCLR=1<<28;
	for(i=0;i<300000;i++);
}

// Function to write to the LCD
void LCD_Write()
{
	flag2 = (flag1 == 1) ? 0 :((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
	temp2=(temp1&0xF0)>>4;
	port_write();
	if(flag2==0)
	{
		temp2=temp1&0xf;
		port_write();
	}
}

// Function to initialize the LCD
void LCD_Init()
{
	int LCD_init[]={0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
	int i;
	flag1 = 0;
	for(i=0; i<=8; i++)
	{
		temp1 = LCD_init[i];
		LCD_Write();
	}
	flag1 = 1;
}

// Function to display a string on the LCD
void LCD_Display(char *s)
{
	int i;
	for(i=0; s[i]!='\0'; i++)
	{
		if(i == 16) // Move to second line after 16 characters
		{
			flag1 = 0;
			temp1 = 0xc0; // Set cursor to the beginning of the second line
			LCD_Write();
			flag1 = 1;
		}
		temp1 = s[i];
		LCD_Write();
	}
}

// Function to handle keypad input
int get_keypad_input()
{
	int i, j, x, col, row, key = -1;
	while(key == -1)
	{
		for(i=0; i<4; i++)
		{
			LPC_GPIO2->FIOPIN = 1 << (10 + i);
			x = LPC_GPIO1->FIOPIN;
			for(j=0; j<50; j++); // Small delay
			x = (x >> 23) & 0xf;
			if(x != 0)
			{
				if(x == 1) col = 0;
				else if(x == 2) col = 1;
				else if(x == 4) col = 2;
				else if(x == 8) col = 3;
				row = i;
				key = 4*row + col;
				break;
			}
		}
	}
	return key;
}

// Function to display the expression
void LCD_Display_Expression(int A, char operator, int B)
{
	char expression[20];
	sprintf(expression, "%d %c %d =", A, operator, B);
	LCD_Display(expression);
}

int main()
{
	int A,B,result;
	char operator,result_str[5];
	SystemInit();
	SystemCoreClockUpdate();

	// LCD initialization
	

	// Set GPIO directions for keypad and LCD
	LPC_PINCON->PINSEL0 = 0;
	LPC_PINCON->PINSEL1 = 0;
	LPC_PINCON->PINSEL3 = 0;
	LPC_PINCON->PINSEL4 = 0;
	LPC_GPIO0->FIODIR = 0XFF<<4 | 0XF<<15;  // P0.11 TO P0.4->SEVEN SEG P0.18 TO P0.15->DECODER
	LPC_GPIO1->FIODIR = 0;   // P1.26 TO P1.23->COLS
	LPC_GPIO2->FIODIR = 0XF<<10;  // P2.13 TO P2.10->ROWS

	LPC_GPIO0->FIOPIN = 0;
	LCD_Init();

	// Get inputs A, operator, B, and '='
	for(idx = 0; idx < 4; idx++)
	{
		key_input[idx] = get_keypad_input();
	}

	A = key_input[0];
	B = key_input[2];
	operator = (key_input[1] == 10) ? '+' : '-'; // Assuming key 10 is '+', and key 11 is '-'

	if(operator == '+')
		result = A + B;
	else
		result = A - B;

	// Display the expression on the LCD
	LCD_Display_Expression(A, operator, B);
	
	// Convert result to string for display on LCD
	sprintf(result_str, "%d", result);
	LCD_Display(result_str);

	while(1); // Infinite loop
}
