#include "bsp_led.h"


void LED_GPIO_Config (void)
	
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK | LED4_GPIO_CLK| LED5_GPIO_CLK | LED6_GPIO_CLK | LED7_GPIO_CLK | LED8_GPIO_CLK , ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED3_GPIO_PIN;
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED4_GPIO_PIN;
	GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED5_GPIO_PIN;
	GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED6_GPIO_PIN;
	GPIO_Init(LED6_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED7_GPIO_PIN;
	GPIO_Init(LED7_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED8_GPIO_PIN;
	GPIO_Init(LED8_GPIO_PORT, &GPIO_InitStruct);
	
}



