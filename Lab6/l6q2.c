//not sure if working
//Write an embedded C program to turn ON the LED when the switch connected to P2.12 is pressed and turn OFF the LED when the switch is released.

#include <lpc17xx.h>


//use Peripherals->GPIO fast interface->Port 0
int main()
{
	int x,i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0; //P0.4
	LPC_PINCON->PINSEL4=0; //P2.12
	
	LPC_GPIO0->FIODIR=1<<4; //FOR LED
	LPC_GPIO2->FIODIR=0<<12;//FOR SWITCH
	
	x=LPC_GPIO2->FIOPIN;
	x=x&1<<12;
	
	
	while(1)
	{
		if(x==0)
		{
			LPC_GPIO0->FIOSET=1<<4;
		//for(i=0;i<10000;i++);
		}
		else
		{
			LPC_GPIO0->FIOCLR=1<<4;
		}
		
	}
	
}