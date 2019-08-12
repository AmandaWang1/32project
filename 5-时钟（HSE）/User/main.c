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
	HSE_SetSysClk(RCC_PLLMul_9);     //��xΪ9ʱΪ72M����xΪ16ʱΪ128M
		
	led ();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay();
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay();
	}		
}

