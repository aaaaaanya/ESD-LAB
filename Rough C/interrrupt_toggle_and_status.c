//led toggling but switch status not being displayed

//Toggle LED connected to p0.4 every second while displaying the status of switch connected to P2.12 on the LED connected to P0.5
//toggle p0.4,switch p2.12,status p0.5

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
	//LPC_GPIO0->FIOPIN= ~(LPC_GPIO0->FIOPIN & 1<<4);
	// or 
	LPC_GPIO0->FIOMASK=0xFFFFFFEF;
	LPC_GPIO0->FIOPIN^=(1<<4);
	LPC_GPIO0->FIOMASK=0;
}

int main()
{
	int x;
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0=0;//p0.4 led toggle,p0.5
	LPC_PINCON->PINSEL4=0;//p2.12 led
	
	LPC_GPIO0->FIODIR=1<<4|1<<5;
	//LPC_GPIO2->FIODIR|=0<<12;
	LPC_GPIO2->FIODIR &= ~(1 << 12);
	
	
	timer0_init();
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1)
	{
		x=((LPC_GPIO2->FIOPIN)>>12)&0x1;
		
		LPC_GPIO0->FIOMASK=0xFFFFFFDF;
		LPC_GPIO0->FIOPIN=x<<5;
		LPC_GPIO0->FIOMASK=0;
	}
	
}
/*
//chat gpt code
#include <stdio.h>
#include <lpc17xx.h>

void timer0_init()
{
    LPC_TIM0->TCR = 0x2;          // Reset Timer
    LPC_TIM0->CTCR = 0;           // Timer mode
    LPC_TIM0->PR = 999;           // Prescale for 1s delay (if clock is 100 MHz)
    LPC_TIM0->MR0 = 2999;         // Match register for 1s delay
    LPC_TIM0->MCR = 3;            // Reset and interrupt on MR0 match
    LPC_TIM0->EMR = 0;            // No change on external match
    LPC_TIM0->TCR = 0x1;          // Start Timer
}

void TIMER0_IRQHandler(void)
{
    LPC_TIM0->IR = 1;             // Clear interrupt flag
    LPC_GPIO0->FIOPIN ^= (1 << 4); // Toggle LED at P0.4
}

int main()
{
    int x;
    SystemInit();
    SystemCoreClockUpdate();
    
    LPC_PINCON->PINSEL0 = 0;      // Set P0.4 and P0.5 as GPIO
    LPC_PINCON->PINSEL4 = 0;      // Set P2.12 as GPIO

    LPC_GPIO0->FIODIR = (1 << 4) | (1 << 5); // Set P0.4 and P0.5 as outputs
    LPC_GPIO2->FIODIR &= ~(1 << 12); // Set P2.12 as input

    timer0_init();
    NVIC_EnableIRQ(TIMER0_IRQn);   // Enable TIMER0 interrupt
    
    while (1)
    {
        x = (LPC_GPIO2->FIOPIN >> 12) & 0x1; // Read switch state
        LPC_GPIO0->FIOPIN = (x << 5); // Update P0.5 based on switch state
    }
}
*/