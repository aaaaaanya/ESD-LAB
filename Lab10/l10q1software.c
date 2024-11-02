//works
//pr's code - actually for hardware mode
#include <LPC17xx.h>
#include <stdio.h>

int temp1, temp2, flag1, flag2;
float adc_temp1, adc_temp2, difference;
char vtg1[20], vtg2[20]; // Increased size for safety

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
if ((flag1 == 0) && ((temp1 == 0x30) || (temp1 == 0x20)))
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

void initialize_LCD() {
int i;
int lcd_init[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x01, 0x80, 0x06};
flag1 = 0;
for (i = 0; i <= 8; i++) {
temp1 = lcd_init[i];
LCD_write();
}
flag1 = 1;
}

void display_voltages() {
// Display V1 and V2 in a concise format
int i;
sprintf(vtg1, "V1: %.2fV V2: %.1fV", adc_temp1, adc_temp2);
sprintf(vtg2, "Diff: %.2fV", difference);

// Display on the first line
flag1 = 0;
temp1 = 0x80; // Set cursor to first line
LCD_write();
flag1 = 1;
for ( i = 0; vtg1[i] != '\0'; i++) {
temp1 = vtg1[i];
LCD_write();
}

// Display on the second line
flag1 = 0;
temp1 = 0xC0; // Set cursor to second line
LCD_write();
flag1 = 1;
for ( i = 0; vtg2[i] != '\0'; i++) {
temp1 = vtg2[i];
LCD_write();
}
}

int main() {
SystemInit();
SystemCoreClockUpdate();

LPC_PINCON->PINSEL1 = 0; // Set GPIO
LPC_GPIO0->FIODIR = 0xF << 23 | 1 << 27 | 1 << 28; // Configure pins for LCD
initialize_LCD();

LPC_PINCON->PINSEL3 = 3 << 30; // P1.31 as AD0.5
LPC_SC->PCONP = (1 << 12); // Enable peripheral ADC
LPC_SC->PCONP |= (1 << 15); // Power for GPIO block

while (1) {
// Read ADC Channel 4
LPC_ADC->ADCR = (1 << 4) | (1<<5)| (1 << 21) | (1 << 16) | (1 << 5); // Start conversion
while (!(LPC_ADC->ADDR4 >> 31)); // Wait for conversion
adc_temp1 = (LPC_ADC->ADDR4 >> 4) & 0x0FFF; // Read ADC value
adc_temp1 = (adc_temp1 * 3.3 / 0xfff); // Convert to voltage

// Read ADC Channel 5

while (!(LPC_ADC->ADDR5 >> 31)); // Wait for conversion
adc_temp2 = (LPC_ADC->ADDR5 >> 4) & 0x0FFF; // Read ADC value
adc_temp2 = (adc_temp2 * 3.3 / 0xfff); // Convert to voltage

// Calculate the difference
difference = adc_temp1 - adc_temp2;

// Display the results on LCD
display_voltages();
}
}
