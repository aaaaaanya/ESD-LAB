//Timer interrupt for rectangular waveform generation (1.5 second HIGH and 0.5 second LOW) at P0.2

#include <stdio.h>
#include <lpc17xx.h>
int flag=1;

void timer0_init()
{
	LPC_TIM0->TCR=0x2;
	LPC_TIM0->CTCR=0;//timer mode
	LPC_TIM0->EMR=0; //no change in em
	LPC_TIM0->MCR=5;//stop and interrupt
	LPC_TIM0->PR=2999;
	LPC_TIM0->MR0=1499; //for high
	LPC_TIM0->TCR=0X1;
	LPC_GPIO0->FIOSET=1<<2;
	return;
}

void TIMER0_IRQHandler(void)
{
	if(flag==1)
	{
		flag=0;
		LPC_TIM0->TCR=0x2;
		LPC_GPIO0->FIOCLR=1<<2;
		LPC_TIM0->MR0=499;	
		LPC_TIM0->TCR=0x1;
	}
	else
	{
		flag=1;
		LPC_TIM0->TCR=0x2;
		LPC_GPIO0->FIOCLR=1<<2;
		LPC_TIM0->MR0=1499;	
		LPC_TIM0->TCR=0x1;
	}
}

int main()
{
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL0=0;
	timer0_init();
	NVIC_EnableIRQ(TIMER0_IRQn);
	while(1);
}