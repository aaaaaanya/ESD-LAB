//WORKS
//Static 4 digit number
//Static number
#include <LPC17xx.h>
int main()
{
	int seven_seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	int n=1234,temp,i,j;
	SystemInit();
	SystemCoreClockUpdate();

	LPC_PINCON->PINSEL0=0;//Configuring lines P0.11 to P0.4+
	LPC_PINCON->PINSEL3=0;//P1.26 to P1.23 for decoder

LPC_GPIO0->FIODIRL=0XFF0;
LPC_GPIO1->FIODIR=0xF<<23;
while(1)
{
	temp=n;
	for(i=0;i<4;i++)
	{
		LPC_GPIO1->FIOPIN=i<<23;//for decoder
		LPC_GPIO0->FIOPIN=seven_seg[temp%10]<<4;
		temp=temp/10;
		for(j=0;j<10000;j++);//delay
	}
}
	
}