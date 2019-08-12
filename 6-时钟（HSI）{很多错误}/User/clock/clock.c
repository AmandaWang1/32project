#include "clock.h"

void HSE_SetSysClk( uint32_t RCC_PLLMul_x)                        
{
	ErrorStatus HSEStatus;
	
	//把RCC寄存器复位成复位值
	RCC_DeInit();
	
	
	//使能HSE
	RCC_HSEConfig(RCC_HSE_ON);                 								
	
	HSEStatus = RCC_WaitForHSEStartUp();               				//等待使能成功
	
	if( HSEStatus == SUCCESS )
	{
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   
		FLASH_SetLatency(FLASH_Latency_2);											//主频配置成72M，要设置成两个等待
		
		//配置三条总线的分频因子
		RCC_HCLKConfig(RCC_SYSCLK_Div1);												
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//锁相环配置,配置PLLCLK = HSE * RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,  RCC_PLLMul_x);		//x是形参	[2,16]之间的整数值
		
		//使能PLL
		RCC_PLLCmd(ENABLE);
		
		//等待PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//选择系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() !=0x08);
	}
}


//运用HSE外部高速晶振来设置系统时钟
void HSI_SetSysClk( uint32_t RCC_PLLMul_x)                        
{
   _IO uint32_t HSIStatus = 0;
	
	//把RCC寄存器复位成复位值
	RCC_DeInit();
	
	
	//使能HSI
	RCC_HSICmd(ENABLE);               								
	
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;               				//直接操作寄存器
	
	if( HSIStatus == RCC_CR_HSIRDY )													//表示启动成功
	{
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   
		FLASH_SetLatency(FLASH_Latency_2);											//主频配置成72M，要设置成两个等待
		
		//配置三条总线的分频因子
		RCC_HCLKConfig(RCC_SYSCLK_Div1);												
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//锁相环配置,配置PLLCLK = HSE * RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2,  RCC_PLLMul_x);		//配置成2分频   
		//使能PLL
		RCC_PLLCmd(ENABLE);
		
		//等待PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		//选择系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() !=0x08);
	}
	else
	{
		/*如果HSI启动失败，用户可以在这里添加处理错误的代码*/
	}
}

