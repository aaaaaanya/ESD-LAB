//Write a c program to display the digital value representing the difference in analog voltages at ADC channel 4 and channel 5 on LCD.
//hardware or burst mode

//CONNECT cnd TO CNAD (lcd)

//chatgpt code
#include <LPC17xx.h>
#include <stdio.h>

int temp1, temp2, flag1, flag2;

void port_write() {
    int i;
    LPC_GPIO0->FIOPIN = temp2 << 23;

    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = 1 << 27;
    else
        LPC_GPIO0->FIOSET = 1 << 27;

    LPC_GPIO0->FIOSET = 1 << 28;
    for (i = 0; i < 50; i++);
    LPC_GPIO0->FIOCLR = 1 << 28;

    for (i = 0; i < 30000; i++);
}

void LCD_write() {
    if ((flag1 == 0) & ((temp1 == 0x30) || (temp1 == 0x20)))
        flag2 = 1;
    else
        flag2 = 0;

    temp2 = temp1 >> 4;
    port_write();

    if (flag2 == 0) {
        temp2 = temp1 & 0xF;
        port_write();
    }
}

void ADC_IRQHandler(void) {
    float v1, v2, diff;
    char vtg1[7], vtg2[7], diffStr[7];
    int t1, t2,i;

    // Check which ADC channel is ready
    int status = LPC_ADC->ADSTAT & (3 << 4);
    if (status == (1 << 4)) {
        t1 = LPC_ADC->ADDR4 >> 4 & 0xFFF;  // Read ADC channel 4
        v1 = (float)t1 * 3.3 / 0xFFF;  // Convert to voltage
    } else if (status == (1 << 5)) {
        t2 = LPC_ADC->ADDR5 >> 4 & 0xFFF;  // Read ADC channel 5
        v2 = (float)t2 * 3.3 / 0xFFF;  // Convert to voltage
    }

    // Calculate the difference
    diff = v1 - v2;

    // Prepare strings for display
    sprintf(vtg1, "%3.2fV", v1);
    sprintf(vtg2, "%3.2fV", v2);
    sprintf(diffStr, "%3.2fV", diff);

    // Display V1
    flag1 = 0;
    temp1 = 0x84;  // Position for V1
    LCD_write();
    flag1 = 1;
    for (i = 0; vtg1[i] != '\0'; i++) {
        temp1 = vtg1[i];
        LCD_write();
    }

    // Display V2
    flag1 = 0;
    temp1 = 0x8B;  // Position for V2
    LCD_write();
    flag1 = 1;
    for (i = 0; vtg2[i] != '\0'; i++) {
        temp1 = vtg2[i];
        LCD_write();
    }

    // Display Difference
    flag1 = 0;
    temp1 = 0x92;  // Position for Difference
    LCD_write();
    flag1 = 1;
    for (i = 0; diffStr[i] != '\0'; i++) {
        temp1 = diffStr[i];
        LCD_write();
    }
}

int main() {
	int i;
	int lcd_init[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x01, 0x80, 0x06};
    // Initialize system and peripherals
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL1 = 0;  // GPIO
    LPC_GPIO0->FIODIR = 0xF << 23 | 1 << 27 | 1 << 28;  // Set GPIO direction
    flag1 = 0;

    // LCD Initialization Sequence
    
    for (i = 0; i <= 8; i++) {
        temp1 = lcd_init[i];
        LCD_write();
    }
    flag1 = 1;

    // Configure ADC
    LPC_PINCON->PINSEL3 = (3 << 30) | (3 << 28);  // Set P1.31 as AD0.5 and P1.30 as AD0.4
    LPC_SC->PCONP = (1 << 12);  // Enable ADC
    LPC_SC->PCONP |= (1 << 15); // Power for GPIO block

    // Enable ADC interrupts
    LPC_ADC->ADCR = (1 << 4) | (1 << 5) | (1 << 21) | (1 << 16);  // Start ADC conversion
    LPC_ADC->ADINTEN = (1 << 4) | (1 << 5);
    NVIC_EnableIRQ(ADC_IRQn);

    while (1);  // Loop indefinitely
}

//my modified code


