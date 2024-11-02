
//WORKING
//vary pwm acc to adc
#include <lpc17xx.h>

void pwm_init(void)
{
	LPC_SC->PCONP|=1<<6;
	LPC_PINCON->PINSEL3|=2<<14;//P1.23 FOR PWM1.4
	LPC_PWM1->PCR=1<<12; //SINGLE EDGE AND ENABLE
	LPC_PWM1->MCR=2; //reset and interrupt
	LPC_PWM1->MR0=30000;
	LPC_PWM1->MR4=20000;
	LPC_PWM1->LER=0XFF;
	LPC_PWM1->TCR=0X2;
	LPC_PWM1->TCR=0X9;
	return;
}

int main()
{
	int adc_temp,j;
	float v;
	SystemInit();
	SystemCoreClockUpdate();
	LPC_SC->PCONP|=1<<12|1<<15;
	LPC_PINCON->PINSEL3|=3<<30;//FUNC3
	pwm_init();
	while(1)	
	{
	  //for(j = 0; j<10000; j++); //doesnt make a diff
		LPC_ADC->ADCR=1<<5|1<<21|1<<24;
		
		while(!( LPC_ADC->ADGDR >>31 == 0));
		adc_temp=(LPC_ADC->ADGDR>>4)&0XFFF;
		v=((float)adc_temp*3.3/0xfff);
		v=v*100/3.3;
		if (v > 100) v = 100; // Clamp to 100%
		
		LPC_PWM1 -> MR4 = v*300;
	 LPC_PWM1 -> LER = 0xFF;
		
	}
	
}



