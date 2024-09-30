

#include <LPC17xx.h>
int j,i,k;
int temp1=0; //carries the 8 bit data/code
int temp2=0; //carries the 4 bit data/code to be operated on
int flag1=0; //0 for command,1 for data (RS)
int flag2=0; //0 for 8 bits,1 for bit MSB
//P0.28 for enable, P0.27 for RS
//P0.26 to P0.23 data lines(D7 to D4)

void intToStr(int N, char *str) {
	int sign;
    i=0; 
	sign = N;// Save the copy of the number for sign
 // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) {  
        str[i++] = N % 10 + '0';//Convert integer digit to character and store it in the str
      	N /= 10;
    } 

    
    if (sign < 0) {
        str[i++] = 'F';// If the number was negative, add a minus sign to the string
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    for (j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void port_write()
{
	LPC_GPIO0->FIODIR=temp2<<23;
	
	if(flag1==0)
	{
		LPC_GPIO0->FIOCLR=1<<27;
	}
	else
	{
		LPC_GPIO0->FIOSET=1<<27;
	}
	//enable LCD
	LPC_GPIO0->FIOSET=1<<28;
	for(j=0;j<10000;j++);//delay
	LPC_GPIO0->FIOCLR=1<<28;
	
	for(j=0;j<200000;j++);//delay for lcd to respond
	
}

void lcd_write()
{
	if(flag1==1)
		flag2=0;
	else if(flag1==0)
	{
		if(temp1==0x30||temp1==0x20)
			flag2=1;
		else
			flag2=0;
	}
	
	
	
	temp2=temp1&0xF0;
	port_write();
	if(flag2==0)
	{
		temp2=temp1&0xF;
		port_write();
	}
}


int main()
{	
	int lcd_init[]={0x30,0x30,0x30,0x20,0x28,0x01,0x06,0x0C,0x80};
	int keycode[3];
	int row,col,i,j,k=0,x,result;
	char result_str[3];
	//4r+c
	SystemInit();
	SystemCoreClockUpdate();
	//P1.23 TO P1.26 for columns
	//P2.10 to P2.13 for rows
//P0.28 for enable,P0.27 for RS
//P0.26 to P0.23 data lines(D7 to D4)
	
	LPC_PINCON->PINSEL1=0;
	LPC_PINCON->PINSEL3=0;
	LPC_PINCON->PINSEL4=0;
	
	LPC_GPIO0->FIODIR=0x3F<<23;//0x3f enabling P0.23 to P0.28
	LPC_GPIO1->FIODIR=0<<23;//columns
	LPC_GPIO2->FIODIR=0XF<<10;//rows
for(k=0;k<3;k++)	
{	for(row=0;row<4;row++)
	{
		LPC_GPIO2->FIOPIN=1<<(10+row);
		for(j=0;j<10000;j++);
		x=LPC_GPIO1->FIOPIN;
		x=(x>>23)&0xF;
		
		if(x==0)
		{
			continue;
		}
		else if(x==8)
		{
			col=3;
		}
		else if(x==4)
		{
			col=2;
		}
		else if(x==2)
		{
			col=1;
		}
		else if(x==1)
		{
			col=0;
		}
		break;
	}
	
	if(x!=0)
	{
		keycode[k]=4*row+col;
		
	}
}
//keycode[2] is operator A is +,F is -
	switch(keycode[1])
{
	case 10:
		result=keycode[0]+keycode[2];
	break;
	case 15:
		result=keycode[0]-keycode[2];
	break;
}

intToStr(result,result_str);

	//sending the command codes
	flag1=0;
	for(i=0;i<9;i++)
	{
		temp1=lcd_init[i];
		lcd_write();
	}
	
	//for the data
	for(i=0;result_str[i]!='\0';i++)
	{
		if(i==16)
		{
			flag1=0;
			temp1=0xC0;
			lcd_write();
			flag1=1;
		}
		temp1=result_str[i];
		lcd_write();
	}


	
}
