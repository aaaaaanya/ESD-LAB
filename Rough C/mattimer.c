//Square waveform on MAT 0.0 output line by taking EM0 on the output pin.
#include<stdio.h>
#include<LPC17xx.h>
void delay(void)
{
LPC_TIM0->TCR = 0x00000002; // Timer0 Reset
LPC_TIM0->CTCR = 0x00000000;
LPC_TIM0->EMR = 0X30;//Toggle bit upon match
LPC_TIM0->PR = 0; //
LPC_TIM0->MR0 = 3000000; //
LPC_TIM0->MCR = 0x00000002; // Reset TC
LPC_TIM0->TCR = 0x00000001; // Timer0 Enable
return;
}
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
LPC_PINCON->PINSEL3 |= (3<<24);//Get EM0 on MAT0.0 (P1.28) line
delay();
while(1);
}