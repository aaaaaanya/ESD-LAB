//Toggle LED connected to p0.2 every second while displaying the status of switch connected to P1.0 on the LED connected to P2.0

#include <stdio.h>
#include <lpc17xx.h>

void timer0_init()
{
	LPC_TIM0->TCR=0x2;
	LPC_TIM0->CTCR=0; //timer mode
	LPC_TIM0->MR0=2999;
	LPC_TIM0->PR=999; //for 1s delay
	LPC_TIM0->MCR=3; //reset and interupt when tc and mr match
	LPC_TIM0->EMR=0; //no change in EM on match
	LPC_TIM0->TCR=0x1;
	return;
	
}

void TIMER0_IRQHandler(void)
{
		LPC_TIM0->IR=1;
	LPC_GPIO0->FIOPIN= ~(LPC_GPIO0->FIOPIN & 1<<2);
	// or 
	//LPC_GPIO0->FIOPIN^=(1<<2);
	
}

int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;//p0.2 led toggle
	LPC_PINCON->PINSEL2=0; //p1.0 switch input
	LPC_PINCON->PINSEL4=0;//p2.0 led
	
	LPC_GPIO0->FIODIR=1<<2;
	LPC_GPIO1->FIODIR=0;
	LPC_GPIO2->FIODIR=1;
	
	
	timer0_init();
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1)
	{
		LPC_GPIO2->FIOPIN=LPC_GPIO1->FIOPIN&0x1;
	}
	
}