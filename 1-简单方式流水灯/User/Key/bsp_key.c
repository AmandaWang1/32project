#include "bsp_key.h"  

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
}

int scan (GPIO_TypeDef *GPIOx,int GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0)
	{
		//���ּ��
	//	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0);
			return 0;
	}
		else
			return 1;
}
