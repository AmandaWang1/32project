#include "stm32f10x.h"
#include "led.h"
#include "clock.h"

void delay (void)
{
	int i;
	for(i=0;i<50000;i++);
	for(i=0;i<50000;i++);
	for(i=0;i<50000;i++);
}


int main (void)
{
	HSI_SetSysClk(RCC_PLLMul_16);       //64M  
	
	led ();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay();
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay();
	}		
}

