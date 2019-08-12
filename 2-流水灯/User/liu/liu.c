#include "liu.h"

void led (void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK1, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin   = LED_GPIO_PIN1 | LED_GPIO_PIN2;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_GPIO_PORT1, &GPIO_InitStruct);
}




