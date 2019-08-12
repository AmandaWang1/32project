#include "anjian.h"

void anjian (void)
{
	GPIO_InitTypeDef    GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = ANJIAN_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init (ANJIAN_GPIO_PORT,&GPIO_InitStruct);
	
}

int scan (GPIO_TypeDef *GPIOx,int GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ON)
	{
		//À… ÷ºÏ≤‚
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == ON);
			return ON;
	}
		else
			return OFF;
}

