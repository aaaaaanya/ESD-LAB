//Toggle P0.2 whenever counter value reaches 3. I. e for every 4 edges using counter interrupt.

#include <stdio.h>
#include <lpc17xx.h>

void timer0_init()
{
	LPC_TIM0->TCR=0x2;
	LPC_TIM0->CTCR=5; //counter mode - rising edge and CAP0.1 used (P1.27)
	LPC_TIM0->MR0=3; //when count reaches 3 will reset or wtv
	LPC_TIM0->PR=0;
	LPC_TIM0->MCR=3; //reset and interupt when tc and mr match
	LPC_TIM0->EMR=0; //no change in EM on match
	LPC_TIM0->TCR=0x2;
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
	LPC_PINCON->PINSEL0=3<<22|3<<24; // for CAP0.1 (P1.27) and MAT0.0(P1.28)
	LPC_GPIO0->FIODIR=1<<2;//p0.2 led toggle
	
	
	timer0_init();
	NVIC_EnableIRQ(TIMER0_IRQn);
	while(1);

	
}