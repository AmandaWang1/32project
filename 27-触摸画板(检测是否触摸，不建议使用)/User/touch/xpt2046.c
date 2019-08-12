/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����������
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 


#include "./touch/xpt2046.h"


 /**
  * @brief  Һ������ʼ��
  * @param  ��
  * @retval ��
  */
void XPT2046_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//û��ʹ��Ӳ��SPI
	
	
	// ��SPI GPIO��ʱ��
	RCC_APB2PeriphClockCmd(XPT2046_SPI_GPIO_CLK, ENABLE);

	// ��CS CLK MOSI ��GPIO����Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(XPT2046_SPI_CS_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_CLK_PIN;
	GPIO_Init(XPT2046_SPI_CLK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MOSI_PIN;
	GPIO_Init(XPT2046_SPI_MOSI_PORT, &GPIO_InitStructure);
	
	
  // ��PENIRQ MISO ��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = XPT2046_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(XPT2046_SPI_MISO_PORT, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = XPT2046_PENIRQ_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(XPT2046_PENIRQ_GPIO_PORT, &GPIO_InitStructure);
		    
}

/**
  * @brief  ���� XPT2046 �ļ�΢�뼶��ʱ����
  * @param  nCount ����ʱ����ֵ����λΪ΢��
  * @retval ��
  */	
static void XPT2046_DelayUS ( __IO uint32_t ulCount )
{
	uint32_t i;


	for ( i = 0; i < ulCount; i ++ )
	{
		uint8_t uc = 12;     //����ֵΪ12����Լ��1΢��  
	      
		while ( uc -- );     //��1΢��	

	}
	
}


//ģ��ʱ��,��������
void XPT2046_SendCMD(uint8_t cmd)//��������ı���
{
	uint8_t i;
	
	XPT2046_CS_ENABLE();//����CS���Ų����ߵ�ƽ
	
	//�����ǵ�Ĭ��״̬����Ϊ�͵�ƽ
	XPT2046_CLK_LOW();
	XPT2046_MOSI_0();
	
	//Ƭѡѡ��
	XPT2046_DelayUS(10);//��ʱ10΢��
	XPT2046_CS_DISABLE();//ͨѶ������ʼ��Ϊ�͵�ƽ
	
	//���Ͱ˸�����λ�����˸�ʱ��,��ʱ�ӵĸߵ�ƽȥ��������
	for(i=0;i<8;i++)
	{
		if((cmd&(0x80>>i)) ==0)//ȡ��λ
		{
			XPT2046_MOSI_0();
		}
		else
		{
			XPT2046_MOSI_1();
		}
		
//�ڲ����ߵ�ƽ֮ǰ��������׼����(��Ϊ�������ز���)
//	XPT2046_MOSI_1();
		
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
	}
	
//	//Ƭѡȡ��
//	XPT2046_CS_ENABLE();//ͨѶ�������ɸߵ�ƽ
	
}

//��ȡ���ݣ���ȡXPT2046��ADC����ֵ
uint16_t XPT2046_ReceiveData(void)
{
	uint8_t i;
	uint16_t receive_temp=0;
	
//	XPT2046_CS_ENABLE();//����CS���Ų����ߵ�ƽ
//	
//	//�����ǵ�Ĭ��״̬����Ϊ�͵�ƽ
//	XPT2046_CLK_LOW();
//	XPT2046_MOSI_0();
//	
//	//Ƭѡѡ��
//	XPT2046_DelayUS(10);//��ʱ10΢��
//	XPT2046_CS_DISABLE();//ͨѶ������ʼ��Ϊ�͵�ƽ
	
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
	
  //12��ʱ�ӣ���ȡ����
	for(i=0;i<12;i++)
	{
		//���յ�һ��������һλ
		receive_temp = receive_temp << 1;
		
		//�ڶ�����֮ǰ�Ȱ����Ÿ�ɸߵ�ƽ
		XPT2046_CLK_HIGH();
		XPT2046_DelayUS(5);
		
		if(XPT2046_MISO() == Bit_SET)//���Ϊ�ߵ�ƽ
		{
			receive_temp |=0x01;
		}
		else
		{
			receive_temp |=0x00;
		}
		
//		//�ڲ����ߵ�ƽ֮ǰ��������׼����(��Ϊ�������ز���)
//		XPT2046_MOSI_1();		
		
		XPT2046_CLK_LOW();
		XPT2046_DelayUS(5);
		
	}
	
	//Ƭѡȡ��
	XPT2046_CS_ENABLE();//ͨѶ�������ɸߵ�ƽ
	
	return receive_temp;
	
}

