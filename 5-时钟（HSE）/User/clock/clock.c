#include "clock.h"


//����HSE�ⲿ���پ���������ϵͳʱ��
void HSE_SetSysClk( uint32_t RCC_PLLMul_x)                        
{
	ErrorStatus HSEStatus;
	
	//��RCC�Ĵ�����λ�ɸ�λֵ
	RCC_DeInit();
	
	
	//ʹ��HSE
	RCC_HSEConfig(RCC_HSE_ON);                 								
	
	HSEStatus = RCC_WaitForHSEStartUp();               				//�ȴ�ʹ�ܳɹ�
	
	if( HSEStatus == SUCCESS )
	{
		//ʹ��Ԥȡָ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   
		FLASH_SetLatency(FLASH_Latency_2);											//��Ƶ���ó�72M��Ҫ���ó������ȴ�
		
		//�����������ߵķ�Ƶ����
		RCC_HCLKConfig(RCC_SYSCLK_Div1);												
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//���໷����,����PLLCLK = HSE * RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,  RCC_PLLMul_x);		//x���β�	[2,16]֮�������ֵ
		
		//ʹ��PLL
		RCC_PLLCmd(ENABLE);
		
		//�ȴ�PLL�ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//ѡ��ϵͳʱ��
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() !=0x08);
	}
}

