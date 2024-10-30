//Toggle LED connected to P0.3 every 0.5s.i.e generate square wave with period 2 seconds

#include <lpc17xx.h>
float x;
void timer_delay();

int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=1<<3;
	x=0.5;
	while(1)
	{
		LPC_GPIO0->FIOSET=1<<3;
		timer_delay();
		LPC_GPIO0->FIOCLR=1<<3;
		timer_delay();
	}
}

void timer_delay()
{
	LPC_TIM0->TCR=0x2; //Reset TC/PC
	LPC_TIM0->PR=999;
	LPC_TIM0->MR0=3000*x-1;
	LPC_TIM0->CTCR=0;
	LPC_TIM0->MCR=0x4;//STOP TC ON MATCH
	LPC_TIM0->EMR=0x20;
	LPC_TIM0->TCR=0x1;
	
	while((LPC_TIM0->EMR&0x1)==0);
	//when EM0 is 1 exit loop
}

