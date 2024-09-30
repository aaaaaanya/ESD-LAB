//LCD INTERFACING
#include <LPC17xx.h>

int temp1; //carries the 8 bit data/code
int temp2; //carries the 4 bit data/code to be operated on
int flag1; //0 for command,1 for data (RS)
int flag2; //0 for 8 bits,1 for bit MSB
//P0.28 for enable, P0.27 for RS
//P0.26 to P0.23 data lines(D7 to D4)
void port_write()
{
	int j;
	LPC_GPIO0->FIOPIN=temp2<<23;
	
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
	for(j=0;j<20;j++);//delay
	LPC_GPIO0->FIOCLR=1<<28;
	
	for(j=0;j<300000;j++);//delay for lcd to respond
	
}

void lcd_write()
{
	/*
	if(flag1==1)
		flag2=0;
	else if(flag1==0)
	{
		if(temp1==0x30||temp1==0x20)
			flag2=1;
		else
			flag2=0;
	}
	*/
	flag2 = (flag1 == 1) ? 0 :((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
	
	
	temp2=temp1&0xF0;
	temp2=temp2>>4;
	port_write();
	if(flag2==0)
	{
		temp2=temp1&0xF;
		port_write();
	}
}


int main()
{
	int i;
	//char s[]={'f','r','i','d','\0'};
	char s[]="crying";
	
	int lcd_init[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};
	
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL1=0;	
	//LPC_GPIO0->FIODIR=0x3F<<23;//enabling P0.23 to P0.28
LPC_GPIO0->FIODIR=3<<27 | 0xF<<23;
	//sending the command codes
	flag1=0;
	for(i=0;i<9;i++)
	{
		temp1=lcd_init[i];
		lcd_write();
	}
	
	//for the data
	flag1=1;

	
	for(i=0;s[i]!='\0';i++)
	{
		if(i==16)
		{
			flag1=0;
			temp1=0xC0;
			lcd_write();
			flag1=1;
		}
		temp1=s[i];
		lcd_write();
	}
	
	
	while(1);
	
}