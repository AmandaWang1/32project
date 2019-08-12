#include "stm32f10x.h"
#include "liu.h"

void delay(void)
{
	int i;
	for(i=0;i<5000;i++);
	for(i=0;i<6000;i++);
	for(i=0;i<6000;i++);
	for(i=0;i<6000;i++);
	for(i=0;i<6000;i++);
	for(i=0;i<6000;i++);
	for(i=0;i<6000;i++);
}

int main (void)
{
	led();
	
	while(1)
	{
		GPIO_SetBits(LED_GPIO_PORT1, LED_GPIO_PIN1);
		GPIO_ResetBits(LED_GPIO_PORT1, LED_GPIO_PIN2);
		delay();
		GPIO_SetBits(LED_GPIO_PORT1, LED_GPIO_PIN1);
		GPIO_ResetBits(LED_GPIO_PORT1, LED_GPIO_PIN2);
		delay();
	}
}



