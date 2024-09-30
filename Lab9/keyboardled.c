


#include <LPC17xx.h>

int main()
{
	int seven_seg[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0x77,0x7c,0x39,0x5E,0x79,0x71};
	int row,col,i,j,x,keycode;
	//4r+c
	SystemInit();
	SystemCoreClockUpdate();
	//P1.23 TO P1.26 for columns
	//P2.10 to P2.13 for rows
	//P0.4 TO P0.11 for led
	//P0.15 TO P0.18 for decoder
	
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL1=0;
	LPC_PINCON->PINSEL3=0;
	LPC_PINCON->PINSEL4=0;
	
	LPC_GPIO0->FIODIR=0xFF<<4|0XF<<15;
	LPC_GPIO1->FIODIR=0<<23;
	LPC_GPIO2->FIODIR=0XF<<10;
while(1)	
{
	for(row=0;row<4;row++)
	{
		LPC_GPIO2->FIOPIN=1<<(10+row);
		for(j=0;j<1000;j++);
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
		keycode=4*row+col;
		LPC_GPIO0->FIOMASK=0xFFFFF00F;
		LPC_GPIO0->FIOPIN=seven_seg[keycode]<<4;
		
	}
}
	
}