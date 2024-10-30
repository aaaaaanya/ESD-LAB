//Display freq of square wave on 7 segment connected to P0.11 to P0.4
#include<stdio.h>
#include<LPC17xx.h>
int seven_seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delay(void)// for 1s delay
{
LPC_TIM0->TCR = 0x00000002; // Timer0 Reset
LPC_TIM0->CTCR = 0x00000000;
LPC_TIM0->EMR = 0X20;//stop bit upon match
LPC_TIM0->PR = 2999; //For 1s
LPC_TIM0->MR0 =999; //
LPC_TIM0->MCR = 0x4; // stop TC
LPC_TIM0->TCR = 0x00000001; // Timer0 Enable
while(((LPC_TIM0->EMR)&0x1)==0);
}

void timer1_init()
{
	LPC_TIM1->CTCR=0x1; //for rising edge
}
int main(void)
{
	int n;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_PINCON->PINSEL3=3<<4;// P1.18 in fn3
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR=0XFF<<4;
	
	timer1_init();
	
	while(1)
	{
		LPC_TIM1->TCR=0X2;
		LPC_TIM1->TCR=0X1;
		delay(); //delay for 1s
		n=LPC_TIM1->TC; //timer1 is in counter mode, it has counted all the rising edges in 1s
		LPC_GPIO0->FIOPIN=seven_seg[n]<<4;
		
	}
	
	
delay();
while(1);
}