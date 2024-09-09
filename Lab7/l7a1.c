//works
//Write a program to simulate an 8- bit ring counter with key press (SW2).
#include <LPC17xx.h>

int main()
{
	int i=0,j,x;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL4=0;
	
	LPC_GPIO0->FIODIR=0XFF<<4;
	LPC_GPIO2->FIODIR=0<<12;
	
	while(1)
	{
		x=LPC_GPIO2->FIOPIN;
		x=x&1<<12;
		
		if(x==0)
		{
			i++;
			
		}
		else
		{
			i--;
			if(i==-1)
			{i=7;}
			
		}
			LPC_GPIO0->FIOPIN=1<<((i%8)+4);
			for(j=0;j<10000000;j++);

	}	
}