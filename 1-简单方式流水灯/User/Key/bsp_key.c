#include "bsp_key.h"  

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
}

int scan (GPIO_TypeDef *GPIOx,int GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0)
	{
		//松手检测
	//	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0);
			return 0;
	}
		else
			return 1;
}
