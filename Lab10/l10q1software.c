//Hardware mode displaying output
////ADC CHannel 5 at P1.31
#include <LPC17xx.h>
#include <stdio.h>

int temp1; //carries the 8 bit data/code
int temp2; //carries the 4 bit data/code to be operated on
int flag1; //0 for command,1 for data (RS)
int flag2; //0 for 8 bits,1 for bit MSB
//P0.28 for enable, P0.27 for RS
//P0.26 to P0.23 data lines(D7 to D4)
void port_write()
{
	int j;
	LPC_GPIO0->FIOPIN=temp2<<23;
	
	if(flag1==0)
	{
		LPC_GPIO0->FIOCLR=1<<27;
	}
	else
	{
		LPC_GPIO0->FIOSET=1<<27;
	}
	//enable LCD
	LPC_GPIO0->FIOSET=1<<28;
	for(j=0;j<20;j++);//delay
	LPC_GPIO0->FIOCLR=1<<28;
	
	for(j=0;j<300000;j++);//delay for lcd to respond
	
}

void lcd_write()
{

	flag2 = (flag1 == 1) ? 0 :((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
	
	
	temp2=temp1&0xF0;
	temp2=temp2>>4;
	port_write();
	if(flag2==0)
	{
		temp2=temp1&0xF;
		port_write();
	}
}


int main()
{
	int i,adc_temp,full_scale=0xFFF;
	float ref_vtg=3.3,in_vtg;
	char vtg[7],dval[7],msg1[]="Analog IP:",msg2[]="ADC output:";
	//char s[]={'f','r','i','d','\0'};
	
	int lcd_init[]={0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};
	
	SystemInit();
	SystemCoreClockUpdate();
LPC_PINCON->PINSEL1=0;	
LPC_GPIO0->FIODIR=3<<27 | 0xF<<23;
//adc
LPC_SC->PCONP=1<<12; //to enable lcd
LPC_SC->PCONP=1<<15; //POWER FOR GPIO BLOCK
LPC_PINCON->PINSEL3=3<<30;
LPC_ADC->ADCR=1<<5|1<<21|1<<24;

while(1)
{
	while ((LPC_ADC->ADGDR & 1<<31)==0);
	//wait till done bit is 1]
	adc_temp=LPC_ADC->ADGDR;
	adc_temp>>=4;
	adc_temp&=0x00000FFF;//12 bit adc
	
	in_vtg=(((float)adc_temp*(float)ref_vtg))/((float)full_scale);
	sprintf(vtg,"%3.2fV",in_vtg);//convert readings into string
	sprintf(dval,"%x",adc_temp); //digitial equivalent
	
	//sending the command codes
	flag1=0;
	for(i=0;i<9;i++)
	{
		temp1=lcd_init[i];
		lcd_write();
	}
	
	//for the data
	//first line
	flag1=1;
	for(i=0;msg1[i]!='\0';i++)
	{
		temp1=msg1[i];
		lcd_write();
	}
	//
	for(i=0;vtg[i]!='\0';i++)
	{
		temp1=vtg[i];
		lcd_write();
	}
	//2nd line
	flag1=0;
	temp1=0xC0;
	lcd_write();
	flag1=1;
	for(i=0;msg2[i]!='\0';i++)
	{
		temp1=msg2[i];
		lcd_write();
	}
	
	for(i=0;dval[i]!='\0';i++)
	{
		temp1=dval[i];
		lcd_write();
	}
	
	for (i=0;i<7;i++)
	vtg[i]=dval[i]=0;
	
}


	
}