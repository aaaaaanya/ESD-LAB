//Write a C program to display 8-bit binary up counter on the LEDs.
#include <LPC17xx.h>

int main()
{
	int i,j;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=0XFF<<4;
	
	while(1)
	{
		for (i=0;i<=255;i++)
		{
			LPC_GPIO0->FIOPIN=i<<4;
			for(j=0;j<10000000;j++);
			
		}		
	}	
}