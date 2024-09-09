//blink LED

#include <lpc17xx.h>


//use Peripherals->GPIO fast interface->Port 0
int main()
{
	int i;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<4;
	
	//LPC_GPIO0->FIOSET=1<<4;
	
	while(1)
	{
		LPC_GPIO0->FIOSET=1<<4;
		for(i=0;i<10000000;i++);//10^7 delay for hardware
		LPC_GPIO0->FIOCLR=1<<4;
		for(i=0;i<10000000;i++);
	}
	
}