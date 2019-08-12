/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   触摸屏驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 


#include "./touch/xpt2046.h"


 /**
  * @brief  液晶屏初始化
  * @param  无
  * @retval 无
  */
void XPT2046_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//没有使用硬件SPI
	
	
	// 打开SPI GPIO的时钟
	RCC_APB2PeriphClockCmd(XPT2046_SPI_GPIO_CLK, ENABLE);

	// 将CS CLK MOSI 的GPIO配置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CLK_PIN;
	GPIO_Init(XPT2046_SPI_CLK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
	GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);
	
	
  // 将PENIRQ MISO 的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_PENIRQ_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(XPT2046_PENIRQ_GPIO_PORT, &GPIO_InitStructure);
		    
}

/**
  * @brief  用于 XPT2046 的简单微秒级延时函数
  * @param  nCount ：延时计数值，单位为微妙
  * @retval 无
  */	
static void XPT2046_DelayUS ( __IO uint32_t ulCount )
{
	uint32_t i;


	for ( i = 0; i < ulCount; i ++ )
	{
		uint8_t uc = 12;     //设置值为12，大约延1微秒  
	      
		while ( uc -- );     //延1微秒	

	}
	
}


//模拟时序,发送数据
void XPT2046_SendCMD(uint8_t cmd)//输入命令的编码
{
	uint8_t i;
	
	XPT2046_CS_ENABLE();//控制CS引脚产生高电平
	
	//把他们的默认状态设置为低电平
	XPT2046_CLK_LOW();
	XPT2046_MOSI_0();
	
	//片选选中
	XPT2046_DelayUS(10);//延时10微秒
	XPT2046_CS_DISABLE();//通讯过程中始终为低电平
	
	//发送八个数据位产生八个时钟,在时钟的高电平去产生数据
	for(i=0;i<8;i++)
	{
		if((cmd&(0x80>>i)) ==0)//取高位
		{
			XPT2046_MOSI_0();
		}
		else
		{
			XPT2046_MOSI_1();
		}
		
//在产生高电平之前，把数据准备好(因为在上升沿采样)
//	XPT2046_MOSI_1();
		
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
	}
	
//	//片选取消
//	XPT2046_CS_ENABLE();//通讯结束拉成高电平
	
}

//读取数据，读取XPT2046的ADC参数值
uint16_t XPT2046_ReceiveData(void)
{
	uint8_t i;
	uint16_t receive_temp=0;
	
//	XPT2046_CS_ENABLE();//控制CS引脚产生高电平
//	
//	//把他们的默认状态设置为低电平
//	XPT2046_CLK_LOW();
//	XPT2046_MOSI_0();
//	
//	//片选选中
//	XPT2046_DelayUS(10);//延时10微秒
//	XPT2046_CS_DISABLE();//通讯过程中始终为低电平
	
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
	
  //12个时钟，读取数据
	for(i=0;i<12;i++)
	{
		//接收到一个数据移一位
		receive_temp = receive_temp << 1;
		
		//在读数据之前先把引脚搞成高电平
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		
		if(XPT2046_MISO() == Bit_SET)//如果为高电平
		{
			receive_temp |=0x01;
		}
		else
		{
			receive_temp |=0x00;
		}
		
//		//在产生高电平之前，把数据准备好(因为在上升沿采样)
//		XPT2046_MOSI_1();		
		
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
		
	}
	
	//片选取消
	XPT2046_CS_ENABLE();//通讯结束拉成高电平
	
	return receive_temp;
	
}

