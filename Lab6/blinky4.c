//blink 4 LEDs using P0.4 to P0.7

#include <lpc17xx.h>


//use Peripherals->GPIO fast interface->Port 0
int main()
{
	int i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<4|1<<5|1<<6|1<<7;
	
	//LPC_GPIO0->FIOSET=1<<4;
	
	while(1)
	{
		LPC_GPIO0->FIOSET=1<<4|1<<5|1<<6|1<<7;
		for(i=0;i<10000;i++);
		LPC_GPIO0->FIOCLR=1<<4|1<<5|1<<6|1<<7;
		for(i=0;i<10000;i++);
	}
	
}