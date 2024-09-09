//Write a C program to read a key and display an 8-bit up/down counter on the LEDs
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
		//upcounter
		if(x==0)
		{
			i++;
			if(i==256)
				i=0;
		}
		//downcounter
		else //i.e for x= non zero
		{
			i--;
			if(i==-1)
				i=255;
		}
		LPC_GPIO0->FIOPIN=i<<4;
		for(j=0;j<10000000;j++);
			
	
		
	}	
}