/*
#include<LPC17xx.h>
#include<stdio.h>
int temp1, temp2, flag1, flag2;

void port_write()
{
int i;
LPC_GPIO0->FIOPIN = temp2 << 23;

if(flag1 == 0)
LPC_GPIO0->FIOCLR = 1 << 27;
else
LPC_GPIO0->FIOSET = 1 << 27;

LPC_GPIO0->FIOSET = 1 << 28;
for(i = 0; i<50; i++);
LPC_GPIO0->FIOCLR = 1 << 28;

for(i = 0; i<30000; i++);
}

void LCD_write()
{
if((flag1 == 0) & ((temp1 == 0x30) || (temp1 == 0x20)))
flag2 = 1;
else
flag2 = 0;
//flag2 = (flag1 == 1) ? 0 :((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
temp2 = temp1 >> 4;
port_write();

if(flag2 == 0)
{
temp2 = temp1 & 0xF;
port_write();
}
}
int main()
{
unsigned int adc_temp;
int i;
float in_vtg;

char msg1[]={"V1:"};
char msg2[]={"D1:"};
char msg3[]={"V2:"};
char msg4[]={"D2:"};
int lcd_init[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x01, 0x80, 0x06};
SystemInit();
SystemCoreClockUpdate();

LPC_PINCON -> PINSEL1 = 0;

LPC_GPIO0 -> FIODIR = 0xF << 23 | 1 << 27 | 1 << 28;
flag1 = 0;
for(i = 0; i<=8; i++)
{
temp1 = lcd_init[i];
LCD_write();
}
flag1 = 1;
LPC_PINCON->PINSEL3=3<<30;//p1.31 as AD0.5
LPC_SC->PCONP=(1<<12);//enable peripheral adc
LPC_SC->PCONP |= (1<<15); //Power for GPIO block

//for first ad0.5
flag1=0;
temp1=0x80;
LCD_write();

flag1=1;
i=0;
while(msg1[i++]!='\0')
{
temp1=msg1[i];
LCD_write();
}

flag1=0;
temp1=0xC0;
LCD_write();
flag1=1;
i=0;

while(msg2[i++]!='\0')
{
temp1=msg2[i];
LCD_write();
}
//for 2nd ad0.4
flag1=0;
temp1=0x88;
LCD_write();

flag1=1;
i=0;
while(msg3[i++]!='\0')
{
temp1=msg3[i];
LCD_write();
}

flag1=0;
temp1=0xC8;
LCD_write();
flag1=1;
i=0;

while(msg4[i++]!='\0')
{
temp1=msg4[i];
LCD_write();
}

while(1)
{
LPC_ADC->ADCR = 1<<4|(1<<5)|(1<<21)|(1<<16);
	LPC_ADC->ADINTEN=1<<4|1<<5;
	NVIC_EnableIRQ(ADC_IRQn);
	while(1);

}
	
}

//
void ADC_IRQHandler(void)
{
	float v1,v2;
	char vtg1[4],dval1[4],vtg2[4],dval2[4];
	int x,i;
	int channel,t1,t2;
	x=LPC_ADC->ADSTAT;
	x=x&(3<<4);
	if(x==1<<4)
	{
		t1=LPC_ADC->ADDR4>>4;
		t1=t1&0xFFF;
		v1 = ((float)t1 * 3.3/0xfff);
	}
	else if(x==1<<5)
	{
				t2=LPC_ADC->ADDR5>>4;
				t2=t2&0xFFF;
				v2 = ((float)t2 * 3.3/0xfff);
	}
	sprintf(vtg1,"%3.2fV",v1);
	sprintf(vtg2,"%3.2fV",v2);
	sprintf(dval1,"%x",t1);
	sprintf(dval2,"%x",t2);
	//for v1
	flag1=0;
temp1=0x84;
LCD_write();
flag1=1;
i=0;

while(vtg1[i]!='\0')
{
temp1=vtg1[i];i++;
LCD_write();
}
//for v2

	flag1=0;
temp1=0x8B;
LCD_write();
flag1=1;
i=0;

while(vtg2[i]!='\0')
{
temp1=vtg2[i];i++;
LCD_write();
}

//for d1

	flag1=0;
temp1=0xC4;
LCD_write();
flag1=1;
i=0;

while(dval1[i]!='\0')
{
temp1=dval1[i];i++;
LCD_write();
}

//for d2

	flag1=0;
temp1=0xCB;
LCD_write();
flag1=1;
i=0;

while(dval2[i]!='\0')
{
temp1=dval2[i];i++;
LCD_write();
}
for(i=0;i<4;i++)
vtg1[i]=dval1[i]=dval2[i]=vtg2[i]=0;

}
*/
