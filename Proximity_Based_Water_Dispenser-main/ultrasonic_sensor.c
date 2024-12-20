//THIS IS WORKING
#include <stdio.h> 
#include <LPC17xx.h> 
#include <string.h>
// Defining Constants
#define LED_Pinsel 0xff // P0.4-0.11 (LEDs)
#define TRIGGER_PIN (1 << 15) // P0.15 (Trigger Pin) 
#define ECHO_PIN (1 << 16) // P0.16 (Echo Pin)
// Variable Declarations
int temp, temp1, temp2 = 0; int flag = 0, flag_command=0;
int i, j, k, l, r, echoTime = 5000; float distance = 0;
//Function Declarations 
void delay(int r1); 
void timer_start(void); 
float timer_stop(); 
void timer_init(void);
void delay_in_US(unsigned int microseconds);
void delay_in_MS(unsigned int milliseconds);

//Functions


int main()
{
  int ledflag = 0;
  //int command_init[] = {3, 3, 3, 2, 2, 0x01, 0x06, 0x0C, 0x80};
  SystemInit(); 
  SystemCoreClockUpdate(); 
	timer_init();
  LPC_PINCON->PINSEL0 &= 0xfffff00f; // Interface LEDs P0.4-P0.11 
  LPC_PINCON->PINSEL0 &= 0x3fffffff; // Interface TRIG P0.15 
  LPC_PINCON->PINSEL1 &= 0xfffffff0; // Interface ECHO P0.16
  LPC_GPIO0->FIODIR |= TRIGGER_PIN | 1 << 17; // Direction for TRIGGER pin and Buzzer
  LPC_GPIO1->FIODIR |= 0 << 16; // Direction for ECHO PIN 
  LPC_GPIO0->FIODIR |= LED_Pinsel << 4; // Direction for LED 
  LPC_PINCON->PINSEL1 |= 0;
  LPC_GPIO0->FIODIR |= 0XF << 23 | 1 << 27 | 1 << 28; // Direction For LCDs


  i = 0;
  flag = 1;
  LPC_GPIO0->FIOCLR |= TRIGGER_PIN;
  while (1)
  {
    LPC_GPIO0->FIOSET = 0x00000800;
    // Output 10us HIGH on the TRIGGER pin 
	  LPC_GPIO0->FIOMASK = 0xFFFF7FFF; 
	  LPC_GPIO0->FIOPIN |= TRIGGER_PIN;
    delay_in_US(10);
    LPC_GPIO0->FIOCLR |= TRIGGER_PIN; LPC_GPIO0->FIOMASK = 0x0;
    while (!(LPC_GPIO0->FIOPIN & ECHO_PIN));// Wait till ECHO PIN becomes high
    timer_start();
    while (LPC_GPIO0->FIOPIN & ECHO_PIN); // Wait till ECHO PIN becomes low 
    echoTime = timer_stop(); // Store the time taken on stopping the timer 
    distance = (0.00343 * echoTime) / 2; //Calculations of Distance in cm

    if (distance < 20)
      {
          LPC_GPIO0->FIOSET = LED_Pinsel << 4; 
          LPC_GPIO0->FIOSET = 1 << 17;
      }
    else
      {
          LPC_GPIO0->FIOCLR = LED_Pinsel << 4; 
          LPC_GPIO0->FIOCLR = 1 << 17;
      }
    delay(88000);
}
}

void delay_in_US(unsigned int microseconds)
{
	LPC_TIM0->TCR = 0x02;
  LPC_TIM0->PR = 0; // Set prescaler to the value of 0 
	LPC_TIM0->MR0 = microseconds - 1; // Set match register for 10us 
	LPC_TIM0->MCR = 0x01; // Interrupt on match
  LPC_TIM0->TCR = 0x01; // Enable timer
  while ((LPC_TIM0->IR & 0x01) == 0); // Wait for interrupt flag 
	LPC_TIM0->TCR = 0x00; // Stop the timer
  LPC_TIM0->IR = 0x01; // Clear the interrupt flag
}
void delay_in_MS(unsigned int milliseconds) // Using Timer0
{
  delay_in_US(milliseconds * 1000);
}
void timer_init(void)
{
// Timer for distance 
	LPC_TIM0->CTCR = 0x0;
  LPC_TIM0->PR = 11999999; //To maintain 12Mhz as per specified for LPC 1768 LPC_TIM0->TCR = 0x02; // Reset Timer
}
void timer_start(void)
{
  LPC_TIM0->TCR = 0x02; // Reset Timer 
	LPC_TIM0->TCR = 0x01; // Enable timer
}
float timer_stop()
{
  LPC_TIM0->TCR = 0x0;
  return LPC_TIM0->TC;
}
void delay(int r1)
{
  for (r = 0; r < r1; r++);
}
